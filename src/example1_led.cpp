/*
 * Blink
 * Based on Arduino one of the simplest examples
 */

#include <Arduino.h>

bool led_curent_state = HIGH;

int led_delay_change = 1000; // in miliseconds

void setup()
{
    // init default serial interface with speed of 9600 bauds
    Serial.begin(9600);

    // initialize LED digital pin as an output.
    // LED_BUILTIN is predefined by Arduino framework
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
    // change state of led output
    led_curent_state = !led_curent_state;

    // print current state into serial port
    Serial.print("Setting LED to: ");
    Serial.print(led_curent_state);
    Serial.println();

    // switch led state
    digitalWrite(LED_BUILTIN, led_curent_state);

    // wait for a second
    delay(led_delay_change);
}