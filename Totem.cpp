/*
 * Totem.cpp
 *
 *  Created on: 15 june 2014
 *      Author: jeckel
 */

#include "Totem.h"


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
