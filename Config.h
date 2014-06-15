/**
 * Configuration file for project Temple
 *
 * @author : Jeckel <jeckel@jeckel.fr>
 */

// HC-SR04 Sensor
#define TRIGGER_PIN       9
#define ECHO_PIN          8

// PIR Sensor
#define PIR_FRONT_PIN     3
#define PIR_BACK_PIN      2
#define PIR_LOCK_DURATION 5000

// LED Strip
#define LEDSTRIP_PIN      6
#define NUM_LEDS          360
#define NB_SEGMENT        2
#define NB_SEGMENT_OFF    1

#define PIN_SELECT_1      4
#define PIN_SELECT_2      5

T_SegmentConfig* segments_on;
T_EffectConfig* effects_on;
T_SegmentConfig* segments_off;
T_EffectConfig* effects_off;


