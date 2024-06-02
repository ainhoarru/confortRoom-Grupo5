// Author: Grupo 5
// Equipos e Instrumentacion Electronica - Master Telecomunicaciones
// UNIR
#include "ConfortRoom.h"

// Variables y flags
int illuminationVal;
float temperature = 0;
float tempExterior = 0;
float tempObjetivo = 23;
float humidity = 0;
const unsigned long lcdOnTime = 5000;  // Tiempo en el que el LCD estará encendido en ms
unsigned long lcdStartTime;
bool lcdOn = false;
bool presence = false;

// Configuración de la placa
void setup() {
  initLCD();            // Setup de la pantalla LCD
  setupIllumination();  // Setup de los elementos para la iluminación
  setupLM35Sensor();    // Configurar el sensor LM35
  servoInit();          // Configurar el servomotor
  Serial.begin(9600);   // Configurar el serial
  Serial.println("Welcome to the room confort system! All sensors set up!");
}

// Codigo principal, se ejecuta cada segundo
void loop() {
  // Lectura de los valores de la temperatura y humedad ambiental del sensor DHT
  // Los valores de temperatura y humedad se pasan como punteros para su acceso desde
  // la función loop (ya que la función solo puede devolver un único valor).
  readDHTSensor(&temperature, &humidity);

  // Lectura del valor de la iluminación del sensor LDR
  illuminationVal = readLDRSensor();

  // Lectura del sensor de presencia PIR
  presence = readMotionSensor();

  // Gestión de la iluminación
  illuminationManagement(illuminationVal, presence);

  // Gestión del sensor de temperatura exterior
  tempExterior = readLM35Sensor();

  // Gestión del Servomotor
  servoManage(temperature, tempExterior, tempObjetivo);

  // La presencia determinará cuando se enciende el LCD, y una vez encendido se mantendrá
  // durante 30 segundos. En caso de detectar una presencia otra vez, el contador se
  // reiniciará. El detector de presencia simula la cercanía de un usuario a la pantalla,
  // además de así evitar que el LCD se deje encendido accidentalmente.
  if (presence && !lcdOn) {
    turnLCDOn();
    lcdOn = true;
    // Muestra los valores definidos en la LCD
    printLCDValues(temperature, humidity, illuminationVal, presence);
    lcdStartTime = millis();
  } else if (presence && lcdOn) {
    printLCDValues(temperature, humidity, illuminationVal, presence);
    lcdStartTime = millis();
  } else if (lcdOn) {
    // En caso de que se haya llegado al tiempo maximo de display, se apaga el LCD.
    printLCDValues(temperature, humidity, illuminationVal, presence);
    if (millis() - lcdStartTime >= lcdOnTime) {
      turnLCDOff();
      lcdOn = false;
    }
  }
  // Esperar 1s
  delay(1000);
}
