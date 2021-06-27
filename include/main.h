#include <Arduino.h>

#include <ESP8266WiFi.h>

#include <BlynkSimpleEsp8266.h>

#include "ServoEasing.h"

ServoEasing Servo;


// Macro definition.

#define BLYNK_PRINT Serial


#define R_1       D4 
#define R_2       D3  
#define L_1       D1
#define L_2       D2

#define minSpeed 400
#define maxSpeed 1024


#define Rudder       D8