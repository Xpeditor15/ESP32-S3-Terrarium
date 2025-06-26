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

#define WAKE_BUTTON 17
#define MODE_BUTTON 15
#define LED 5

#define USE_EXT0_WAKEUP 1
#define BUTTON_PIN_BITMASK(GPIO) (1ULL << GPIO)
#define WAKEUP_GPIO GPIO_NUM_17

#define BUTTON_DEBOUNCE 200
#define POPUP_DISPLAY_TIME 5000

DHT dht = DHT(DHTPIN, DHTTYPE);
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

volatile unsigned long lastActivityTime = 0;
volatile unsigned long lastButtonPress = 0;
volatile unsigned long lastPopupDisplay = 0;
volatile bool modeChanged = false; //false = automatic sleep mode, true = always-on display

void setup() {
  Serial.begin(115200);
  Serial.println("Starting...");

  tft.initR(INITR_144GREENTAB);
  tft.setRotation(2);

  pinMode(TFT_LED, OUTPUT);
  analogWrite(TFT_LED, 200);
  char displayMsg[] = "Display Ready!";
  LCDPrint(tft, displayMsg, ST77XX_YELLOW, 5, 5, 2, true, true);

  delay(1000);

  dht.begin();
  char sensorMsg[] = "DHT Sensor Ready!";
  LCDPrint(tft, sensorMsg, ST77XX_YELLOW, 5, 5, 2, true, true);

  pinMode(WAKE_BUTTON, INPUT_PULLUP);
  pinMode(MODE_BUTTON, INPUT_PULLUP);
  pinMode(LED, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(WAKE_BUTTON), buttonISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(MODE_BUTTON), modeISR, FALLING);
  lastActivityTime = millis(), lastButtonPress = millis();
  delay(1000);

  //Sleep Mode Configs
#if USE_EXT0_WAKEUP
  esp_sleep_enable_ext0_wakeup(WAKEUP_GPIO, 0);
  rtc_gpio_pulldown_dis(WAKEUP_GPIO);
  rtc_gpio_pullup_en(WAKEUP_GPIO);
#endif

  /*esp_sleep_wakeup_cause_t wakeup_reason = esp_sleep_get_wakeup_cause();
  if (wakeup_reason == ESP_SLEEP_WAKEUP_EXT0) {
    LCDPrint(tft, "Woke up from button", ST77XX_GREEN, 5, 5, 2, true, true);
    Serial.println("Woke up from button press");
  }*/
}

void loop() {
  checkSleepTimer(lastActivityTime, modeChanged);

  if (lastPopupDisplay != 0 && (millis() - lastPopupDisplay < POPUP_DISPLAY_TIME)) {
    Serial.println("Displaying popup message");
    delay(1000);
    return;
  } else {
    delay(3000);
    displaySensorData(dht, tft);
  }
}

void IRAM_ATTR buttonISR() {
  lastActivityTime = millis();
}

void IRAM_ATTR modeISR() {
  if (millis() - lastButtonPress < BUTTON_DEBOUNCE) return;

  if (modeChanged) {
    modeChanged = false;
    Serial.println("Switching to automatic sleep mode");
    LCDPrint(tft, "Auto Sleep Mode", ST77XX_GREEN, 5, 5, 2, true, true);
  } else {
    modeChanged = true;
    Serial.println("Switching to always-on display mode");
    LCDPrint(tft, "Always-On Display Mode", ST77XX_GREEN, 5, 5, 2, true, true);
  }
  buttonISR();
  lastPopupDisplay = millis();
}