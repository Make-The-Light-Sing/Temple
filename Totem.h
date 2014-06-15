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
        uint8_t pin;
        uint16_t nb_leds;
        T_SegmentCollectionConfig config_on;
        T_SegmentCollectionConfig config_off;
        
        /* methods*/
    public:
        Totem() {};
};  // class Totem


#endif /* TOTEM_H_ */
