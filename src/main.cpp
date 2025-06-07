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
#define DHTTYPE DHT22

DHT dht = DHT(DHTPIN, DHTTYPE);
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  Serial.begin(115200);

  tft.initR(INITR_144GREENTAB);
  tft.setRotation(2);

  pinMode(TFT_LED, OUTPUT);
  analogWrite(TFT_LED, 200);
  char *displayMsg = "Display Ready!";
  LCDPrint(tft, displayMsg, ST77XX_YELLOW, 5, 5, 2, true, true);
  //LCDPrint(displayMsg, ST77XX_YELLOW, 5, 5, 2, true, true);

  delay(2000);

  dht.begin();
  char *sensorMsg = "DHT Sensor Ready!";
  LCDPrint(tft, sensorMsg, ST77XX_YELLOW, 5, 5, 2, true, true);
  //LCDPrint(sensorMsg, ST77XX_YELLOW, 5, 5, 2, true, true);
  
  delay(2000);
}

void loop() {
  delay(3000);
  displaySensorData(dht, tft);
  //displaySensorData();
  Serial.println("Screen updated!");
}

/*
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

void displaySensorData() {
  float humidity = getHumidity();
  float temperature = getTemperature();

  char *humiMsg = "Humidity: ", *tempMsg = "Temp: ";
  char humiBuffer[10], tempBuffer[10];

  LCDPrint(humiMsg, ST77XX_GREEN, 3, 5, 2, true, true);

  if (humidity == -1) {
    sprintf(humiBuffer, "Error");
  } else {
    sprintf(humiBuffer, "%.2f%%", humidity);
  }

  if (temperature == -1) {
    sprintf(tempBuffer, "Error");
  } else {
    sprintf(tempBuffer, "%.1fC", temperature);
  }

  LCDPrint(humiBuffer, ST77XX_GREEN, 3, 22, 2, false, true);
  LCDPrint(tempMsg, ST77XX_GREEN, 3, 41, 2, false, true);
  LCDPrint(tempBuffer, ST77XX_GREEN, 3, 60, 2, false, true);
}

void LCDPrint(char *string, uint16_t color, int x, int y, int size, bool reset, bool newLine) {
  if (reset) {
    tft.fillScreen(ST77XX_BLACK);
  }
  tft.setTextColor(color);
  tft.setTextSize(size);
  tft.setCursor(x, y);
  if (newLine) {
    tft.println(string);
  } else {
    tft.print(string);
  }
}*/