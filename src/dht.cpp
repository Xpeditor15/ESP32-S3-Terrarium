#include "main.h"

void getDHTdata(DHT dht, float *humidity, float *temperature) {
    float humi = dht.readHumidity();
    float temp = dht.readTemperature();

    if (isnan(humi)) {
        Serial.println("Failed to read humidity!");
        *humidity = -1;
    }

    if (isnan(temp)) {
        Serial.println("failed to read temperature!");
        *temperature = -1;
    }

    *humidity = humi;
    *temperature = temp;
}