/*
 * Totem.h
 *
 * Created on : 15 june 2014
 *     Author : Jeckel <jeckel@jeckel.fr>
 */

#ifndef TOTEM_H_
#define TOTEM_H_

class Totem {
        /* properties */
    public:
        uint8_t  pin     = 6;
        uint16_t nb_leds = 0;
        T_SegmentCollectionConfig config_on;
        T_SegmentCollectionConfig config_off;
        struct CRGB *leds;
        
        /* methods */
    public:
        Totem() {};
        Totem(uint8_t pin, uint16_t nb_leds): pin(pin), nb_leds(nb_leds) { leds = (struct CRGB *) malloc(nb_leds * sizeof(struct CRGB)); };
};  // class Totem


#endif /* TOTEM_H_ */
