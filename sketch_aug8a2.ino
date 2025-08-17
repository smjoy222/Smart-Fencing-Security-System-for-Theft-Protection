#define BLYNK_TEMPLATE_ID "TMPL6iMaKXtaW"
#define BLYNK_TEMPLATE_NAME "Security System"
#define BLYNK_AUTH_TOKEN "Sd4Q1OSDnFZZHuS-X3ONqC4DzrVjcI3W"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Device";
char pass[] = "helloworld10";

// Pin definitions
#define TOUCH_PIN   T0   // GPIO 4
#define BUZZER_PIN  26
#define LED_PIN     25

const int TOUCH_THRESHOLD = 40;
const unsigned long BLINK_MS = 300;

bool systemEnabled = false;
bool ledEnabled = false;
bool buzzerEnabled = false;
bool notifyEnabled = false;

bool wasTouched = false;
bool alertSent = false;
bool blinkState = false;
unsigned long lastBlink = 0;

BlynkTimer timer;

BLYNK_WRITE(V0) {
  systemEnabled = param.asInt();
  Serial.println(systemEnabled ? "🔛 System Enabled" : "🔴 System Disabled");
  if (!systemEnabled) {
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    blinkState = false;
    alertSent = false;
  }
}

BLYNK_WRITE(V1) { ledEnabled = param.asInt(); }
BLYNK_WRITE(V2) { buzzerEnabled = param.asInt(); }
BLYNK_WRITE(V3) { notifyEnabled = param.asInt(); }

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  Blynk.begin(auth, ssid, pass);
  Serial.println("✅ Connected to WiFi and Blynk!");
}

void loop() {
  Blynk.run();
  timer.run();

  unsigned long now = millis();
  int touchValue = touchRead(TOUCH_PIN);
  bool isTouched = touchValue < TOUCH_THRESHOLD;

  Serial.print("Touch Value: ");
  Serial.print(touchValue);
  Serial.print(" | Touched: ");
  Serial.println(isTouched);

  if (!systemEnabled) {
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    return;
  }

  if (isTouched && !wasTouched) {
    Serial.println("🔔 Touch Detected!");
    blinkState = true;
    if (ledEnabled) digitalWrite(LED_PIN, HIGH);
    if (buzzerEnabled) digitalWrite(BUZZER_PIN, HIGH);
    lastBlink = now;

    if (notifyEnabled && !alertSent) {
      Serial.println("📲 Sending Notification: alarm_triggered");
      Blynk.logEvent("alarm_triggered", "🚨 Security Alert: Someone Is In Your Area ⚠️");
      alertSent = true;
    }
  }

  if (isTouched) {
    if (now - lastBlink >= BLINK_MS) {
      blinkState = !blinkState;
      if (ledEnabled) digitalWrite(LED_PIN, blinkState);
      if (buzzerEnabled) digitalWrite(BUZZER_PIN, blinkState);
      lastBlink = now;
    }
  } else if (wasTouched && !isTouched) {
    Serial.println("✅ Touch Released. Alarm Cleared.");
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    blinkState = false;

    if (notifyEnabled) {
      Serial.println("📲 Sending Notification: alarm_cleared");
      Blynk.logEvent("alarm_cleared", "✅ Safe, no one here. 🔕 Alarm OFF");
    }
    alertSent = false;
  }

  wasTouched = isTouched;
  delay(10);
}



