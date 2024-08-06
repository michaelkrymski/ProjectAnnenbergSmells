/*
  Basic Code for MQ-135 Sensor with LCD Display
  This code reads the gas concentration from an MQ-135 sensor and displays it on an LCD.
*/

#include <LiquidCrystal.h>  // Include the LCD library

// Initialize the LCD library with the numbers of the interface pins
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int sensorPin = A0;  // Analog input pin that the MQ-135 is attached to
int sensorValue = 0; // Variable to store the value coming from the sensor

void setup() {
  Serial.begin(9600);  // Initialize serial communication at 9600 bits per second
  lcd.begin(16, 2);    // Set up the LCD's number of columns and rows
}

void loop() {
  sensorValue = analogRead(sensorPin);  // Read the input on analog pin 0
  Serial.print("Gas Concentration: ");
  Serial.println(sensorValue);          // Print the sensor value to the serial monitor

  // Display the sensor value on the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Gas Concentration:");
  lcd.setCursor(0, 1);
  lcd.print(sensorValue);

  delay(1000);  // Delay in milliseconds
}
