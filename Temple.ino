#include <FastSPI_LED2.h>
#include <PIRSensor.h>
#include <HCSR04UltraSonic.h>
#include <Color.h>
#include "Config.h"

//#define DEBUG

HCSR04UltraSonic HCSR04(TRIGGER_PIN, ECHO_PIN);
PIRSensor        PIRFront(PIR_FRONT_PIN, PIR_LOCK_DURATION);
PIRSensor        PIRBack(PIR_BACK_PIN, PIR_LOCK_DURATION);
TM1809Controller800Mhz<LEDSTRIP_PIN> LED;
struct CRGB leds[NUM_LEDS];

/**
 * Init
 */
void setup()
{
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_BLUE, OUTPUT);
    LED.init();
    
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
    for(int iLed = 0; iLed < NUM_LEDS; iLed++) {

        // Read distance from Sensor
        int distance = HCSR04.readDistance();
        #ifdef DEBUG
            Serial.println(distance);
            if (PIRFront.triggered()) {
                Serial.println("Movement in front sensor");
            }
            if (PIRBack.triggered()) {
                Serial.println("Movement in back sensor");
            }
        #endif
        
        
        memset(leds, 0,  NUM_LEDS * sizeof(struct CRGB));
        // Get CRGB value from index in an RGB wheel, index is the distance
        c.Wheel(distance);
        
        // Output color
        if (PIRFront.hasMovement() || PIRBack.hasMovement()) {
            analogWrite(LED_RED, 255 - c.r * 2);
            analogWrite(LED_BLUE, 255 - c.b * 2);
            analogWrite(LED_GREEN, 255 - c.g * 2);
            leds[iLed] = c;
        } else {
            analogWrite(LED_RED, 255);
            analogWrite(LED_BLUE, 255);
            analogWrite(LED_GREEN, 255);
            leds[iLed] = CBlack;
        }
        LED.showRGB((byte*)leds, NUM_LEDS);
        // Delay
        delay(20);
    }
}
