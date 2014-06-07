#include <PIRSensor.h>
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

#define PIR_FRONT_PIN 3
#define PIR_BACK_PIN  2

#define PIR_LOCK_DURATION 5000
//#define DEBUG

HCSR04UltraSonic HCSR04(TRIGGER_PIN, ECHO_PIN);
PIRSensor        PIRFront(PIR_FRONT_PIN, PIR_LOCK_DURATION);
PIRSensor        PIRBack(PIR_BACK_PIN, PIR_LOCK_DURATION);

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
        if (PIRFront.triggered()) {
            Serial.println("Movement in front sensor");
        }
        if (PIRBack.triggered()) {
            Serial.println("Movement in back sensor");
        }
    #endif
        
    // Get CRGB value from index in an RGB wheel, index is the distance
    c.Wheel(distance % 384);
    
    // Output color
    if (PIRFront.hasMovement() || PIRBack.hasMovement()) {
        analogWrite(LED_RED, 255 - c.r * 2);
        analogWrite(LED_BLUE, 255 - c.b * 2);
        analogWrite(LED_GREEN, 255 - c.g * 2);
    } else {
        analogWrite(LED_RED, 255);
        analogWrite(LED_BLUE, 255);
        analogWrite(LED_GREEN, 255);
    }
    // Delay
    delay(100);
}
