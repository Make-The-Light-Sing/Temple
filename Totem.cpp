/*
 * Totem.cpp
 *
 *  Created on: 15 june 2014
 *      Author: jeckel
 */

#include "Totem.h"

/**
 * Initialize Totem
 */
void Totem::init()
{
    Effect_Factory factory;
    for (unsigned int i = 0; i < config_on.size; i++) {
        segments.addSegment(new Segment(config_on.segments[i], factory.createEffect(config_on.effects[i])));
    }
    for (unsigned int i = 0; i < config_off.size; i++) {
        segmentsOff.addSegment(new Segment(config_off.segments[i], factory.createEffect(config_off.effects[i])));
    }
    segments.init();
    segmentsOff.init();
}   // init


/**
 * Switch totem mode
 */
void Totem::setMode(E_TOTEM_MODE new_mode)
{
    if (mode != new_mode) {
        memset(leds, 0, nb_leds * sizeof(struct CRGB));
    }
    mode = new_mode;
}   // setMode

/**
 * Return active segments collection
 */
SegmentCollection Totem::getSegments()
{
    if (isAwake()) {
        return segments;
    } else {
        return segmentsOff;
    }
}

/**
 * Define new color to actual totem
 */
void Totem::setColor(CRGB c)
{
    if (isAwake()) {
        for(unsigned int i = 0; i < config_on.size; i++) {
            segments.setSegmentColor(i, c);
        }
    }
}   // set Color

/**
 * Return delay for active segments collection
 */
uint16_t Totem::getDelay()
{
    if (isAwake()) {
        return config_on.delay;
    } else {
        return config_off.delay;
    }
}
