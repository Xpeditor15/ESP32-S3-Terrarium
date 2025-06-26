#include "main.h"

#define PUSHBUTTON 17
#define WAKE_BUTTON 17
#define MODE_BUTTON 15

#define INACTIVITY_TIMEOUT 2*60*1000

int pushbutton = 15;
int state = LOW;
int val = 0;
int LED = 5;

void printWakeupReason() {
    esp_sleep_wakeup_cause_t wakeup_reason;

    wakeup_reason = esp_sleep_get_wakeup_cause();
    
    switch (wakeup_reason) {
        case ESP_SLEEP_WAKEUP_EXT0:
            Serial.println("Wakeup caused by external signal");
            break;
        default: 
            Serial.println("Wakeup caused by restart");
            break;
    }
}

void checkSleepTimer(volatile unsigned long lastActivityTime, volatile bool mode) {
    if (mode) {
        Serial.println("Display is in always-on mode");
        return;
    }

    if ((millis() - lastActivityTime) >= INACTIVITY_TIMEOUT) {
        Serial.println("Inactivity timeout reached, going to sleep...");

        detachInterrupt(digitalPinToInterrupt(WAKE_BUTTON));
        detachInterrupt(digitalPinToInterrupt(MODE_BUTTON));

        delay(2000);
        esp_deep_sleep_start();
    }
}