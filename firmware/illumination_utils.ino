#include "ConfortRoom.h"

// Constantes para la transfomación de tensión a Lux del LDR
const float GAMMA = 0.7;
const float RL10 = 50;

// Configuración de los elementos de la iluminación
void setupIllumination() {
  // LDR
  pinMode(LDR_PIN, INPUT);
  // Led RGB
  pinMode(BLUE_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  // Sensor PIR
  pinMode(PIR_MOTION_PIN, INPUT);
}
// Función para la lectura del LDR, realiza la conversión a Lux
int readLDRSensor() {
  int ldrValue = analogRead(LDR_PIN);
  return analogValueToLux(ldrValue);
}
// Función para la lectura del sensor PIR de presencia, devuelve True en caso de
// detectar presencia
bool readMotionSensor() {
  int sensorVal = digitalRead(PIR_MOTION_PIN);
  return sensorVal == HIGH;
}

// Gestiona el LED RGB, que se encenderá en caso de que se detecte presencia y no 
// haya luz
void illuminationManagement(int ldrValue, bool isPresence) {
  // Solo se enciende el led en verde si hay poca luz y se detecta presencia
  if (isPresence) {
    if (ldrValue < LDR_THRESHOLD) {
      rgbLedColor(HIGH, LOW, HIGH);
    } else {
      rgbLedColor(LOW, LOW, LOW);
    }
  } else {
    rgbLedColor(LOW, LOW, LOW);
  }
}

// Funcion para encender el LED RGB
void rgbLedColor(int redValue, int greenValue, int blueValue) {
  digitalWrite(RED_LED_PIN, redValue);
  digitalWrite(GREEN_LED_PIN, greenValue);
  digitalWrite(BLUE_LED_PIN, blueValue);
}

// Convierte los valores analógicos del LDR a Lux - https://docs.wokwi.com/parts/wokwi-photoresistor-sensor
float analogValueToLux(int analogVal) {
  float voltage = (analogVal / (float)1024) * 5; // Valor analógico a voltage
  float ldrVoltage = 5 - voltage; // Valor del voltage en la LDR
  float ldrResistance = ldrVoltage/voltage * 10000; // Resistencia de la LDR
  float lux = pow(RL10 * 1e3 * pow(10, GAMMA) / ldrResistance, (1 / GAMMA));

  return lux;
}
