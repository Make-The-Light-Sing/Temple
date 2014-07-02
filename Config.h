/**
 * Configuration file for project Temple
 *
 * @author : Jeckel <jeckel@jeckel.fr>
 */

#include "Totem.h"

// HC-SR04 Sensor
#define TRIGGER_PIN       4
#define ECHO_PIN          5

// PIR Sensor
#define PIR_FRONT_PIN     3
#define PIR_BACK_PIN      2
#define PIR_LOCK_DURATION 5000

// LED Strip
#define LEDSTRIP_PIN      6

/**
 * Test configuration with 21 leds
 */
#define TOTEM_TEST 0
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
 * Bridge : 30-31
 */
#define TOTEM_MOURNING 31
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
        .delay = 0,
        .segments = config_mourning_on
    },
    .config_off = {
        .size = 4,
        .delay = 0,
        .segments = config_mourning_off
    },
    .i2c_port = TOTEM_MOURNING
};


/**
 * Totem 2 : Trance inductind electronic multifrequency polysemous light Emitter
 * Shortname : Techno
 * Building with triangle base.
 * Color : outside : grey, green, red, inside : white, yellow
 * 3 strips of 90 leds each
 * Bridge : 32-33
 */
#define TOTEM_TECHNO 33
T_SegmentConfig config_techno_on[4] = {
    {0, 90, {CWhite, DOWN, Wave}},
    {90, 90, {CWhite, UP, Wave}},
    {180, 90, {CWhite, DOWN, Wave}}
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
    },
    .i2c_port = TOTEM_TECHNO
};

/**
 * Totem 3 :
 * Shortname : Meditation
 * One column with plates
 * Bridges : 34-35
 */
#define TOTEM_MEDITATION 35

/**
 * Totem 4 :
 * Shortname : Ecstasy
 * The claw
 * Bridges : 36-37
 */
#define TOTEM_ECSTASY    37
T_SegmentConfig config_ecstasy_on[4] = {
    {0, 93, {CWhite, DOWN, Wave}},
    {93, 93, {CWhite, UP, Wave}},
    {186, 105, {CWhite, DOWN, Wave}}
};
T_SegmentConfig config_ecstasy_off[4] = {
    {0, 93, {CWhite, UP, Spark}},
    {93, 93, {CWhite, UP, Spark}},
    {186, 105, {CWhite, UP, Spark}}
};
T_TotemConfig config_ecstasy = {
    .nb_leds = 291,
    .config_on = {
        .size = 3,
        .delay = 10,
        .segments = config_ecstasy_on
    },
    .config_off = {
        .size = 3,
        .delay = 0,
        .segments = config_ecstasy_off
    },
    .i2c_port = TOTEM_ECSTASY
};


/**
 * Pyramid, located in the center, no sensor on this one, use sensor from other totem
 * Bridge : 38-39
 */
#define TOTEM_PYRAMID    39
T_SegmentConfig config_pyramid_on[1] = {
    {0, 21, {CWhite, UP, Rainbow}}
};
T_SegmentConfig config_pyramid_off[1] = {
    {0, 21, {CWhite, DOWN, Spark}}
};
T_TotemConfig config_pyramid = {
    .nb_leds = 21,
    .config_on = {
        .size = 1,
        .delay = 10,
        .segments = config_pyramid_on
    },
    .config_off = {
        .size = 1,
        .delay = 0,
        .segments = config_pyramid_off
    },
    .i2c_port = 0        // ===> Should be master
};

// */
