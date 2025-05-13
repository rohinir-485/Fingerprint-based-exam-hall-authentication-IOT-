# Fingerprint-based-exam-hall-authentication-IOT-
🔐 Fingerprint-Based Access Control System with LCD, IR Sensor, and Servo
This project uses a fingerprint sensor, LCD display, IR sensor, and servo motor to build a basic biometric door access control system. It verifies a user's fingerprint before allowing access and automatically closes the door after a few seconds.

📦 Components Used
Arduino Uno

Adafruit Fingerprint Sensor

16x2 LCD Display

Servo Motor (e.g., SG90)

IR Obstacle Detection Sensor

Jumper Wires

Breadboard

Power Supply (e.g., 5V)
🧠 How It Works
Initialization:

The LCD displays system readiness.

The fingerprint sensor is initialized.

The IR sensor monitors whether someone is standing within range.

Fingerprint Scan:

When someone is detected by the IR sensor, the LCD prompts them to place their finger on the scanner.

The fingerprint is read and compared with stored templates.

Access Control:

If a match is found, the LCD shows Access Granted with the user ID.

The servo rotates to unlock the door.

A message instructs the user to enter.

A 5-second countdown is shown, after which the door is closed automatically.

Access Denied:

If the fingerprint is not recognized, the LCD displays Access Denied.

📂 File Structure
This sketch is a single .ino file intended to run on an Arduino Uno or compatible board.

🔧 Setup Instructions
Install Libraries:

Adafruit_Fingerprint via Library Manager.

LiquidCrystal (built-in).

Servo (built-in).

SoftwareSerial (built-in).

Wiring:

Connect the components as per the pin configuration table.

Make sure to power the fingerprint sensor with proper 3.3V or 5V (as per the module).

Enroll Fingerprints:

Use the Adafruit enrollment sketch to register fingerprints before running this code.
