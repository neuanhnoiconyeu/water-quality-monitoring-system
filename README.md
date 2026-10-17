
# Water Quality Monitoring System

An Arduino Uno R3-based water quality monitoring prototype that measures water temperature and Total Dissolved Solids (TDS). The system uses a DS18B20 temperature sensor and a TDS sensor, displays readings on a 16x2 I2C LCD, and sends measurement data to the Arduino Serial Monitor.

## Features

- **Temperature Monitoring:** Reads water temperature using a DS18B20 digital temperature sensor.
- **TDS Measurement:** Measures Total Dissolved Solids using a TDS sensor and the GravityTDS library.
- **Temperature Compensation:** Uses the measured temperature to compensate TDS calculations.
- **LCD Display:** Displays temperature and TDS readings on a 16x2 I2C LCD.
- **Serial Monitoring:** Outputs sensor readings through the Serial Monitor at 9600 baud.
- **Disconnected Sensor Fallback:** Uses a default temperature of 25°C if the temperature sensor is disconnected.

## Hardware Requirements

- Arduino Uno R3
- DS18B20 temperature sensor
- Gravity TDS sensor/module
- 16x2 I2C LCD
- Breadboard and jumper wires
- Appropriate power connections and any components required by the specific sensor modules

## Pin Connections

| Component | Arduino Uno R3 |
|---|---|
| DS18B20 data pin | Digital pin D2 |
| TDS sensor analog output | Analog pin A1 |
| I2C LCD SDA | A4 / SDA |
| I2C LCD SCL | A5 / SCL |
| Power and ground | Follow each module's specifications |

**Notes:**
- The LCD address is configured as `0x27`. Change it if your LCD uses a different I2C address.
- A bare DS18B20 typically requires a pull-up resistor on its data line. Follow the sensor's wiring documentation.
- Check the voltage requirements of each module before connecting it to the Arduino.

## Software Requirements

- Arduino IDE
- Arduino AVR board support for Arduino Uno
- The following libraries:
  - `GravityTDS`
  - `OneWire`
  - `DallasTemperature`
  - `LiquidCrystal_I2C`

`EEPROM.h` and `Wire.h` are included with the Arduino environment. The current sketch includes `EEPROM.h`, although it is not directly used in the program.

## Installation and Setup

1. Clone or download this repository.
2. Install the required libraries using the Arduino IDE Library Manager.
3. Connect the DS18B20 sensor, TDS sensor, and I2C LCD according to the pin connection table.
4. Open `WaterQualityMonitoring.ino` in the Arduino IDE.
5. Select **Arduino Uno** under **Tools > Board**.
6. Select the correct serial port under **Tools > Port**.
7. Upload the sketch to the board.
8. Open **Tools > Serial Monitor** and set the baud rate to `9600`.

## Example Output

The Serial Monitor prints readings in the following format:

```text
Temp: 24.8 C | TDS: 215 ppm
```

The values above are illustrative only. Actual measurements depend on the water sample, sensor calibration, wiring, and operating conditions.

The LCD displays temperature on the first row and TDS on the second row.

## How It Works

1. The Arduino reads the water temperature from the DS18B20 sensor.
2. If the temperature sensor reports a disconnection, the program uses 25°C as a fallback value.
3. The measured temperature is passed to the GravityTDS library.
4. The TDS library updates the measurement and returns a TDS value in parts per million (ppm).
5. The temperature and TDS readings are displayed on the LCD and printed to the Serial Monitor.
6. The process repeats approximately once per second.

## Limitations

- **TDS is not turbidity.** TDS estimates the concentration of dissolved substances in water, while turbidity measures water cloudiness. This implementation uses a TDS sensor and does not currently measure turbidity.
- The default temperature fallback of 25°C can affect TDS compensation if the temperature sensor is disconnected. Check the sensor connection if the displayed temperature remains at this value.
- Reliable measurements depend on appropriate sensor calibration and correct wiring.
- This prototype is intended for educational and experimental use. It is not a certified water-safety testing device.

## Future Improvements

- Add documented sensor calibration procedures.
- Integrate a separate turbidity sensor to measure water clarity.
- Log measurements over time for analysis and visualization.
- Add threshold alerts for selected monitoring parameters.
- Document testing results and measurement accuracy.

## License

No license has been specified yet. Add a license if you intend to define how others may use, modify, and distribute this project.
