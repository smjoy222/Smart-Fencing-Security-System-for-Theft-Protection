#include <WiFi.h>
#include <HTTPClient.h>

#define TOUCH_PIN    T0    // GPIO 4
#define BUZZER_PIN   26    // Safe GPIO for buzzer
#define LED_PIN      25    // Safe GPIO for LED

const int TOUCH_THRESHOLD     = 40;
const unsigned long BLINK_MS  = 300;

const char* WIFI_SSID     = "CODE-RED";
const char* WIFI_PASSWORD = "redcode@";

const char* BOT_TOKEN     = "8307223142:AAFC_Z0isX5h_uW6SA2gBAILMmSGBxWyTec";
const char* CHAT_ID       = "1734320317";

bool wasTouched    = false;
bool alertSent     = false;
bool blinkState    = false;
unsigned long lastBlink = 0;

void setup() {
  Serial.begin(115200);
  
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_PIN, LOW);

  Serial.println("Connecting to Wi‑Fi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ Wi‑Fi Connected!");
  Serial.println("✅ Safe, no one here.");
}

void loop() {
  unsigned long now = millis();
  int touchValue   = touchRead(TOUCH_PIN);
  bool isTouched   = touchValue < TOUCH_THRESHOLD;

  // Touch just started?
  if (isTouched && !wasTouched) {
    // reset blink timer so toggle happens BLINK_MS from now
    lastBlink = now;
    blinkState = false;
    // send alert once
    if (!alertSent) {
      sendTelegram("🚨 Someone Is In Your Area !!!⚠️");
      alertSent = true;
    }
  }

  // While touched, blink at BLINK_MS
  if (isTouched) {
    if (now - lastBlink >= BLINK_MS) {
      blinkState = !blinkState;
      digitalWrite(BUZZER_PIN, blinkState);
      digitalWrite(LED_PIN, blinkState);
      lastBlink = now;
    }
  }
  // Touch just ended?
  else if (wasTouched && !isTouched) {
    // immediately turn OFF outputs
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_PIN, LOW);
    // notify once
    sendTelegram("✅ Safe, no one here.");
    sendTelegram("🔕 Alarm OFF.");
    alertSent = false;
    // ensure blinkState reset
    blinkState = false;
  }

  wasTouched = isTouched;
  delay(10);
}

void sendTelegram(const String &message) {
  if (WiFi.status() != WL_CONNECTED) return;
  HTTPClient http;
  String url = "https://api.telegram.org/bot" + String(BOT_TOKEN)
               + "/sendMessage?chat_id=" + String(CHAT_ID)
               + "&text=" + message;
  http.begin(url);
  int code = http.GET();
  Serial.println(code>0? "📩 Telegram sent":"❌ Telegram failed");
  http.end();
}
