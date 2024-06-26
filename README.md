# Confort Room - Grupo 5

Confort Room es el proyecto de simulación de la monitorización de una habitación inteligente desarrollado en el contexto de la asignatura de Equipos e Instrumentación Electrónica del Máster en Ingeniería de Telecomunicación impartido en la UNIR.

Sensores para la medición de la temperatura ambiente, humedad y luz se combinan con una placa Arduino Uno, que permite la visualización de las lecturas mediante y el control sobre distintos actuadores de forma que se consigue un ambiente óptimo en la habitación la cual se aplica.

## Características

A continuación se listan los elementos incluidos en el proyecto

- Placa Keystudio KS0486 PLUS para el desarrollo, basada en la placa Arduino UNO R3.
- Placa de pruebas sin soldadura KS0343.
- Keystudio módulo KS0061 1602 I2C, display LCD de 16x2 con fondo azul y luz blanca de fondo para la representación de los datos.
- Cable USB-C para la programación de la placa.
- 1 led RGB para la iluminación del entorno.
- 1 sensor LDR para la medición de la luz ambiente.
- Sensor DHT11 para la medición de la temperatura y la humedad ambiente.
- Sensor de movimiento PIR KS0052 de Keyestudio.
- Servo motor KS0194 de Keyestudio para el control de la posición de la ventana de la habitación.


## Funcionamiento

El dispositivo cuenta con un display LCD que permite la visualización de 4 datos distintos:

- Temperatura (˚C)
- Humedad (%)
- Luz (Lux)
- Movimiento/Presencia

Este display solo se encenderá y mostrará la información en caso de que detecte movimiento en la habitación. Cuenta con un botón que permite controlar que datos se muestran, dado que se exiben 2 datos simultaneamente: temperatura y humedad, o luz y detección de movimiento.

Además, el sistema permite el control sobre dos elementos en función de las lecturas de los sensores
- Mediante un led se gestiona la luz de la habitación. Dicha luz se encenderá en caso de detección de movimiento y la luz ambiental se encuentre por debajo del umbral establecido.
- Mediante un servo motor se gestiona la posición de una ventana, que permite la ventilación de la habitación dependiendo de las lecturas de luz, temperatura y humedad del entorno.


### Demo

Se ha grabado un video con la demo del codigo con el circuito físico. Haz click en la siguiente imagen para acceder al video!

