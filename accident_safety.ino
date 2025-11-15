// Accident Detection using ADXL335 (ONLY Accelerometer)
// Author: Arif's Helper

// --- ORIGINAL ACCELEROMETER PART (unchanged) ---
int xPin = A0;
int yPin = A1;
int zPin = A2;
// LED pin
int ledPin = 8;

float threshold = 3.0;   // Sensitivity threshold

// --- NEW: Motor & IR sensor pins (for L298 style motor driver) ---
const int irPin = 2;         // REES52 OUT -> D2 (active LOW when obstacle)
const int motorIn1 = 5;      // L298 IN1
const int motorIn2 = 6;      // L298 IN2
const int motorEnA = 9;      // L298 ENA (PWM) - controls motor speed

// Optional: set default motor speed (0-255)
const uint8_t MOTOR_SPEED = 255; // adjust if needed (max 255)

void setup() {
  Serial.begin(9600);
  Serial.println("Accident Detection System Started...");

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);   // LED off initially

  // --- NEW initializations for motor and IR sensor ---
  pinMode(irPin, INPUT_PULLUP); // use INPUT_PULLUP; module pulls LOW when obstacle
  pinMode(motorIn1, OUTPUT);
  pinMode(motorIn2, OUTPUT);
  pinMode(motorEnA, OUTPUT);

  // Start motor running (fan ON). If you prefer motor OFF at start set below to 0.
  motorForward(MOTOR_SPEED);
}

void loop() {

  // ======== READ ACCELEROMETER ========
  int xValue = analogRead(xPin);
  int yValue = analogRead(yPin);
  int zValue = analogRead(zPin);

  // Convert to approximate G-force (-3g to +3g)
  float xG = (xValue - 512) / 102.3;
  float yG = (yValue - 512) / 102.3;
  float zG = (zValue - 512) / 102.3;

  // Calculate total G-force
  float totalG = sqrt((xG * xG) + (yG * yG) + (zG * zG));

  Serial.print("G-Force: ");
  Serial.println(totalG);

  // ======== CHECK ACCIDENT ========
  /*if (totalG > threshold) {
    Serial.println("🚨 ACCIDENT DETECTED!");
    delay(2000);
  }

  delay(200);
}*/
  if (totalG > threshold) {
    Serial.println("🚨 ACCIDENT DETECTED!");
    digitalWrite(ledPin, HIGH);   // TURN ON LED
    delay(2000);
  } else {
    digitalWrite(ledPin, LOW);    // LED OFF (normal condition)
  }

  // ======== NEW: Obstacle detection + motor control ========
  // REES52 OUT is LOW when obstacle is present (we used INPUT_PULLUP)
  bool obstacleDetected = (digitalRead(irPin) == LOW);

  if (obstacleDetected) {
    // Turn OFF motor immediately
    motorStop();
    Serial.println("IR: Obstacle detected -> Motor OFF (fan stopped)");
    // optional: wait a bit to avoid flicker
    delay(500);
  } else {
    // No obstacle: keep motor running (fan ON)
    motorForward(MOTOR_SPEED);
    // (you can remove this Serial spam later)
    // Serial.println("IR: Clear -> Motor ON");
  }

  delay(200);
}

// ----------------- Motor helper functions -----------------
void motorStop() {
  // Stop motor by disabling PWM and setting IN pins LOW (coast)
  analogWrite(motorEnA, 0);
  digitalWrite(motorIn1, LOW);
  digitalWrite(motorIn2, LOW);
}

void motorForward(uint8_t speed) {
  // Make motor turn in one direction (adjust wiring if motor spins reverse)
  digitalWrite(motorIn1, HIGH);
  digitalWrite(motorIn2, LOW);
  analogWrite(motorEnA, speed);
}
