#define BLYNK_TEMPLATE_ID "TMPL6iMaKXtaW"
#define BLYNK_TEMPLATE_NAME "Security System"
#define BLYNK_AUTH_TOKEN "Sd4Q1OSDnFZZHuS-X3ONqC4DzrVjcI3W"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Device";
char pass[] = "helloworld10";

#define TOUCH_PIN1   T0
#define TOUCH_PIN2   T3
#define BUZZER_PIN   26
#define LED_PIN      25
#define SERVO_PIN    27

const int TOUCH_THRESHOLD = 40;
const unsigned long BLINK_MS = 300;
const unsigned long SERVO_STEP_DELAY = 2;
const int SERVO_STEP_SIZE = 2;

bool systemEnabled = false;
bool ledEnabled = false;
bool buzzerEnabled = false;
bool notifyEnabled = false;
bool touchControlEnabled = false;

bool wasTouched1 = false;
bool wasTouched2 = false;
bool alertSent1 = false;
bool alertSent2 = false;
bool blinkState = false;
unsigned long lastBlink = 0;

BlynkTimer timer;
Servo myServo;
int servoTarget = 0;
int servoCurrent = 0;

BLYNK_WRITE(V0) {
  systemEnabled = param.asInt();
  if (!systemEnabled) {
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    servoTarget = 0;
    blinkState = false;
    alertSent1 = false;
    alertSent2 = false;
  }
}
BLYNK_WRITE(V1) { ledEnabled = param.asInt(); }
BLYNK_WRITE(V2) { buzzerEnabled = param.asInt(); }
BLYNK_WRITE(V3) { notifyEnabled = param.asInt(); }
BLYNK_WRITE(V5) {
  touchControlEnabled = param.asInt();
  if (!touchControlEnabled) {
    servoTarget = 0;
    alertSent1 = false;
    alertSent2 = false;
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
  myServo.attach(SERVO_PIN);
  myServo.write(0);
  servoCurrent = 0;
  servoTarget = 0;
  Blynk.begin(auth, ssid, pass);
}

void moveServoSmooth() {
  if (servoCurrent < servoTarget) {
    servoCurrent += SERVO_STEP_SIZE;
    if (servoCurrent > servoTarget) servoCurrent = servoTarget;
    myServo.write(servoCurrent);
    delay(SERVO_STEP_DELAY);
  } else if (servoCurrent > servoTarget) {
    servoCurrent -= SERVO_STEP_SIZE;
    if (servoCurrent < servoTarget) servoCurrent = servoTarget;
    myServo.write(servoCurrent);
    delay(SERVO_STEP_DELAY);
  }
}

void loop() {
  Blynk.run();
  timer.run();
  int touchValue1 = touchRead(TOUCH_PIN1);
  int touchValue2 = touchRead(TOUCH_PIN2);
  bool isTouched1 = touchValue1 < TOUCH_THRESHOLD;
  bool isTouched2 = touchValue2 < TOUCH_THRESHOLD;
  bool anyTouched = isTouched1 || isTouched2;
  if (!systemEnabled) {
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    servoTarget = 0;
    moveServoSmooth();
    wasTouched1 = isTouched1;
    wasTouched2 = isTouched2;
    return;
  }
  if (touchControlEnabled) {
    if (isTouched1 && !wasTouched1) {
      servoTarget = 90;
      if (notifyEnabled && !alertSent1) {
        Blynk.logEvent("area1_alert", "🚨 Someone is in Area 1!");
        alertSent1 = true;
      }
    }
    if (isTouched2 && !wasTouched2) {
      servoTarget = 180;
      if (notifyEnabled && !alertSent2) {
        Blynk.logEvent("area2_alert", "🚨 Someone is in Area 2!");
        alertSent2 = true;
      }
    }
    if ((wasTouched1 && !isTouched1) || (wasTouched2 && !isTouched2)) {
      servoTarget = 0;
      if (notifyEnabled) {
        Blynk.logEvent("alarm_cleared", "✅ Safe, no one here. 🔕 Alarm OFF");
      }
      alertSent1 = false;
      alertSent2 = false;
    }
  } else {
    servoTarget = 0;
  }
  moveServoSmooth();
  if (anyTouched) {
    unsigned long now = millis();
    if (now - lastBlink >= BLINK_MS) {
      blinkState = !blinkState;
      lastBlink = now;
    }
    if (ledEnabled)    digitalWrite(LED_PIN,    blinkState ? HIGH : LOW);
    if (buzzerEnabled) digitalWrite(BUZZER_PIN, blinkState ? HIGH : LOW);
  } else {
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    blinkState = false;
  }
  wasTouched1 = isTouched1;
  wasTouched2 = isTouched2;
}
