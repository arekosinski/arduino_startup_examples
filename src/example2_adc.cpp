/*
 * ADC Read
 * Basic example of using ADC with Arduino
 */

#include <Arduino.h>


#define ADC_RESOLUTION 1024 // ADC is 10 bit resolution
#define SYSTEM_VOLTAGE 5.1  // in volts
#define ADC_PORT       A0   // port on which our circuit is connected

int adc_value_reading = 0;
float adc_voltage = 0.0;

int loop_delay = 500; // set delay between next run to 0.5 second

void setup()
{
    // init default serial interface with speed of 115200 bauds
    Serial.begin(115200);

    // initialize LED digital pin as an output.
    // LED_BUILTIN is predefined by Arduino framework
    pinMode(LED_BUILTIN, OUTPUT);

    // source of reference signal - default board voltage 5V
    analogReference(DEFAULT);
}

void loop()
{
    // let's get start time of this loop
    // micros - Returns the number of microseconds since the Arduino board began running the current program.
    uint32_t time_start = micros();
    
    // get ADC value
    // resolution of ADC in default is 1024 bits (0-1023)
    adc_value_reading = analogRead(ADC_PORT);
    
    // calculate voltage based on ADC reading
    adc_voltage = ((float)adc_value_reading / (float)ADC_RESOLUTION ) * SYSTEM_VOLTAGE;

    Serial.print("Analog read: ");
    Serial.print(adc_value_reading);
    Serial.print("; Voltage: ");
    Serial.print(adc_voltage);
    Serial.println(" V");

    // show time! how long it takes to get one ADC reading?
    uint_fast8_t time_diff = micros() - time_start;
    Serial.print("Operations time [microseconds]: ");
    Serial.println(time_diff);

    delay(loop_delay);
}