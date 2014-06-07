#include <HCSR04UltraSonic.h>
#include <Color.h>

/**
 * RGB Led test plugged on PWM output of Arduino Mega 2560
 */
#define LED_RED    44
#define LED_GREEN  45
#define LED_BLUE   46

#define TRIGGER_PIN 9
#define ECHO_PIN    8

//#define DEBUG

HCSR04UltraSonic HCSR04(TRIGGER_PIN, ECHO_PIN);

/**
 * Init
 */
void setup()
{
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_BLUE, OUTPUT);
    
    #ifdef DEBUG
        Serial.begin(9600);
    #endif
}

/**
 * Main loop
 */
void loop()
{
    // Init color structure
    struct CRGB c;
    
    // Read distance from Sensor
    int distance = HCSR04.readDistance();
    #ifdef DEBUG
        Serial.println(distance);
    #endif
        
    // Get CRGB value from index in an RGB wheel, index is the distance
    c.Wheel(distance % 384);
    // Output color
    analogWrite(LED_RED, 255 - c.r * 2);
    analogWrite(LED_BLUE, 255 - c.b * 2);
    analogWrite(LED_GREEN, 255 - c.g * 2);
    // Delay
    delay(100);
}
