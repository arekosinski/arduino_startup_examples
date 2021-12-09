/*
*
*/

#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include "Adafruit_SHT31.h"

// SHT31 variables
Adafruit_SHT31 sht31 = Adafruit_SHT31();

#define I2C_ADDRESS_SHT31   0x44

// OLED variables
U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);

// u8g2 lib is one of many to handle OLED displays

void setup(void) {

    Serial.begin(115200);
    Serial.println("Starting...");

    // initialize SHT31 temp/humidity sensor
    if (! sht31.begin(I2C_ADDRESS_SHT31)) {
        Serial.println("Couldn't find SHT31");
        for (;;) { delay(1000); }; // loop for ever in case of error
    };

    u8g2.begin();
    u8g2.clearDisplay();
}

void loop(void) {

    float sht31_temperature = sht31.readTemperature(); //get temperature from sensor
    float sht31_humidity = sht31.readHumidity(); //get humidity from sensor

    if (! isnan(sht31_temperature)) {  // check if 'is not a number'
        Serial.print("Temp *C = ");
        Serial.println(sht31_temperature);
    } else { 
        Serial.println("SHT31: Failed to read temperature");
    }
  
    if (! isnan(sht31_humidity)) {  // check if 'is not a number'
        Serial.print("Hum. % = ");
        Serial.println(sht31_humidity);
    } else { 
        Serial.println("SHT31: Failed to read humidity");
    }

    // convert string into chars
    char str_temperature[6];
    char str_humidity[6];
    dtostrf(sht31_temperature,5,2,str_temperature);
    dtostrf(sht31_humidity,5,2,str_humidity);

    /* OLED Display
    *
    *  (0,0)  --------------- (0,128)
    *         |             |
    *         |             |
    *  (64,0) --------------- (64,128)
    */
    u8g2.firstPage();
    do {
        u8g2.drawFrame(0,0,128,64);
        u8g2.setFont(u8g_font_profont12);
        u8g2.drawStr(4,22,"Temp *C");
        u8g2.drawStr(4,50,"Hum %");
        u8g2.setFont(u8g_font_helvB18n);
        u8g2.drawStr(55,26,str_temperature);
        u8g2.drawStr(55,56,str_humidity);
    } while ( u8g2.nextPage() );

    delay(1000);
}

