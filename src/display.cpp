#include "main.h"


void LCDPrint(Adafruit_ST7735 tft, char *string, uint16_t color, int x, int y, int size, bool reset, bool newLine) {
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
}

void LCDPrintBetter(Adafruit_ST7735 tft, char *string, char *oldString, uint16_t color, int x, int y, int size, bool reset, bool newLine) {
    if (reset) {
        tft.setTextColor(ST77XX_BLACK);
        tft.setTextSize(size);
        tft.setCursor(x, y);
        
        if (newLine) {
            tft.println(oldString);
        } else {
            tft.print(oldString);
        }
    }

    tft.setTextColor(color);
    tft.setTextSize(size);
    tft.setCursor(x, y);

    if (newLine) {
        tft.println(string);
    } else {
        tft.print(string);
    }
}

void displaySensorData(DHT dht, Adafruit_ST7735 tft) {
    float humidity, temperature;
    getDHTdata(dht, &humidity, &temperature);

    char *humiMsg = "Humidity: ", *tempMsg = "Temp: ";
    char humiBuffer[10], tempBuffer[10];

    LCDPrint(tft, humiMsg, ST77XX_GREEN, 3, 5, 2, true, true);

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

    LCDPrint(tft, humiBuffer, ST77XX_GREEN, 3, 22, 2, false, true);
    LCDPrint(tft, tempMsg, ST77XX_GREEN, 3, 41, 2, false, true);
    LCDPrint(tft, tempBuffer, ST77XX_GREEN, 3, 60, 2, false, true);
}