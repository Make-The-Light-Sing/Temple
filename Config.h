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
    {0, 5, {CWhite, UP, Wave}},
    {5, 10, {CWhite, UP, Spark}},
    {15, 6, {CWhite, DOWN, Color_Chase}}
};
T_SegmentConfig config_test_off[1] = {
    {0, 21, {CWhite, UP, Spark}}
};
T_TotemConfig config_test = {
    .nb_leds = 21,
    .config_on = {
        .size = 3,
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
 * Mourning totem configuration
 * Configuration of the Mourning Totem, the one with the square base
 * 4 strip of 90 leds each
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
        .delay = 20,
        .segments = config_mourning_on
    },
    .config_off = {
        .size = 4,
        .delay = 0,
        .segments = config_mourning_off
    }
};

// */
