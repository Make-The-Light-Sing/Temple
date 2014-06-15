/*
 * Totem.h
 *
 * Created on : 15 june 2014
 *     Author : Jeckel <jeckel@jeckel.fr>
 */

#ifndef TOTEM_H_
#define TOTEM_H_

#include <FastSPI_LED2.h>
#include <PIRSensor.h>
#include <HCSR04UltraSonic.h>
#include <Color.h>
#include <Segment.h>


typedef enum E_TOTEM_MODE {
    SLEEPING = 0,
    AWAKE    = 1
};

class Totem {
        /* properties */
    public:
        uint8_t  pin     = 6;
        uint16_t nb_leds = 0;
        T_SegmentCollectionConfig config_on;
        T_SegmentCollectionConfig config_off;
        struct CRGB *leds;
    protected:
        E_TOTEM_MODE      mode = SLEEPING;
        SegmentCollection segments;
        SegmentCollection segmentsOff;        
        
        /* methods */
    public:
        Totem() {};
        Totem(uint8_t pin, uint16_t nb_leds): pin(pin), nb_leds(nb_leds) { leds = (struct CRGB *) malloc(nb_leds * sizeof(struct CRGB)); };
        void         init();
        void         setMode(E_TOTEM_MODE new_mode);
        E_TOTEM_MODE getMode() { return mode; };
        boolean      isSleeping() { return mode == SLEEPING; };
        boolean      isAwake() { return mode == AWAKE; };
        void         setSleeping() { setMode(SLEEPING); };
        void         setAwake() { setMode(AWAKE); };
        SegmentCollection getSegments();
        void         setColor(CRGB c);
        uint16_t     getDelay();
};  // class Totem


#endif /* TOTEM_H_ */
