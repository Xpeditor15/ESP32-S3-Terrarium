#include "main.h"

float getHumidity(DHT dht) {
    float humidity = dht.readHumidity();
    if (isnan(humidity)) {
        Serial.println("Failed to read humidity!");
        return -1;
    }
    return humidity;
}

float getTemperature(DHT dht) {
    float temperature = dht.readTemperature();
    if (isnan(temperature)) {
        Serial.println("Failed to read temperature!");
        return -1;
    }
    return temperature;
}