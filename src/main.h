#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include "driver/rtc_io.h"
#include "driver/gpio.h"
#include "esp_sleep.h"
#include "esp_mac.h"

void IRAM_ATTR buttonISR();
void IRAM_ATTR modeISR();
void displaySensorData(DHT dht, Adafruit_ST7735 tft);
void getDHTdata(DHT dht, float *humidity, float *temperature);
void LCDPrint(Adafruit_ST7735 tft, char *string, uint16_t color, int x, int y, int size, bool reset, bool newLine);
void LCDPrintBetter(Adafruit_ST7735 tft, char *string, char *oldString, uint16_t color, int x, int y, int size, bool reset, bool newLine);
void printWakeupReason();
void checkSleepTimer(volatile unsigned long lastActivityTime, volatile bool mode);