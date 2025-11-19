// FSR seat-detect alarm - Arduino Uno
// FSR wired as voltage divider: 5V - FSR - A0 - 10kΩ - GND
// Buzzer -> pin 8, LED -> pin 9 (220Ω series resistor)
// Continuous pressure >= threshold for presenceHoldMs -> alarm ON
// Alarm stops when pressure < threshold

const int fsrPin = A0;         // analog input reading the divider
const int buzzerPin = 8;       // buzzer (active or passive)
const int ledPin = 9;          // LED (with 220Ω resistor)

// CONFIG
const bool passiveBuzzer = false;  // false = active buzzer (digital HIGH), true = passive (tone)
const unsigned int toneFreq = 1000; // Hz for passive buzzer

const unsigned int pressureThreshold = 300; // ADJUST: 0-1023. Increase for heavier pressure needed.
const unsigned long presenceHoldMs = 5000UL; // continuous pressure required (5000 ms)
const unsigned long ledBlinkInterval = 300UL; // blink speed when alarm ON

// STATE
unsigned long detectStart = 0;  // millis when continuous pressure began, 0 = not counting
bool alarmOn = false;
unsigned long lastBlinkToggle = 0;
bool ledState = LOW;

void setup() {
  pinMode(fsrPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);
  digitalWrite(ledPin, LOW);
}

void loop() {
  unsigned long now = millis();

  // read analog and optionally do simple smoothing (3-sample average)
  int v1 = analogRead(fsrPin);
  delay(3);
  int v2 = analogRead(fsrPin);
  delay(3);
  int v3 = analogRead(fsrPin);
  int value = (v1 + v2 + v3) / 3;

  bool pressed = (value >= pressureThreshold);

  if (pressed) {
    if (detectStart == 0) detectStart = now;
    if (!alarmOn && (now - detectStart >= presenceHoldMs)) {
      alarmOn = true;
      lastBlinkToggle = now;
      ledState = LOW; // so first toggle turns it ON
    }
  } else {
    // any release resets detection and immediately stops alarm
    detectStart = 0;
    if (alarmOn) {
      alarmOn = false;
      stopAlarmOutputs();
    }
  }

  // alarm output
  if (alarmOn) {
    if (now - lastBlinkToggle >= ledBlinkInterval) {
      lastBlinkToggle = now;
      ledState = !ledState;
      digitalWrite(ledPin, ledState ? HIGH : LOW);
      if (passiveBuzzer) {
        if (ledState) tone(buzzerPin, toneFreq);
        else noTone(buzzerPin);
      } else {
        digitalWrite(buzzerPin, ledState ? HIGH : LOW);
      }
    }
  } else {
    digitalWrite(ledPin, LOW);
    if (passiveBuzzer) noTone(buzzerPin);
    else digitalWrite(buzzerPin, LOW);
  }

  // short, non-blocking pacing
  delay(20);
}

void stopAlarmOutputs() {
  digitalWrite(ledPin, LOW);
  if (passiveBuzzer) noTone(buzzerPin);
  else digitalWrite(buzzerPin, LOW);
  ledState = LOW;
}
