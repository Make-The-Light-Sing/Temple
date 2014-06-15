#include <FastSPI_LED2.h>
#include <PIRSensor.h>
#include <HCSR04UltraSonic.h>
#include <Color.h>
#include <Segment.h>
#include "Config.h"
#include "Totem.h"

//#define DEBUG

HCSR04UltraSonic HCSR04(TRIGGER_PIN, ECHO_PIN);
PIRSensor        PIRFront(PIR_FRONT_PIN, PIR_LOCK_DURATION);
PIRSensor        PIRBack(PIR_BACK_PIN, PIR_LOCK_DURATION);
SegmentCollection segments;
SegmentCollection segmentsOff;

Totem<LEDSTRIP_PIN> totem;

/**
 * Init
 */
void setup()
{
    setTotemTest1();
    totem.init();
    
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
    
    if (PIRFront.hasMovement() || PIRBack.hasMovement()) {
        totem.setAwake();
        totem.setColor(c);
    } else {
        totem.setSleeping();
    }
    totem.oneStep();
}

/**
 * Totem with square base
 */
void setTotemTest1()
{
    T_SegmentConfig* segments_on;
    T_SegmentConfig* segments_off;

    uint8_t  nb_segment_on  = 2;
    uint16_t nb_leds        = 21;
    uint8_t  nb_segment_off = 1;
    uint16_t segment_on_delay = 20;
    uint16_t segment_off_delay = 0;

    totem = Totem<LEDSTRIP_PIN>(nb_leds);

    segments_on = (T_SegmentConfig *) malloc(nb_segment_on * sizeof(T_SegmentConfig));
    segments_on[0] = {totem.leds, 10, {CWhite, UP, Wave}};
    segments_on[1] = {totem.leds + 10, 11, {CWhite, DOWN, Wave}};
    segments_off = (T_SegmentConfig *) malloc(nb_segment_off * sizeof(T_SegmentConfig));
    segments_off[0] = {totem.leds, 21, {CWhite, DOWN, Spark}};

    totem.config_on = { nb_segment_on, segment_on_delay, segments_on};
    totem.config_off = { nb_segment_off, segment_off_delay, segments_off};
}

/**
 * Totem with square base
 */
/*void setTotemMounrning(CRGB* leds)
{
    unsigned char nb_segment_on  = 4;
    uint16_t nb_leds        = 360;
    unsigned char nb_segment_off = 4;
    unsigned char segment_on_delay = 5;
    unsigned char segment_off_delay = 0;

    segments_on = (T_SegmentConfig *) malloc(nb_segment_on * sizeof(T_SegmentConfig));
    segments_on[0] = {leds, 90};
    segments_on[1] = {leds + 90, 90};
    segments_on[2] = {leds + 180, 90};
    segments_on[3] = {leds + 270, 90};
    
    effects_on = (T_EffectConfig *) malloc(nb_segment_on * sizeof(T_EffectConfig));
    effects_on[0] = {CWhite, UP, Wave};
    effects_on[1] = {CWhite, DOWN, Wave};
    effects_on[2] = {CWhite, UP, Wave};
    effects_on[3] = {CWhite, DOWN, Wave};
    
    segments_off = (T_SegmentConfig *) malloc(nb_segment_off * sizeof(T_SegmentConfig));
    segments_off[0] = {leds, 90};
    segments_off[1] = {leds + 90, 90};
    segments_off[2] = {leds + 180, 90};
    segments_off[3] = {leds + 270, 90};
    
    effects_off = (T_EffectConfig *) malloc(nb_segment_off * sizeof(T_EffectConfig));
    effects_off[0] = {CWhite, DOWN, Spark};
    effects_off[1] = {CWhite, DOWN, Spark};
    effects_off[2] = {CWhite, DOWN, Spark};
    effects_off[3] = {CWhite, DOWN, Spark};

    totem = {
        LEDSTRIP_PIN,
        nb_leds,
        { nb_segment_on, segment_on_delay, segments_on, effects_on},
        { nb_segment_off, segment_off_delay, segments_off, effects_off }
    };
}

// */
