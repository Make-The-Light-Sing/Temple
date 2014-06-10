/**
 * Configuration file for project Temple
 *
 * @author : Jeckel <jeckel@jeckel.fr>
 */

#include <Color.h>

// RGB Test led
#define LED_RED           44
#define LED_GREEN         45
#define LED_BLUE          46

// HC-SR04 Sensor
#define TRIGGER_PIN       9
#define ECHO_PIN          8

// PIR Sensor
#define PIR_FRONT_PIN     3
#define PIR_BACK_PIN      2
#define PIR_LOCK_DURATION 5000

// LED Strip
#define LEDSTRIP_PIN      6
#define NUM_LEDS          21
#define NB_SEGMENT        2
#define NB_SEGMENT_OFF    1

#define PIN_SELECT_1      4
#define PIN_SELECT_2      5

struct CRGB leds[NUM_LEDS];

typedef struct T_Totem {
    unsigned char pin;
    unsigned char nb_leds;
    T_SegmentCollectionConfig config_on;
    T_SegmentCollectionConfig config_off;
};

T_SegmentConfig* segments_on;
T_EffectConfig* effects_on;
T_SegmentConfig* segments_off;
T_EffectConfig* effects_off;

T_Totem totem = {
    LEDSTRIP_PIN,
    21,
    { 2, segments_on, effects_on},
    { 1, segments_off, effects_off }
};

