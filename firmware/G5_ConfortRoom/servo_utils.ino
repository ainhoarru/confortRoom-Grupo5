#include "ConfortRoom.h"

// Objeto para el control del servo
Servo servoMotor;

// Objetos para la libreria Fuzzy
Fuzzy *fuzzyWindow = new Fuzzy();

// Definimos las variables FuzzySet para la logica Fuzzy
// Temperatura
FuzzySet* cold = new FuzzySet(0, 0, 10, 20);
FuzzySet* warm = new FuzzySet(15, 20, 25, 30);
FuzzySet* hot = new FuzzySet(25, 35, 40, 40);

// TemperaturaExt
FuzzySet* coldExt = new FuzzySet(0, 0, 10, 20);
FuzzySet* warmExt = new FuzzySet(15, 20, 20, 20);
FuzzySet* hotExt = new FuzzySet(25, 35, 40, 40);

// Humedad
FuzzySet* dry = new FuzzySet(0, 0, 60, 70);
FuzzySet* humid = new FuzzySet(60, 70, 80, 80);

// Definimos las variables FuzzySet para los outputs
// Servo
FuzzySet* minPosition = new FuzzySet(10, 20, 20, 30);
FuzzySet* midPosition = new FuzzySet(70, 90, 90, 110);
FuzzySet* maxPosition = new FuzzySet(110, 180, 180, 180);

void servoInit() {
  servoMotor.attach(SERVO_PIN);
  // Fuzzy inputs
  // Temperatura
  FuzzyInput* temperature = new FuzzyInput(1);
  temperature->addFuzzySet(cold);
  temperature->addFuzzySet(warm);
  temperature->addFuzzySet(hot);
  fuzzyWindow->addFuzzyInput(temperature);
  // Temperatura exterior
  FuzzyInput* temperatureExt = new FuzzyInput(2);
  temperatureExt->addFuzzySet(coldExt);
  temperatureExt->addFuzzySet(warmExt);
  temperatureExt->addFuzzySet(hotExt);
  fuzzyWindow->addFuzzyInput(temperatureExt);
  // Humedad
  FuzzyInput* humidity = new FuzzyInput(3);
  humidity->addFuzzySet(dry);
  humidity->addFuzzySet(humid);
  fuzzyWindow->addFuzzyInput(humidity);

  // Fuzzy outputs
  // Nuestro output es el servo motor
  FuzzyOutput* servoAngle = new FuzzyOutput(1);
  servoAngle->addFuzzySet(minPosition);
  servoAngle->addFuzzySet(midPosition);
  servoAngle->addFuzzySet(maxPosition);
  fuzzyWindow->addFuzzyOutput(servoAngle);

  // Definimos las reglas de Fuzzy para el control
  // Regla 1: si la temperatura o la humedad es alta, abrir la ventana (servo)
  FuzzyRuleAntecedent* ifTempHighAndHumidityHigh = new FuzzyRuleAntecedent();
  ifTempHighAndHumidityHigh->joinWithOR(hot, humid);
  // Creamos la consecuencia/accion de abrir la ventana del todo
  FuzzyRuleConsequent* thenOpenWindow = new FuzzyRuleConsequent();
  thenOpenWindow->addOutput(maxPosition);
  FuzzyRule* rule1 = new FuzzyRule(1, ifTempHighAndHumidityHigh, thenOpenWindow);
  fuzzyWindow->addFuzzyRule(rule1);
  // Regla 2: si es de noche, la temperatura interior es menor a la exterior -> abrir la ventana en ventilación (servo)
  FuzzyRuleAntecedent* ifTempHighExtTempLow = new FuzzyRuleAntecedent();
  ifTempHighExtTempLow->joinWithAND(warm, warmExt);
  // Creamos la consecuencia/accion de abrir la ventana en ventilacion
  FuzzyRuleConsequent* thenOpenWindowVentilation = new FuzzyRuleConsequent();
  thenOpenWindowVentilation->addOutput(minPosition);
  FuzzyRule* rule2 = new FuzzyRule(2, ifTempHighExtTempLow, thenOpenWindowVentilation);
  fuzzyWindow->addFuzzyRule(rule2);
}

void servoManage(float temperature, float tempExterior, bool presence, float humidity, int illuminationVal) {
  // Incluimos los inputs a la libreria de la logica Fuzzy
  fuzzyWindow->setInput(1, temperature);
  fuzzyWindow->setInput(2, tempExterior);
  fuzzyWindow->setInput(3, humidity);
  // Ejecutamos el fuzzify() para ejecutar el algoritmo
  fuzzyWindow->fuzzify();

  // Obtenemos la posicion del servo mediante la funcion defuzzify y obteniendo el output 1
  float servoPosition = fuzzyWindow->defuzzify(1);

  // Aplicamos el valor obtenido en la posicion del servo
  servoMotor.write(servoPosition);
  Serial.print("Servo->");
  Serial.println(servoPosition);
}
