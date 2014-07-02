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

typedef struct T_TotemConfig {
    uint16_t                  nb_leds;
    T_SegmentCollectionConfig config_on;
    T_SegmentCollectionConfig config_off;
    uint8_t                   i2c_port;
};

template <uint8_t DATA_PIN>
class Totem {
        /* properties */
    public:
        uint16_t nb_leds = 0;
        T_SegmentCollectionConfig config_on;
        T_SegmentCollectionConfig config_off;
        struct CRGB *leds;
        TM1809Controller800Mhz<DATA_PIN> LED;
    protected:
        E_TOTEM_MODE      mode = SLEEPING;
        SegmentCollection segments;
        SegmentCollection segmentsOff;
        T_TotemConfig     _totemConfig;
        
        /* methods */
    public:
        Totem() {};
        Totem(uint16_t nb_leds): nb_leds(nb_leds)
        {
            leds = (struct CRGB *) malloc(nb_leds * sizeof(struct CRGB));
            segments.setLeds(leds);
            segmentsOff.setLeds(leds);
        };
        Totem(T_TotemConfig config): 
            nb_leds(config.nb_leds), config_on(config.config_on), config_off(config.config_off), _totemConfig(config)
        {
            leds = (struct CRGB *) malloc(nb_leds * sizeof(struct CRGB));
            segments.setLeds(leds);
            segmentsOff.setLeds(leds);
        };
        
        /**
         * Init totem
         */
        void init()
        {
            Effect_Factory factory;
            for (unsigned int i = 0; i < config_on.size; i++) {
                segments.addSegment(new Segment(config_on.segments[i]));
            }
            for (unsigned int i = 0; i < config_off.size; i++) {
                segmentsOff.addSegment(new Segment(config_off.segments[i]));
            }
            segments.init();
            segmentsOff.init();
            LED.init();
        };
        
        /**
         * Set totem mode
         */
        void setMode(E_TOTEM_MODE new_mode)
        {
            if (mode != new_mode) {
                memset(leds, 0, nb_leds * sizeof(struct CRGB));
            }
            mode = new_mode;
        };
        
        E_TOTEM_MODE getMode()
        {
            return mode;
        };
        
        boolean isSleeping()
        {
            return mode == SLEEPING;
        };
        
        boolean isAwake()
        {
            return mode == AWAKE;
        };
        
        void setSleeping()
        {
            setMode(SLEEPING);
        };
        
        void setAwake()
        {
            setMode(AWAKE);
        };
        
        /**
         * Return activ segments collection
         */
        SegmentCollection getSegments()
        {
            if (isAwake()) {
                return segments;
            } else {
                return segmentsOff;
            }
        };    // getSegments
        
        /**
         * Change color on awake segments
         */
        void setColor(CRGB c)
        {
            if (isAwake()) {
                for(unsigned int i = 0; i < config_on.size; i++) {
                    segments.setSegmentColor(i, c);
                }
            }
        };    // setColor
        
        /**
         * Return delay for active segments collection
         */
        uint16_t getDelay()
        {
            if (isAwake()) {
                return config_on.delay;
            } else {
                return config_off.delay;
            }
        };    // getDelay
        
        /**
         * Animate to next step
         */
        void oneStep()
        {
            getSegments().preStep();
            LED.showRGB((unsigned char *) leds, nb_leds);
            getSegments().postStep();
            delay(getDelay());
        };
};  // class Totem


#endif /* TOTEM_H_ */
