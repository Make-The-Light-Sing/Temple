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

struct CRGB leds[NUM_LEDS];

T_SegmentConfig seg_config[NB_SEGMENT] = {
        { leds,       10},
        { leds + 10,  11},
    };

T_EffectConfig effect_config[NB_SEGMENT] = {
        { CRed,   DOWN, Pulse },
        { CBlue,  UP,   Wave },
};
