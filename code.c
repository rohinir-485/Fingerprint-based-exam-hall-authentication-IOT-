#include <LiquidCrystal.h>
#include <Adafruit_Fingerprint.h>
#include <Servo.h>
#include <SoftwareSerial.h>

// Set up the SoftwareSerial connection to the fingerprint sensor
SoftwareSerial mySerial(2, 3); // RX, TX
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
// Initialize Servo Object
Servo servo;

// Initialize the library with the LCD pins
LiquidCrystal lcd(12, 11, 6, 7, 5, 4);

// Define the pin where the IR sensor is connected
const int sensorPin = 10;
bool initMsg;
void setup() {
  // Initialize the serial monitor
  Serial.begin(9600);
  servo.attach(9);      // Attach the servo to pin 9
  servo.write(90);       // Set the servo to 0 degrees initially
  delay(1000);

  // Set up the LCD's columns and rows
  lcd.begin(16, 2);
  delay(1000);
  initMsg = false;
  // Set the sensor pin as input
  pinMode(sensorPin, INPUT);
  Serial.println("Fingerprint sensor initializing...");
  delay(1000);
  
  // Initialize fingerprint sensor
  finger.begin(57600);
      delay(1000);
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
    displayMessage("Sensor ready","");
    delay(2000);
    displayMessage("Stand inside ","the mark");
  } else {
    Serial.println("No fingerprint sensor");
    displayMessage("Sensor error","");
    while (1); // Halt the program if sensor not found
  }
}
  
void displayMessage(String message1, String message2) {
  // Clear the LCD only if the message is different to avoid flicker
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(message1);
    lcd.setCursor(0, 1);
    lcd.print(message2);
}

void closingCountDown(){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Door closes in:");
    for(int i = 5; i > 0; i--){
    lcd.setCursor(0, 1);

    lcd.print(String(i) + " Seconds");
    delay(1000);
    }
}
void loop() {
  // Read the IR sensor value
  int sensorValue = digitalRead(sensorPin);
  if(!initMsg){
   displayMessage("Stand inside ","the mark");
   initMsg = true;
  }
  

  while (sensorValue == LOW)
  {
    unsigned long lastPollTime = 0;
    const unsigned long pollInterval = 200; // Poll every 200ms
    bool detected;
    uint8_t d;
    displayMessage("Place your ","finger");
    do{

      delay(1000);
      d = finger.getImage();
      detected = d == FINGERPRINT_OK;
      sensorValue = digitalRead(sensorPin);
    } while(d != FINGERPRINT_OK && sensorValue == LOW);
    if(detected)
    {
      // Convert the image
      uint8_t p = finger.image2Tz();
      if (p == FINGERPRINT_OK){
        // Search for a match
        p = finger.fingerSearch();
        if (p == FINGERPRINT_OK) {
          String matchMessage = "ID: " + String(finger.fingerID);
          displayMessage("Access Granted",matchMessage);
          delay(3000);    
          servo.write(0);      // Unlock the door
          displayMessage("Enter the hall","");
          delay(3000);  
          closingCountDown();        // Keep door open for 10 seconds
          servo.write(90);            // Closes the door
          lcd.clear();
          initMsg = false;
          delay(1500);          // waits for 3 seconds
        } else {
          displayMessage("No match found","Access Denied");
          servo.write(90); 
          delay(1500);    
          initMsg = false;
        }
      }
    }     
  }
}
