#include <FastSPI_LED2.h>
#include <PIRSensor.h>
#include <HCSR04UltraSonic.h>
#include <Color.h>
#include <Segment.h>
#include "Config.h"

//#define DEBUG

HCSR04UltraSonic HCSR04(TRIGGER_PIN, ECHO_PIN);
PIRSensor        PIRFront(PIR_FRONT_PIN, PIR_LOCK_DURATION);
PIRSensor        PIRBack(PIR_BACK_PIN, PIR_LOCK_DURATION);
TM1809Controller800Mhz<LEDSTRIP_PIN> LED;
SegmentCollection segments;
SegmentCollection segmentsOff;

boolean active = false;

/**
 * Init
 */
void setup()
{
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_BLUE, OUTPUT);
    
    Effect_Factory factory;
    LED.init();
    
    for(unsigned int i = 0; i < NB_SEGMENT; i++) {
        segments.addSegment(new Segment(seg_config[i], factory.createEffect(effect_config[i])));
    }
    for(unsigned int i = 0; i < NB_SEGMENT_OFF; i++) {
        segmentsOff.addSegment(new Segment(seg_config_off[i], factory.createEffect(effect_config_off[i])));
    }
    segments.init();
    segmentsOff.init();
    
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
    c.Wheel(distance);
    
    // Output color
    if (PIRFront.hasMovement() || PIRBack.hasMovement()) {
        analogWrite(LED_RED, 255 - c.r * 2);
        analogWrite(LED_BLUE, 255 - c.b * 2);
        analogWrite(LED_GREEN, 255 - c.g * 2);
        for(unsigned int i = 0; i < NB_SEGMENT; i++) {
            segments.setSegmentColor(i, c);
        }
        segments.preStep();
        LED.showRGB((unsigned char *) leds, NUM_LEDS);
        segments.postStep();
        active = true;
    } else {
        analogWrite(LED_RED, 255);
        analogWrite(LED_BLUE, 255);
        analogWrite(LED_GREEN, 255);
        if (active == true) {
            memset(leds, 0, NUM_LEDS * sizeof(struct CRGB));
            active = false;
        }
        segmentsOff.preStep();
        LED.showRGB((unsigned char *) leds, NUM_LEDS);
        segmentsOff.postStep();
    }
    // Delay
    delay(20);
}
