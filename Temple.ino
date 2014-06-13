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
    
    pinMode(PIN_SELECT_1, INPUT);
    pinMode(PIN_SELECT_2, INPUT);
    
//    setTotemTest2(leds);
//    setConfiguration(leds);
    setTotemMounrning(leds);
    
    Effect_Factory factory;
    LED.init();
    for (unsigned int i = 0; i < totem.config_on.size; i++) {
        segments.addSegment(new Segment(totem.config_on.segments[i], factory.createEffect(totem.config_on.effects[i])));
    }
    for (unsigned int i = 0; i < totem.config_off.size; i++) {
        segmentsOff.addSegment(new Segment(totem.config_off.segments[i], factory.createEffect(totem.config_off.effects[i])));
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
        for(unsigned int i = 0; i < totem.config_on.size; i++) {
            segments.setSegmentColor(i, c);
        }
        segments.preStep();
        LED.showRGB((unsigned char *) leds, totem.nb_leds);
        segments.postStep();
        active = true;
        // Delay
        delay(totem.config_on.delay);
    } else {
        analogWrite(LED_RED, 255);
        analogWrite(LED_BLUE, 255);
        analogWrite(LED_GREEN, 255);
        if (active == true) {
            memset(leds, 0, totem.nb_leds * sizeof(struct CRGB));
            active = false;
        }
        segmentsOff.preStep();
        LED.showRGB((unsigned char *) leds, totem.nb_leds);
        segmentsOff.postStep();
        // Delay
        delay(totem.config_off.delay);
    }
}

void setConfiguration(CRGB* leds)
{
    if (digitalRead(PIN_SELECT_1) == HIGH)
    {
        setTotemTest1(leds);
    } else {
        setTotemTest2(leds);
    }
}

/**
 * Totem with square base
 */
void setTotemTest1(CRGB* leds)
{
    unsigned char nb_segment_on  = 2;
    unsigned int nb_leds        = 21;
    unsigned char nb_segment_off = 1;
    unsigned char segment_on_delay = 20;
    unsigned char segment_off_delay = 0;

    segments_on = (T_SegmentConfig *) malloc(nb_segment_on * sizeof(T_SegmentConfig));
    segments_on[0] = {leds, 10};
    segments_on[1] = {leds + 10, 11};
    
    effects_on = (T_EffectConfig *) malloc(nb_segment_on * sizeof(T_EffectConfig));
    effects_on[0] = {CWhite, UP, Wave};
    effects_on[1] = {CWhite, DOWN, Wave};
    
    segments_off = (T_SegmentConfig *) malloc(nb_segment_off * sizeof(T_SegmentConfig));
    segments_off[0] = {leds, 21};
    
    effects_off = (T_EffectConfig *) malloc(nb_segment_off * sizeof(T_EffectConfig));
    effects_off[0] = {CWhite, DOWN, Spark};

    totem = {
        LEDSTRIP_PIN,
        nb_leds,
        { nb_segment_on, segment_on_delay, segments_on, effects_on},
        { nb_segment_off, segment_off_delay, segments_off, effects_off }
    };
}

/**
 * Totem with square base
 */
void setTotemTest2(CRGB* leds)
{
    unsigned char nb_segment_on  = 2;
    unsigned int nb_leds        = 21;
    unsigned char nb_segment_off = 1;
    unsigned char segment_on_delay = 20;
    unsigned char segment_off_delay = 0;

    segments_on = (T_SegmentConfig *) malloc(nb_segment_on * sizeof(T_SegmentConfig));
    segments_on[0] = {leds, 10};
    segments_on[1] = {leds + 10, 11};
    
    effects_on = (T_EffectConfig *) malloc(nb_segment_on * sizeof(T_EffectConfig));
    effects_on[0] = {CWhite, DOWN, Wave};
    effects_on[1] = {CWhite, UP, Wave};
    
    segments_off = (T_SegmentConfig *) malloc(nb_segment_off * sizeof(T_SegmentConfig));
    segments_off[0] = {leds, 21};
    
    effects_off = (T_EffectConfig *) malloc(nb_segment_off * sizeof(T_EffectConfig));
    effects_off[0] = {CWhite, DOWN, Wave};

    totem = {
        LEDSTRIP_PIN,
        nb_leds,
        { nb_segment_on, segment_on_delay, segments_on, effects_on},
        { nb_segment_off, segment_off_delay, segments_off, effects_off }
    };
}

/**
 * Totem with square base
 */
void setTotemMounrning(CRGB* leds)
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
