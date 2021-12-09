/*
*
*/

#include <Arduino.h>

#define PORT_PUSH_BUTTON 2
#define LED_EXTERNAL 3

bool led_external_state = false;
bool led_change_state = false;

void isr_led_change_state() { // function to handle interrupt
    led_external_state = !led_external_state;
    led_change_state = true;
}

void setup()
{
    // init default serial interface with speed of 9600 bauds
    Serial.begin(115200);

    // initialize LED digital pin as an output
    // LED_BUILTIN is predefined by Arduino framework
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(LED_EXTERNAL, OUTPUT);

    // initialize direction of port with push button connected
    pinMode(PORT_PUSH_BUTTON,INPUT);

    // turn off LED by default
    digitalWrite(LED_EXTERNAL,HIGH);

    // listen to any change on pin PORT_PUSH_BUTTON and execute isr_led_change_state function
    attachInterrupt(digitalPinToInterrupt(PORT_PUSH_BUTTON), isr_led_change_state, CHANGE); // will fire when button is pressed or released
}

void loop()
{
    if (led_change_state == true) {
        digitalWrite(LED_EXTERNAL,led_external_state);
        Serial.print("Zmiana stanu na: ");
        Serial.println(led_external_state);
        led_change_state = false;
    };
    // in this place arduino should go to deep sleep to lower current consumption
}