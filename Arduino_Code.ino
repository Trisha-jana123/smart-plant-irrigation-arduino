#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);  // Change this to your actual I2C address

int sensor_pin = A0;       // Sensor Pin
int relay_pin = 7;         // Relay Pin
int last_sensor_data = -1; // Variable to store previous sensor data

void setup()
 {
  Serial.begin(9600);
  lcd.init();               // Initialize LCD
  lcd.backlight();          // Turn on backlight
  pinMode(sensor_pin, INPUT);
  pinMode(relay_pin, OUTPUT);
  }

void loop() {
  int sensor_data = analogRead(sensor_pin);
  
  //when the sensor data changes, it prints the value
  if (sensor_data != last_sensor_data) {
    Serial.print("Sensor_data: ");
    Serial.print(sensor_data);
    Serial.print("\t | ");
    last_sensor_data = sensor_data;  
  }

  if (sensor_data > 950)
   {
    Serial.println("No moisture, Soil is dry");
    digitalWrite(relay_pin, LOW);
    lcd.setCursor(0, 0);
    lcd.print("Soil Dry   ");
    lcd.setCursor(0, 1);
    lcd.print("Motor ON ");
  }
   else if (sensor_data >= 400 && sensor_data <= 950)
    {
    Serial.println("There is some moisture, Soil is medium");
    digitalWrite(relay_pin, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Soil Medium");
    lcd.setCursor(0, 1);
    lcd.print("Motor OFF");
  }
   else if (sensor_data < 400)
    {
    Serial.println("Soil is wet");
    digitalWrite(relay_pin, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Soil Wet   ");
    lcd.setCursor(0, 1);
    lcd.print("Motor OFF");
  }

  delay(1000);
  }