[![Demo](./doc/img/demo_circuit.png)](https://youtu.be/6NCw_0ztRkU)


## Esquema de conexiones

![Esquema](./doc/img/esquema.jpeg)

## Componentes

A contiuación se listarán los componentes necesarios para la realización de la simulación. 

### Arduino UNO

![Arduino_UNO](https://upload.wikimedia.org/wikipedia/commons/5/59/Arduino_uno.png)

Se trata de una placa de microcontrolador con alimentada por el chip ATmega328p, que tiene 32kB de memoria de proograma Flash, 2kB de SRAM y 1kB de EEPROM. Esta incluye pines y leds distribuidos de la siguiente manera:
   - Tiene pines GPIO digitales del 0 al 13. Los pines desde el A0 hasta el A5 funcionan además como entrada analógica. Los pines digitales 3, 5, 6, 9, 10 y 11 tienen soporte de hardware PWM.
   - Tiene tres pines de tierra, GND.1, GND.2 y GND.3
   - Los pines VIN/5V están conectados a la fuente de alimentación positiva
   - Los pines 3.3V / IOREF / AREF / RESET no están disponibles en la simulación

La placa incluye cuatro LEDs:
   - Condujo I - conectado al pin digital 13
   - Condujo RX - cuya función es la actividad de RX en serie
   - Condujo Texas- cuya función es la actividad de TX
   - Condujo EN - se trata de un LED que siempre está encendidoo mientras se esté ejecutando la simulación

[Datasheet](https://docs.wokwi.com/parts/wokwi-arduino-uno)

### Módulo sensor de fotorresistor (LDR)

![LDR](https://alltopnotch.co.uk/wp-content/uploads/imported/4/LDR-Photoresistor-Light-Detection-Sensor-Module-Dependent-Resistor-Arduino-PIC-362145909694-3.JPG)

Este módulo incluye un LDR, es decir, una resistencia dependiente de la luz; conectado en serie, mediante del pin A0, con una resistencia de 10K. El voltaje de este pin depende de la cantidad de luz que incide sobre el sensor (se puede leer conectando el pin A0 a un pin de entrada analógica y empleando la función analogRead()).
La sensibilidad del LDR se controla a través de dos parámetro,s r|10, que es la resistencia del LDr a un nivel de iluminación de 10lux, y el valor gamma, el cual determina la pendiente del gráfico log(R)/log(llux) (estos datos vienen especificados en al hoja de datos del LDR).
  El pin digital de salida D0 podemos establecer el umbral, ajustando el potenciómetro integrado, para que cuando esté oscuro se ponga alto y cuando haya luz se ponga bajo. El umbral que viene predeterminado es 2,5V / 100lux aproximádamente.

[Datasheet](https://docs.wokwi.com/parts/wokwi-photoresistor-sensor)
  
### Pantalla LCD de 2 líneas y 16 caracteres por línea (LCD 1602)

![LCD_1602](https://upload.wikimedia.org/wikipedia/commons/9/94/Lcd_16x2.png)

Este componente tiene dos configuraciones posibles, la estándar y la I2C. Emplea el chip controlador LCD Hitachi HD44780, el cual viene con una fuente incorporada y con la capaciddad de definición de hasta 8 caracteres personalizados.
Se trata de una pantalla que proyecta los resultados configurados en el código y que dspone de 256 caracteres con lo siguientes rangos:
     - 0-7: caracteres definidos por el usuario
     - 8-31: caracteres en blanco
     - 32-127: caracteres ASCII estándar
     - 128-255: caracteres y símbbolos de Europa occidental y cirílicos

[Datasheet](https://docs.wokwi.com/parts/wokwi-lcd1602)

### Sensor de Movimiento Infrarrojo (PIR)

![PIR](https://www.electan.com/images/PIR%20Motion%20Sensor.jpg)

Se trata de un sensor de movimiento que se activa al seleccionarlo (haciendo clic en él) mientras se ejecuta la simulación o al abrir la correspondiente ventana emergente. Al activarlo, el pinde salida se elevará duurante 5 segundo y después bajará. Durante los siguientes 1,2 segundos, el correspondiente tiempo de inhibición, el sensor ignorará cualquier tipo de entrada adicional y, tras este tiempo, comenzará con su correspondiente detección del movimiento.
   La duración del pin de salida se puede configurar mediante elatributo delayTime o con el potenciómetro en su versión física. 

[Datasheet](https://docs.wokwi.com/parts/wokwi-pir-motion-sensor)
   
### Sensor DHT11 (Keyestudio)

![DHT11 Sensor](https://wiki.keyestudio.com/images/e/e9/%E6%97%A0%E6%A0%87%E9%A2%98-0034.png)

Se trata de un sensor de temperatura y humedad compuesto que se conecta a un microcontrolador de 8 bits de alto rendimiento. Incluye una resistencia y un dispositivo de temperatura NTC con sensación de humedad. Presenta coeficientes de calibración precisos que se almacenan en la memoria del programa OTP, donde los sensores internos detectan las señales en el proceso. Consta de un sistema de interfaz serial de un solo cable.

[Datasheet](https://wiki.keyestudio.com/Ks0034_keyestudio_DHT11_Temperature_and_Humidity_Sensor)

### Micro Servomotor Estándar

![Micro_Servomotor](https://bestarduino.com/upload/201902/06/201902061139001202.jpg)

Se trata de un tipo de motor compacto diseñado para proporcionar un control del movimiento angular. Consta de un motor de corriente continua, un circuito de control y un mecanismo de retroalimentación de posición, como un potenciómetro o un codificador. Esta retroalimentación permite al sistema controlar con precisión la posición del eje del motor.
Tiene un rango de movimiento de 180 grados y tiene una velocidad de rotación variable.Se controlan mediante señales de pulso modulado en anchura (PWM) generadas por un microcontrolador o un dispositivo electrónico. Al variar el ancho del pulso de control, es posible controlar la posición del eje del motor y, por lo tanto, el movimiento del dispositivo al que está conectado.

[Datasheet](https://docs.wokwi.com/parts/wokwi-servo)

### Termistor NTC

![Termistor](https://fw.lnwfile.com/_/fw/_raw/eo/ws/0u.jpg)

Se trata de un sensor de temperatura analógico que tiene una resistencia eléctrica que disminuye a medida que aumenta la temperatura. Esto significa que su resistencia disminuye a medida que aumenta la temperatura y viceversa. Este cambio en la resistencia se utiliza para medir la temperatura ambiente.
Se conecta en un circuito de división de voltaje junto con una resistencia de referencia conocida. La tensión en el punto de conexión entre el termistor y la resistencia de referencia se mide y se utiliza para determinar la resistencia del termistor, que a su vez se traduce en una temperatura utilizando una tabla de calibración o una ecuación específica del dispositivo.

[Datasheet](https://docs.wokwi.com/parts/wokwi-ntc-temperature-sensor)


## Mejoras propuestas

Como opciones de mejora se ha implementado un buzzer que se active en el modo de emergencia y un display de 4 dígitos que actua como display de la temperatura actual de la sala, a modo de termómetro. 
[Enlace](https://wokwi.com/projects/399625353140785153)

![Mejoras](./doc/img/wokwi_mejoras.png)


## Lógica de Control

Hemos empleado Fuzzy Logic para implementar el control. En primer lugar, hemos añadido la librería correspondiente:

```
#include <Fuzzy.h>
```

A continuación, hemos definido las reglas para gestionar el control de la luz:

```
// Regla 1: si ya es de noche y se detecta presencia -> se enciende el led
FuzzyRuleAntecedent* ifNightAndPresence = new FuzzyRuleAntecedent();
ifNightAndPresence->joinWithAND(dark, presenceInput);
// Creamos la consecuencia/accion de encender el led
FuzzyRuleConsequent* thenLedOn = new FuzzyRuleConsequent();
thenLedOn->addOutput(maxLight);
FuzzyRule* rule1 = new FuzzyRule(1, ifNightAndPresence, thenLedOn);
fuzzyIllumination->addFuzzyRule(rule1);
```
Y por último, hemos definido las reglas del control de la ventana:

```
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

```
