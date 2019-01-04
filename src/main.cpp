#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#include "lt_dash.h"

// display
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

// dht 22
DHT dht(DHTPIN, DHTTYPE);


#define LT_PIC_BMP_WIDTH  128
#define LT_PIC_BMP_HEIGHT 64
static const unsigned char PROGMEM lt_pic_bmp[] =
{
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00,
  0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00,
  0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00,
  0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00,
  0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00,
  0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00,
  0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00,
  0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00,
  0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00,
  0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00,
  0x00, 0x00, 0x16, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00,
  0x00, 0x00, 0x35, 0xff, 0xff, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00,
  0x00, 0x00, 0x27, 0x00, 0x01, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00,
  0x00, 0x00, 0x4b, 0x00, 0x01, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00,
  0x00, 0x00, 0x4f, 0x00, 0x01, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00,
  0x00, 0x00, 0x95, 0x00, 0x01, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00,
  0x00, 0x01, 0x25, 0x00, 0x01, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00,
  0x00, 0x01, 0x29, 0x00, 0x01, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00,
  0x00, 0x02, 0x49, 0x00, 0x01, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00,
  0x00, 0x04, 0x51, 0x00, 0x01, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00,
  0x00, 0x04, 0x71, 0x00, 0x01, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00,
  0x00, 0x08, 0xa1, 0x00, 0x01, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00,
  0x00, 0x08, 0xa1, 0x00, 0x01, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00,
  0x00, 0x19, 0x7f, 0xff, 0xff, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00,
  0x00, 0x31, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00,
  0x00, 0x21, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00,
  0x00, 0x41, 0x00, 0x00, 0x0f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00,
  0x00, 0xc1, 0x00, 0x00, 0x0f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00,
  0x00, 0x41, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00,
  0x00, 0x41, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00,
  0x00, 0x41, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00,
  0x00, 0x41, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00,
  0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00,
  0x00, 0xc1, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00,
  0x00, 0xc1, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00,
  0x00, 0x41, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00,
  0x00, 0x41, 0x00, 0x03, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x00, 0x00, 0x02, 0x00,
  0x00, 0x61, 0x00, 0x07, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0x00, 0x00, 0x02, 0x00,
  0x00, 0x41, 0x00, 0x1f, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xc0, 0x00, 0x02, 0x00,
  0x00, 0x41, 0x00, 0x3b, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xf0, 0x00, 0x02, 0x00,
  0x00, 0x41, 0x00, 0x7c, 0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x03, 0xf8, 0x00, 0x06, 0x00,
  0x00, 0x47, 0xff, 0xf0, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0xef, 0xff, 0xfc, 0x00,
  0x00, 0xf9, 0x00, 0x60, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x44, 0x00, 0x7f, 0x00,
  0x01, 0x89, 0x00, 0x41, 0xe1, 0x80, 0x00, 0x00, 0x00, 0x00, 0x50, 0x38, 0x34, 0x00, 0xc1, 0x00,
  0x01, 0x01, 0x00, 0xc3, 0xf0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x60, 0xfe, 0x34, 0x00, 0x81, 0x00,
  0x01, 0x05, 0x00, 0xc6, 0x08, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x71, 0xc7, 0x14, 0x00, 0x81, 0x80,
  0x01, 0x85, 0x00, 0xcc, 0x48, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x71, 0x13, 0x14, 0x00, 0x9f, 0x80,
  0x00, 0x7f, 0xff, 0xcc, 0x2c, 0x40, 0x00, 0x00, 0x00, 0x00, 0x73, 0x29, 0x1c, 0x3f, 0xf0, 0x00,
  0x00, 0x00, 0x00, 0xcc, 0xa8, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xf3, 0x29, 0x17, 0xe0, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xcc, 0x48, 0x80, 0x00, 0x00, 0x00, 0x00, 0x31, 0x11, 0x10, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x47, 0x30, 0x80, 0x00, 0x00, 0x00, 0x00, 0x11, 0xc3, 0x20, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x23, 0xe1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0xfe, 0x60, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x20, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x38, 0xc0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x18, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x01, 0x80, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x06, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x82, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

//static const int STATES[] = {
//  STATE_TEMPERATURE, STATE_ENGINE
//};

int currentState = STATE_INIT;
int currentStateIndex = STATE_INIT;

unsigned long lastUpdateTimestamp = 0;

void temperatureScreenHandler() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Check if any reads failed and exit early
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(0, 12);
  display.setTextSize(2);
  display.print("I:  ");
  display.print(temperature);
  display.println();
  display.print("H:  ");
  display.print(humidity);
  display.println("%");
  display.display();

}

void engineScreenHandler() {
  //dummy for now
  display.clearDisplay();
  display.setCursor(0, 12);
  display.println("RPM: 999");
  display.println("TEMP: 42");
  display.display();
}

void (*state_handler[])() = {
  temperatureScreenHandler, engineScreenHandler
};

void setup()   {
  Serial.begin(9600);
  Serial.print(display.width());
  Serial.print("\n");
  Serial.print(display.height());

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)

  display.clearDisplay();
  display.drawBitmap(0, 0, lt_pic_bmp, LT_PIC_BMP_WIDTH, LT_PIC_BMP_HEIGHT, WHITE);
  display.display();
  delay(5000);
}


void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastUpdateTimestamp >= DISPLAY_SWITCH_INTERVAL) {
    lastUpdateTimestamp = currentMillis;
    currentStateIndex++;
    // handle overflow
    if (currentStateIndex == STATE_COUNT) {
      currentStateIndex = 0;
    }
    state_handler[currentStateIndex]();
  }

}
