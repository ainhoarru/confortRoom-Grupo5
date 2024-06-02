#include "ConfortRoom.h"

// Definicion de la variable del motor
Servo servoMotor;

// Definición de variables para la apertura/cerrado del servomotor
unsigned long nightVentStartTime = 0;
unsigned long nightVentFinishTime = 0;
bool nightVentActive = false;
bool nightVentDone = false;

// Configuración del pin de lectura del Servo Motor
void servoInit() {
  servoMotor.attach(SERVO_PIN);
}

// Funcion para la gestion de las posiciones del ServoMotor
void servoManage(float temperature, float tempExterior, float tempObjetivo) {

  // Evaluar condición de emergencia
  if (temperature > TEMPERATURE_EMERGENCY_THRESHOLD && humidity > HUMIDITY_EMERGENCY_THRESHOLD) {
    // Si la temperatura interior supera el umbral de emergencia y la humedad interior también supera su umbral de emergencia
    servoMotor.write(90);  // Abrir la ventana completamente (servomotor a 90 grados)
    Serial.println("EMERGENCIA");

  } else {
    // Si no hay una condición de emergencia, evaluar la ventilación nocturna automática
    if (illuminationVal < NIGHT_LIGHT_THRESHOLD && !presence) {
      // Si el valor del sensor de luz indica noche y no hay presencia detectada
      if (!nightVentDone) {
        // Si la ventilación nocturna no se ha realizado en esta hora
        if (!nightVentActive) {
          // Si la ventilación nocturna no está activa, iniciar el proceso
          nightVentActive = true;         // Marcar la ventilación nocturna como activa
          nightVentStartTime = millis();  // Guardar el tiempo de inicio de la ventilación nocturna
          servoMotor.write(90);           // Abrir la ventana completamente (servomotor a 90 grados)
          Serial.println("Ventilacion nocturna: ventana abierta");

        } else if (millis() - nightVentStartTime >= 30000) {  // Si han pasado 5 minutos desde el inicio de la ventilación nocturna (300000 milisegundos = 5 minutos)
          nightVentActive = false;                            // Marcar la ventilación nocturna como inactiva
          nightVentDone = true;                               // Marcar la ventilación nocturna como realizada
          servoMotor.write(0);                                // Cerrar la ventana completamente (servomotor a 0 grados)
          Serial.println("Ventilacion nocturna ACABADA: ventana cerrada");
          nightVentFinishTime = millis();
        }
      } else {
        if (millis() - nightVentFinishTime >= 3600000) {  // Forzamos un tiempo de espera de 1 hora entre ciclos de ventilación
          // Si no es de noche o hay presencia detectada, reiniciar la bandera de ventilación nocturna realizada
          nightVentDone = false;  // Resetear la bandera para la siguiente hora
        }
      }
    } else {
      servoMotor.write(0);      // Cerrar la ventana completamente (servomotor a 0 grados)
      nightVentActive = false;  // Marcar la ventilación nocturna como inactiva
    }

    // Evaluar ventilación por temperatura y humedad si no hay ventilación nocturna activa
    if (!nightVentActive) {
      // Si la ventilación nocturna no está activa, evaluar la ventilación combinada por temperatura y humedad
      if (temperature > TEMPERATURE_THRESHOLD && tempExterior < temperature && humidity < HUMIDITY_THRESHOLD) {
        // Si la temperatura interior es mayor que el umbral, la temperatura exterior es menor que la interior, y la humedad interior es menor que el umbral
        servoMotor.write(90);  // Abrir la ventana completamente (servomotor a 90 grados)
        Serial.println("ABIERTO");

      } else {
        // Si no se cumplen las condiciones para abrir la ventana
        servoMotor.write(0);  // Cerrar la ventana completamente (servomotor a 0 grados)
        Serial.println("CERRADO");
      }
    }
  }
}