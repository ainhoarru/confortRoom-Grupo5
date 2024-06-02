/*
  ConfortRoom.h - Constantes para el programa
*/

#ifndef ConfortRoom_h
#define ConfortRoom_h

// Definición de las librerias extra para los sensores
// Libreria para la LCD con bus I2C
#include <LiquidCrystal_I2C.h>
// Libreria para el uso de sensores DHT con Arduino
#include "dht.h"

// Definición de variables globales
// DHT
#define DHT_SENSOR_PIN 3
// LDR
#define LDR_PIN A0
#define LDR_THRESHOLD 10 // Valor asignado en lux al anochecer https://docs.wokwi.com/parts/wokwi-photoresistor-sensor
// LED RGB
#define BLUE_LED_PIN 11
#define GREEN_LED_PIN 12
#define RED_LED_PIN 13
// Boton
#define BUTTON_PIN 2
// Sensor PIR
#define PIR_MOTION_PIN 7

#endif
