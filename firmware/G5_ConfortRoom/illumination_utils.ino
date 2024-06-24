#include "ConfortRoom.h"

// Constantes para la transfomación de tensión a Lux del LDR
const float GAMMA = 0.7;
const float RL10 = 50;

// Objetos para la libreria Fuzzy
Fuzzy *fuzzyIllumination = new Fuzzy();

// Definimos las variables FuzzySet para la logica Fuzzy
// Presencia
FuzzySet* noPresenceInput = new FuzzySet(0, 0, 0, 0); // Representa 'false'
FuzzySet* presenceInput = new FuzzySet(HIGH, HIGH, HIGH, HIGH); // Representa 'true'

// Illuminación
FuzzySet* dark = new FuzzySet(0, 0, 10, 50);
FuzzySet* day = new FuzzySet(30, 100, 500, 1000);

// Definimos las variables FuzzySet para los outputs
// Led
FuzzySet* minLight = new FuzzySet(0, 0, 0, 0);
FuzzySet* maxLight = new FuzzySet(600, 800, 1023, 1023);
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

  // Presencia
  FuzzyInput* presence = new FuzzyInput(1);
  presence->addFuzzySet(noPresenceInput);
  presence->addFuzzySet(presenceInput);
  fuzzyIllumination->addFuzzyInput(presence);
  // Illuminación
  FuzzyInput* light = new FuzzyInput(2);
  light->addFuzzySet(dark);
  light->addFuzzySet(day);
  fuzzyIllumination->addFuzzyInput(light);
  // Fuzzy outputs
  // Nuestro output es el led
  FuzzyOutput* ledLight = new FuzzyOutput(1);
  ledLight->addFuzzySet(minLight);
  ledLight->addFuzzySet(maxLight);
  fuzzyIllumination->addFuzzyOutput(ledLight);

  // Definimos las reglas de Fuzzy para el control
  // Regla 1: si la es de noche y se detecta presencia -> se enciende el led
  FuzzyRuleAntecedent* ifNightAndPresence = new FuzzyRuleAntecedent();
  ifNightAndPresence->joinWithAND(dark, presenceInput);
  // Creamos la consecuencia/accion de encender el led
  FuzzyRuleConsequent* thenLedOn = new FuzzyRuleConsequent();
  thenLedOn->addOutput(maxLight);
  FuzzyRule* rule1 = new FuzzyRule(1, ifNightAndPresence, thenLedOn);
  fuzzyIllumination->addFuzzyRule(rule1);
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
  // Incluimos los inputs a la libreria de la logica Fuzzy
  fuzzyIllumination->setInput(1, isPresence);
  fuzzyIllumination->setInput(2, ldrValue);
  // Ejecutamos el fuzzify() para ejecutar el algoritmo
  fuzzyIllumination->fuzzify();
  float ledValue = fuzzyIllumination->defuzzify(1);
  rgbLedColor(ledValue, 0, ledValue);

  Serial.print("LED->");
  Serial.println(ledValue);
}
// Funcion para encender el LED RGB
void rgbLedColor(int redValue, int greenValue, int blueValue) {
  analogWrite(RED_LED_PIN, redValue);
  analogWrite(GREEN_LED_PIN, greenValue);
  analogWrite(BLUE_LED_PIN, blueValue);
}

// Convierte los valores analógicos del LDR a Lux - https://docs.wokwi.com/parts/wokwi-photoresistor-sensor
float analogValueToLux(int analogVal) {
  float voltage = (analogVal / (float)1024) * 5;       // Valor analógico a voltage
  float ldrVoltage = 5 - voltage;                      // Valor del voltage en la LDR
  float ldrResistance = ldrVoltage / voltage * 10000;  // Resistencia de la LDR
  float lux = pow(RL10 * 1e3 * pow(10, GAMMA) / ldrResistance, (1 / GAMMA));

  return lux;
}
