/**
 * Configuration file for project Temple
 *
 * @author : Jeckel <jeckel@jeckel.fr>
 */

#include "Totem.h"

// HC-SR04 Sensor
#define TRIGGER_PIN       9
#define ECHO_PIN          8

// PIR Sensor
#define PIR_FRONT_PIN     3
#define PIR_BACK_PIN      2
#define PIR_LOCK_DURATION 5000

// LED Strip
#define LEDSTRIP_PIN      6

/**
 * Test configuration with 21 leds
 */
T_SegmentConfig config_test_on[3] = {
    {0, 10, {CWhite, UP, Wave}},
    {10, 11, {CWhite, DOWN, Color_Chase}}
};
T_SegmentConfig config_test_off[1] = {
    {0, 21, {CWhite, UP, Spark}}
};
T_TotemConfig config_test = {
    .nb_leds = 21,
    .config_on = {
        .size = 2,
        .delay = 20,
        .segments = config_test_on
    },
    .config_off = {
        .size = 1,
        .delay = 0,
        .segments = config_test_off
    }
};


/**
 * Totem 1 : Temple of endlessly mourning the poisoning life emptiness
 * Shortname : Mourning
 * Building with square base.
 * Color : outside : dark gray / blue, inside : green, maroon
 * 4 strips of 90 leds each
 */
T_SegmentConfig config_mourning_on[4] = {
    {0, 90, {CWhite, UP, Wave}},
    {90, 90, {CWhite, DOWN, Wave}},
    {180, 90, {CWhite, UP, Wave}},
    {270, 90, {CWhite, DOWN, Wave}}
};
T_SegmentConfig config_mourning_off[4] = {
    {0, 90, {CWhite, UP, Spark}},
    {90, 90, {CWhite, UP, Spark}},
    {180, 90, {CWhite, UP, Spark}},
    {270, 90, {CWhite, UP, Spark}}
};
T_TotemConfig config_mourning = {
    .nb_leds = 360,
    .config_on = {
        .size = 4,
        .delay = 10,
        .segments = config_mourning_on
    },
    .config_off = {
        .size = 4,
        .delay = 0,
        .segments = config_mourning_off
    }
};


/**
 * Totem 2 : Trance inductind electronic multifrequency polysemous light Emitter
 * Shortname : Techno
 * Building with triangle base.
 * Color : outside : grey, green, red, inside : white, yellow
 * 3 strips of 90 leds each
 */
T_SegmentConfig config_techno_on[4] = {
    {0, 90, {CWhite, UP, Wave}},
    {90, 90, {CWhite, DOWN, Wave}},
    {180, 90, {CWhite, UP, Wave}}
};
T_SegmentConfig config_techno_off[4] = {
    {0, 90, {CWhite, UP, Spark}},
    {90, 90, {CWhite, UP, Spark}},
    {180, 90, {CWhite, UP, Spark}}
};
T_TotemConfig config_techno = {
    .nb_leds = 270,
    .config_on = {
        .size = 3,
        .delay = 10,
        .segments = config_techno_on
    },
    .config_off = {
        .size = 3,
        .delay = 0,
        .segments = config_techno_off
    }
};

// */
