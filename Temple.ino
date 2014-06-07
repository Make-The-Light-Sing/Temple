#include <Color.h>

/**
 * RGB Led test plugged on PWM output of Arduino Mega 2560
 */
#define LED_RED    44
#define LED_GREEN  45
#define LED_BLUE   46

/**
 * Init
 */
void setup()
{
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_BLUE, OUTPUT);
}

/**
 * Main loop
 */
void loop()
{
    // Init color structure
    struct CRGB c;
    for (uint16_t i = 0; i < 384; i+= 1)
    {
        // Get CRGB value from index in an RGB wheel
        c.Wheel(i);
        // Output color
        analogWrite(LED_RED, 255 - c.r * 2);
        analogWrite(LED_BLUE, 255 - c.b * 2);
        analogWrite(LED_GREEN, 255 - c.g * 2);
        // Delay
        delay(25);
    }
}
