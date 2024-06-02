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
// Libreria para el uso del Servo Motor
#include <Servo.h>

// Definición de variables globales
// DHT
#define DHT_SENSOR_PIN 3
// LDR
#define LDR_PIN A0
#define LDR_THRESHOLD 10  // Valor asignado en lux al anochecer https://docs.wokwi.com/parts/wokwi-photoresistor-sensor
// LED RGB
#define BLUE_LED_PIN 11
#define GREEN_LED_PIN 12
#define RED_LED_PIN 13
// Boton
#define BUTTON_PIN 2
// Sensor PIR
#define PIR_MOTION_PIN 7
// Servo
#define SERVO_PIN 9
// LM35
#define LM35_PIN A1
// Umbrales para la gestion del ServoMotor
#define TEMPERATURE_THRESHOLD 25
#define TEMPERATURE_EMERGENCY_THRESHOLD 30
#define HUMIDITY_THRESHOLD 60
#define HUMIDITY_EMERGENCY_THRESHOLD 70
#define NIGHT_LIGHT_THRESHOLD 10  // Umbral para definir la noche
#endif
