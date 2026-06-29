/*
 * Minor Project: Climate Control Module
 * Unlox Academy - Week 01 Project
 *
 * Components:
 *   - Arduino Uno
 *   - Potentiometer (simulates LM35 temperature sensor)
 *   - TIP120 NPN Transistor
 *   - DC Motor (Fan)
 *   - 1N4007 Flyback Diode
 *   - 1kOhm Resistor
 *
 * Motor Behavior:
 *   - OFF (PWM = 0)   below 27 degree C
 *   - Linear ramp     27 degree C to 40 degree C
 *   - Max speed       (PWM = 255) at 40 degree C and above
 *
 * Pin Connections:
 *   - Potentiometer middle pin  -> A0
 *   - Motor PWM (via TIP120)    -> D9
 */

// ── Pin definitions ──────────────────────────────────────────
const int TEMP_PIN     = A0;  // Potentiometer / LM35 analog input
const int MOTOR_PIN    = 9;   // PWM output to TIP120 base (via 1k resistor)

// ── Temperature thresholds ───────────────────────────────────
const float TEMP_MIN   = 27.0;  // Fan turns ON at this temp
const float TEMP_MAX   = 40.0;  // Fan reaches full speed here

// ── Timing ───────────────────────────────────────────────────
const unsigned long INTERVAL = 500; // Print every 500ms
unsigned long lastTime = 0;

// ────────────────────────────────────────────────────────────
void setup() {
  Serial.begin(9600);
  pinMode(MOTOR_PIN, OUTPUT);
  analogWrite(MOTOR_PIN, 0); // Motor OFF at start
  Serial.println("Climate Control Module Started");
  Serial.println("--------------------------------");
}

// ────────────────────────────────────────────────────────────
void loop() {
  unsigned long now = millis();

  if (now - lastTime >= INTERVAL) {
    lastTime = now;

    // ── Read analog value from potentiometer (0 to 1023) ──
    int rawValue = analogRead(TEMP_PIN);

    // ── Convert to voltage (0V to 5V) ──
    float voltage = rawValue * (5.0 / 1023.0);

    // ── Simulate temperature using LM35 formula ──
    // LM35: 10mV per degree C → temp = voltage * 100
    // Potentiometer goes 0-5V so temp range = 0°C to 500°C
    // To make simulation easier, we scale it to 0°C to 50°C
    // by mapping: tempC = voltage * 10
    float tempC = voltage * 10.0;

    // ── Calculate PWM value ──
    int pwmValue;

    if (tempC < TEMP_MIN) {
      pwmValue = 0;           // Fan OFF

    } else if (tempC >= TEMP_MAX) {
      pwmValue = 255;         // Fan full speed

    } else {
      // Linear mapping between 27°C and 40°C
      pwmValue = (int)((tempC - TEMP_MIN) / (TEMP_MAX - TEMP_MIN) * 255.0);
    }

    // ── Drive the motor ──
    analogWrite(MOTOR_PIN, pwmValue);

    // ── Print output in required format ──
    Serial.print("Temp: ");
    Serial.print(tempC, 1);
    Serial.print("C, PWM: ");
    Serial.println(pwmValue);
  }
}
