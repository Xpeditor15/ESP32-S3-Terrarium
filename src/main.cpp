#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include "main.h"

/*
MOSI: 11
MISO: 13
SCL: 12
SS: 10
*/

#define TFT_CS 10
#define TFT_RST 20
#define TFT_DC 9
#define TFT_LED 8

#define DHTPIN 21

DHT dht = DHT(DHTPIN, DHT22);
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

/*void setup() {
  Serial.begin(115200);

  dht.begin();
  Serial.println("DHT sensor initialized!");

  pinMode(TFT_LED, OUTPUT);
  analogWrite(TFT_LED, 200); // Turn on backlight

  tft.initR(INITR_144GREENTAB);
  tft.setRotation(2);

  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(1);
  tft.setCursor(0, 0);
  tft.println("Hello, World!");
  Serial.println("TFT initialized!");
}*/

void setup() {
  Serial.begin(115200);

  tft.initR(INITR_144GREENTAB);
  tft.setRotation(2);

  tft.fillScreen(ST77XX_BLACK);
  pinMode(TFT_LED, OUTPUT);
  analogWrite(TFT_LED, 200);
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(2);
  tft.setCursor(0, 0);
  tft.println("Initialized!");
  delay(2000);
  Serial.println("TFT Initialized!");
  
  dht.begin();
  Serial.println("DHT sensor initialized!");
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.println("DHT sensor initialized!");
}

void loop() {
  delay(3000);
  displaySensorData();
  Serial.println("Screen updated!");
}

float getHumidity() {
  float humidity = dht.readHumidity();
  if (isnan(humidity)) {
    Serial.println("Failed to read humidity!");
    return -1;
  }
  return humidity;
}

float getTemperature() {
  float temperature = dht.readTemperature();
  if (isnan(temperature)) {
    Serial.println("Failed to read temperature!");
    return -1;
  }
  return temperature;
}

void clearScreen() {
  tft.fillScreen(ST77XX_BLACK);
}

void displaySensorData() {
  clearScreen();
  float humidity = getHumidity();
  float temperature = getTemperature();

  if (humidity >= 0 && temperature >= 0) {
    tft.setCursor(0, 20);
    tft.setTextColor(ST77XX_GREEN);
    tft.setTextSize(2);
    tft.print("Humidity: ");
    tft.print(humidity);
    tft.println("%");
    
    tft.setCursor(0, 60);
    tft.print("Temp: ");
    tft.print(temperature);
    tft.println("C");
    
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print("%, Temperature: ");
    Serial.print(temperature);
    Serial.println("C");
  }
  else {
    tft.setCursor(0, 20);
    tft.setTextColor(ST77XX_RED);
    tft.setTextSize(2);
    tft.println("Sensor Error!");
    Serial.println("Sensor Error!");
  }
}