# Vegetation-Monitoring-System
The explanation of the arduino code for the plant monitoring system is provided below.

# Included Libraries:
SPI.h: Arduino SPI library.
Wire.h: Arduino Wire library for I2C communication.
Adafruit_GFX.h: Graphics library for Adafruit displays.
Adafruit_SSD1306.h: Adafruit library for the SSD1306 OLED display.
SimpleDHT.h: Library for DHT11 sensor.

# Pin Definitions:
LDRInput (Analog Pin A0): Light-dependent resistor (LDR) sensor.
duration: Duration for the buzzer tone.
pinDHT11 (Digital Pin 2): DHT11 sensor.
sensor_pin (Analog Pin A1): Soil moisture sensor.

# Object Instantiation:
SimpleDHT11 dht11(pinDHT11): Object instantiation for the DHT11 sensor.
Adafruit_SSD1306 display(screen_width, screen_height): Object instantiation for the OLED display.

# Setup:
Serial communication is initialized at a baud rate of 9600.
Pin modes are set for the relay, buzzer, and LDR sensor.
OLED display initialization.

# Loop:
Read temperature and humidity from the DHT11 sensor.
Read soil moisture from the analog soil moisture sensor.
Calculate moisture percentage based on the soil moisture reading.
Print sensor data to the Serial Monitor.
Display sensor data on the OLED display.
Control a relay based on moisture level (turn on if moisture is below 10%).
Activate a buzzer based on specified conditions (humidity, moisture, and temperature thresholds).
Display the data on the OLED screen.

# Relay Control:
The relay (connected to pin 8) is turned on if the moisture percentage is below 10%.

# Buzzer Control:
The buzzer (connected to pin 7) is activated based on certain conditions related to humidity, moisture, and temperature.

# OLED Display:
Display sensor data related to temperature, humidity, moisture, and light level on the OLED screen.
