#include "ConfortRoom.h"

// Configuración del pin de lectura del LM35
void setupLM35Sensor() {
  pinMode(LM35_PIN, INPUT);
}

// Funcion que realiza la lectura del sensor LM35 y convierte el valor analógico
// leido en el pin en grados Celsius
float readLM35Sensor() {
  const float maxV = 5000;                 // Voltage maximo asociada a la lectura analogica (mV)
  int analogValue = analogRead(LM35_PIN);  // Lectura del pin

  float mvOut = ((float)analogValue * maxV) / 1023.;  // Conversion a mV
  float temp = mvOut / 10;                            // Por cada 10 mV -> 1 grado
  return temp;
}
