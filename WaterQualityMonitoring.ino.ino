#include <EEPROM.h>
#include <GravityTDS.h>

#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD 16x2
LiquidCrystal_I2C lcd(0x27, 16, 2);

// DS18B20
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// TDS
#define TdsSensorPin A1
GravityTDS gravityTds;

float temperature = 25;
float tdsValue = 0;

void setup()
{
  Serial.begin(9600);

  // Temp sensor
  sensors.begin();

  // LCD
  lcd.init();
  lcd.backlight();

  // TDS
  gravityTds.setPin(TdsSensorPin);
  gravityTds.setAref(5.0);       // Arduino Uno = 5V
  gravityTds.setAdcRange(1024);  // 10-bit ADC
  gravityTds.begin();
}

void loop()
{
  sensors.requestTemperatures();
  temperature = sensors.getTempCByIndex(0);

  if (temperature == DEVICE_DISCONNECTED_C) {
    temperature = 25; // fallback
  }

  gravityTds.setTemperature(temperature);
  gravityTds.update();
  tdsValue = gravityTds.getTdsValue();

  // ==== Serial ====
  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print(" C | TDS: ");
  Serial.print(tdsValue, 0);
  Serial.println(" ppm");

  // ==== LCD ====
  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.print(temperature, 1);
  lcd.print((char)223);
  lcd.print("C     ");

  lcd.setCursor(0, 1);
  lcd.print("Turbidity:");
  lcd.print(tdsValue, 0);
  lcd.print("ppm   ");

  delay(1000);
}