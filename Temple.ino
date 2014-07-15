#include <FastSPI_LED2.h>
#include <PIRSensor.h>
#include <HCSR04UltraSonic.h>
#include <Color.h>
#include <Segment.h>
#include "Config.h"
#include "Totem.h"
//#include <Wire.h>

//#define DEBUG

HCSR04UltraSonic HCSR04(TRIGGER_PIN, ECHO_PIN, 10000); // ==> Around 3m
PIRSensor        PIRFront(PIR_FRONT_PIN, PIR_LOCK_DURATION);
PIRSensor        PIRBack(PIR_BACK_PIN, PIR_LOCK_DURATION);

Totem<LEDSTRIP_PIN> totem;
uint8_t configId;
struct CRGB stripColor;


/**
 * Init
 */
void setup()
{
    configId = detectConfig(); 
    setConfig(configId);
    totem.init();
    
/*    uint8_t port = totem.getI2CPort();
    if (port == 0) {
        Wire.begin();
    } else {
        Wire.begin(port);
        Wire.onRequest(onRequestHandler);
    }*/
    totem.setAwake();
    stripColor = CGreen;
    
    #ifdef DEBUG
        Serial.begin(9600);
    #endif   
}

/**
 * Main loop
 */
void loop()
{
    if (configId != TOTEM_PYRAMID) {
        // Read distance from Sensor
        //int distance = HCSR04.readDistance();
        int distance = HCSR04.timing() >> 4;
        #ifdef DEBUG
            Serial.println(distance);
            if (PIRFront.triggered()) {
                Serial.println("Movement in front sensor");
            }
            if (PIRBack.triggered()) {
                Serial.println("Movement in back sensor");
            }
        #endif
            
        // Get CRGB value from index in an RGB wheel, index is the distance
        stripColor.Wheel(distance);
    }    
    
    //if (PIRFront.hasMovement() || PIRBack.hasMovement()) {
    if (getMovement()) {
        totem.setAwake();
        totem.setColor(stripColor);
    } else {
        totem.setSleeping();
    }
    totem.oneStep();
}

/**
 * Detect jumper to define which configuration to use 
 * 30-31 ==> Totem 1 : Mourning
 * 32-33 ==> Totem 2 : Techno
 * else ==> config test
 */
uint8_t detectConfig()
{
    #if defined(__AVR_ATmega2560__)
        pinMode(30, OUTPUT);    // Totem TOTEM_MOURNING
        pinMode(31, INPUT);
        pinMode(32, OUTPUT);    // Totem TOTEM_TECHNO
        pinMode(33, INPUT);
        pinMode(34, OUTPUT);    // Totem TOTEM_MEDITATION
        pinMode(35, INPUT);
        pinMode(36, OUTPUT);    // Totem TOTEM_ECSTASY
        pinMode(37, INPUT);
        pinMode(38, OUTPUT);    // pyramid
        pinMode(39, INPUT);
        digitalWrite(30, LOW);
        digitalWrite(31, HIGH);    // pull up
        digitalWrite(32, LOW);
        digitalWrite(33, HIGH);    // pull up
        digitalWrite(34, LOW);
        digitalWrite(35, HIGH);    // pull up
        digitalWrite(36, LOW);
        digitalWrite(37, HIGH);    // pull up
        digitalWrite(38, LOW);
        digitalWrite(39, HIGH);    // pull up
        
        if (digitalRead(31) == LOW) {
            return TOTEM_MOURNING;
        } else if (digitalRead(33) == LOW) {
            return TOTEM_TECHNO;
        } else if (digitalRead(35) == LOW) {
            return TOTEM_MEDITATION;
        } else if (digitalRead(37) == LOW) {
            return TOTEM_ECSTASY;
        } else if (digitalRead(39) == LOW) {
            return TOTEM_PYRAMID;
        }
        return TOTEM_TEST;
    #else
        pinMode(12, OUTPUT);    // Totem TOTEM_MEDITATION
        pinMode(13, INPUT);
        digitalWrite(12, LOW);
        digitalWrite(13, HIGH);    // pull up
        if (digitalRead(13) == LOW) {
            return TOTEM_MEDITATION;
        }
        return TOTEM_TEST;
    #endif
}


/**
 * Initialize configuration according to hardware detection
 */
void setConfig(uint8_t configId)
{
    switch(configId) {
        case TOTEM_MOURNING:
            totem = Totem<LEDSTRIP_PIN>(config_mourning);
            break;
        case TOTEM_TECHNO:
            totem = Totem<LEDSTRIP_PIN>(config_techno);
            break;
        case TOTEM_MEDITATION:
            totem = Totem<LEDSTRIP_PIN>(config_meditation);
            break;
        case TOTEM_ECSTASY:
            totem = Totem<LEDSTRIP_PIN>(config_ecstasy);
            break;
        case TOTEM_PYRAMID:
            totem = Totem<LEDSTRIP_PIN>(config_pyramid);
            break;
        case TOTEM_TEST:
        default:
            totem = Totem<LEDSTRIP_PIN>(config_test);
    }
}

/**
 * When master make a resquest, send actual color
 */
/*void onRequestHandler()
{
    //uint8_t buffer[1] = { PIRBack.hasMovement() ? 1 : 0 };
    uint8_t buffer[1] = { totem.isAwake() ? 1 : 0 };
//    Wire.write(buffer, 1);
}*/

/**
 * Check if given totem id is awake or not, using i2c channel
 */
boolean checkTotemAwake(int totemId)
{
    boolean awake = false;
/*    if (Wire.requestFrom(totemId, 1) == 1)
    {
        awake = (Wire.read() > 0);
    }*/
    return awake;
}

/**
 * Return if there is movement activating this totem
 */
boolean getMovement()
{
    static int lastTotem = TOTEM_MOURNING;
    static int lastMovement = 0;
    if (configId == TOTEM_PYRAMID) {
        /*switch(lastTotem) {
            case TOTEM_MOURNING :
                lastTotem = TOTEM_TECHNO;
                break;
            case TOTEM_TECHNO :
                lastTotem = TOTEM_MEDITATION;
                break;
            case TOTEM_MEDITATION :
                lastTotem = TOTEM_ECSTASY;
                break;
            case TOTEM_ECSTASY :
            default:
                lastTotem = TOTEM_MOURNING;
                break;
        }
        if (checkTotemAwake(lastTotem)) {
            lastMovement = 4;
        } else if (lastMovement > 0) {
            lastMovement --;
        }
        return (lastMovement > 0);*/
        return true;
            
        //return checkTotemAwake(TOTEM_TECHNO) && checkTotemAwake(TOTEM_ECSTASY);
        //return true;
    } else {
        return (PIRFront.hasMovement() || PIRBack.hasMovement());
    }
}
