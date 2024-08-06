# Food Waste Odor Detection System

This project aims to design a system to safely vent the gasses from a food waste dumpster to prevent bad odors from affecting workers and nearby areas. The system uses an Arduino and an MQ-135 gas sensor to detect and measure the concentration of gases emitted from the food waste.

## Components Needed

1. **Arduino Board** (e.g., Arduino Uno)
2. **MQ-135 Gas Sensor**
3. **Breadboard and Jumper Wires**
4. **Power Supply** (for the Arduino)
5. **LCD Display** (optional, for real-time monitoring)
6. **Data Logging Module** (optional, for recording data)

## Sensor Selection

The MQ-135 gas sensor is suitable for detecting various gases like ammonia, sulfur, benzene, smoke, and other harmful gases, which are likely to be present in food waste. It provides an analog output based on the concentration of gases.

## Wiring Diagram

1. **MQ-135 Sensor:**
   - VCC to 5V on Arduino
   - GND to GND on Arduino
   - A0 (Analog Output) to A0 on Arduino

2. **LCD Display (Optional):**
   - Connect as per the specific LCD display datasheet

## Calibrating the MQ-135 Sensor

To ensure accurate readings, the MQ-135 sensor needs to be calibrated. Follow these steps to calibrate the sensor:

1. **Preheat the Sensor:**
   - Power the sensor for at least 24 hours before using it for the first time to stabilize its internal heating element.

2. **Clean Air Calibration:**
   - Place the sensor in a clean air environment.
   - Note the analog value from the sensor (this value will be used as the baseline for clean air).

3. **Adjust the Load Resistor:**
   - If possible, adjust the load resistor to get a baseline value close to 200-300 in clean air.
   - This value represents the sensor's resistance in clean air.

4. **Calculate the Ratio:**
   - Use the formula `RS/R0` to calculate the ratio, where `RS` is the resistance of the sensor in the test gas, and `R0` is the resistance of the sensor in clean air.

5. **Determine the Concentration:**
   - Use the sensor's datasheet graph to map the `RS/R0` ratio to the gas concentration.

## Reading the Data

- **Analog Value:** The sensor outputs an analog value between 0 and 1023. This value represents the concentration of gases detected by the sensor.
- **RS/R0 Ratio:** This ratio is crucial for determining the concentration of specific gases. `RS` is the resistance of the sensor in the presence of the target gas, and `R0` is the resistance in clean air. The sensor's datasheet provides graphs that relate this ratio to specific gas concentrations.
- **Gas Concentration:** By comparing the RS/R0 ratio with the datasheet graphs, you can determine the concentration of different gases like ammonia, sulfur, benzene, etc.

## Arduino Code

### Basic Code

This code is for using an LCD to display gas concentration values in real-time.

```cpp
#include <LiquidCrystal.h>  // Include the LCD library (only if using an LCD)

// Initialize the LCD library with the numbers of the interface pins (only if using an LCD)
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int sensorPin = A0;  // Analog input pin that the MQ-135 is attached to
int sensorValue = 0; // Variable to store the value coming from the sensor

void setup() {
  Serial.begin(9600);  // Initialize serial communication at 9600 bits per second
  lcd.begin(16, 2);    // Set up the LCD's number of columns and rows (only if using an LCD)
}

void loop() {
  sensorValue = analogRead(sensorPin);  // Read the input on analog pin 0
  Serial.print("Gas Concentration: ");
  Serial.println(sensorValue);          // Print the sensor value to the serial monitor

  // Display the sensor value on the LCD (only if using an LCD)
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Gas Concentration:");
  lcd.setCursor(0, 1);
  lcd.print(sensorValue);

  delay(1000);  // Delay in milliseconds
}
```

### Headless Code


For a setup without an LCD, focusing only on outputting results to an SD card, you can use a stacking SD card module that operates at 3.3V. This module plugs into all the pins of the Arduino and includes an SD card slot with an onboard real-time clock optionally powered by a battery. This ensures the clock keeps running even when the main power is off. Use the following code:

```cpp
#include <SPI.h>
#include <SD.h>

const int sensorPin = A0;  // Analog input pin that the MQ-135 is attached to
const int chipSelect = 10; // SD card module chip select pin
int sensorValue = 0;       // Variable to store the value coming from the sensor

void setup() {
  Serial.begin(9600);
  if (!SD.begin(chipSelect)) {
    Serial.println("SD card initialization failed!");
    return;
  }
  Serial.println("SD card initialized.");
}

void loop() {
  sensorValue = analogRead(sensorPin);  // Read the input on analog pin 0
  Serial.print("Gas Concentration: ");
  Serial.println(sensorValue);          // Print the sensor value to the serial monitor

  // Write to the SD card
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
```
