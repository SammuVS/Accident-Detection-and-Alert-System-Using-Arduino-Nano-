# Accident-Detection-and-Alert-System-Using-Arduino-Nano-
We built a simple, low-cost safety system that tries to prevent accidents by using a REES52 IR sensor to instantly stop the motor through an L298N when an obstacle appears. If a collision still occurs, the ADXL335 accelerometer detects the impact and activates a buzzer and LED to alert nearby people for immediate help.

# How it works (flow)

1. The REES52 IR sensor constantly scans the area in front of the vehicle for any nearby obstacle.

2. The motor runs the fan normally, but the moment the IR sensor spots an object, the Arduino signals the L298N motor driver to immediately stop the fan. The fan stays off until the obstacle moves out of the sensor’s detection zone.

3. If an impact still occurs, the ADXL335 accelerometer detects the sudden change in motion, and the Arduino activates the buzzer and LED to warn people around.

## Components (what I used)
- Arduino Nano
- L298N Motor Driver Module
- REES52 IR Infrared Obstacle Avoidance Sensor Module
- ADXL335 3-axis Accelerometer
- Mini DC Motor (3V–6V)
- Buzzer (active)
- LED 
- Breadboard, jumper wires,normal electrical wires and USB cable
- HIW 9V battery (or appropriate power supply for motor)
