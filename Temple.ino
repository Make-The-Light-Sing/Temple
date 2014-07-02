#include <FastSPI_LED2.h>
#include <PIRSensor.h>
#include <HCSR04UltraSonic.h>
#include <Color.h>
#include <Segment.h>
#include "Config.h"
#include "Totem.h"
#include <Wire.h>

#define DEBUG

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
    
    uint8_t port = totem.getI2CPort();
    if (port == 0) {
        Wire.begin();
    } else {
        Wire.begin(port);
        Wire.onRequest(onRequestHandler);
    }
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
    if (configId == TOTEM_PYRAMID) {
        if (Wire.requestFrom(TOTEM_MOURNING, 3) == 3)
        {
            stripColor.r = Wire.read();
            stripColor.g = Wire.read();
            stripColor.b = Wire.read();
        }
        totem.setColor(stripColor);
        totem.oneStep();
    } else {    
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
        
        if (PIRFront.hasMovement() || PIRBack.hasMovement()) {
            totem.setAwake();
            totem.setColor(stripColor);
        } else {
            totem.setSleeping();
        }
        totem.oneStep();
    }
}

/**
 * Detect jumper to define which configuration to use 
 * 30-31 ==> Totem 1 : Mourning
 * 32-33 ==> Totem 2 : Techno
 * else ==> config test
 */
uint8_t detectConfig()
{
    pinMode(30, OUTPUT);    // Totem 1
    pinMode(31, INPUT);
    pinMode(32, OUTPUT);    // Totem 2
    pinMode(33, INPUT);
    pinMode(34, OUTPUT);    // Totem 3
    pinMode(35, INPUT);
    pinMode(36, OUTPUT);    // Totem 4
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
void onRequestHandler()
{
    uint8_t buffer[3] = {stripColor.r, stripColor.g, stripColor.b};
    Wire.write(buffer, 3);
}
