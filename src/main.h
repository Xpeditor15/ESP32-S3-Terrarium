#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

//float getHumdity();
//float getTemperature();
//void displaySensorData();
//void LCDPrint(char *string, uint16_t color, int x, int y, int size, bool reset, bool newLine);
float getHumidity(DHT dht);
float getTemperature(DHT dht);
void displaySensorData(DHT &dht, Adafruit_ST7735 tft);
void LCDPrint(Adafruit_ST7735 tft, char *string, uint16_t color, int x, int y, int size, bool reset, bool newLine);