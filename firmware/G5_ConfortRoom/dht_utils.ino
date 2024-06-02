#include "ConfortRoom.h"

// Configurar el sensor DHT
dht dhtSensor;

// Función para la lectura del sensor DHT22. El resultado para los parámetros de la temperatura
// y la humedad se guardan en los punteros que se pasan a la función.
void readDHTSensor(float* temperature, float* humidity) {
  // Configuración de las variables locales necesarias para la lectura
  // float temp = dhtSensor.readTemperature(); // Temperatura
  // float hum = dhtSensor.readHumidity(); // Humedad

  // Lectura del sensor, la función read necesita del PIN del DHT para la lectura. Los resultados
  // se guardan en la propia variable. En caso de error, no hay lectura, por lo que se muestra el
  // error en el Serial y se termina la ejecución de la función.
  int status = dhtSensor.read11(DHT_SENSOR_PIN);
  if (status != DHTLIB_OK) {
    Serial.println("Error reading from DHT sensor.");
    return;
  }

  // Se guardan los valores devueltos por la función byte en los punteros introducidos en la
  // función.
  *temperature = dhtSensor.temperature;
  *humidity = dhtSensor.humidity;
}
