#define TOUCH_PIN    T0  
#define BUZZER_PIN   13 
#define LED_PIN      12  

const int TOUCH_THRESHOLD = 40;

bool wasTouched = false;
unsigned long previousMillis = 0;
const unsigned long interval =  250;
bool ledBuzzerState = false;         

void setup() {
  Serial.begin(115200);
  delay(1000); 

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_PIN, LOW);

  Serial.println("✅ System ready. Monitoring iron wire...");
}

void loop() {
  int touchValue = touchRead(TOUCH_PIN);
  bool isTouched = (touchValue < TOUCH_THRESHOLD);

  unsigned long currentMillis = millis();

  if (isTouched) {
    if (!wasTouched) {
      Serial.println("🚨 Someone Is In Your Area !!!⚠️");
      previousMillis = currentMillis;
      ledBuzzerState = true;
      digitalWrite(BUZZER_PIN, HIGH);
      digitalWrite(LED_PIN, HIGH);
    } else {
      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        ledBuzzerState = !ledBuzzerState;

        digitalWrite(BUZZER_PIN, ledBuzzerState ? HIGH : LOW);
        digitalWrite(LED_PIN, ledBuzzerState ? HIGH : LOW);
      }
    }
  } else {
    if (wasTouched) {
      Serial.println("✅ Safe, No One Here.");
      Serial.println("🔕 Alarm OFF");
      digitalWrite(BUZZER_PIN, LOW);
      digitalWrite(LED_PIN, LOW);
    }
  }

  wasTouched = isTouched;
}
