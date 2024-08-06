/*
  Headless Mode Code for MQ-135 Sensor with SD Card Logging
  This code reads the gas concentration from an MQ-135 sensor and logs it to an SD card.
*/

#include <SPI.h>
#include <SD.h>

const int sensorPin = A0;  // Analog input pin that the MQ-135 is attached to
const int chipSelect = 10; // SD card module chip select pin
int sensorValue = 0;       // Variable to store the value coming from the sensor

void setup() {
  Serial.begin(9600);

  // Initialize the SD card
  if (!SD.begin(chipSelect)) {
    Serial.println("SD card initialization failed!");
    return;
  }
  Serial.println("SD card initialized.");

  // Create or open the data file on the SD card
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println("Gas Concentration Log");
    dataFile.close();
  } else {
    Serial.println("Error opening datalog.txt");
  }
}

void loop() {
  // Read the sensor value
  sensorValue = analogRead(sensorPin);

  // Print the sensor value to the serial monitor
  Serial.print("Gas Concentration: ");
  Serial.println(sensorValue);

  // Write the sensor value to the SD card
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.print("Gas Concentration: ");
    dataFile.println(sensorValue);
    dataFile.close();
  } else {
    Serial.println("Error opening datalog.txt");
  }

  delay(1000);  // Delay in milliseconds
}
