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
- Sensor de movimiento PIR KS0052 de keyestudio.


## Funcionamiento

El dispositivo cuenta con un display LCD que permite la visualización de 4 datos distintos:

- Temperatura (˚C)
- Humedad (%)
- Luz (Lux)
- Movimiento/Presencia

Este display solo se encenderá y mostrará la información en caso de que detecte movimiento en la habitación. Cuenta con un botón que permite controlar que datos se muestran, dado que se exiben 2 datos simultaneamente: temperatura y humedad, o luz y detección de movimiento.

Además, el sistema permite el control sobre la luz de la habitación. Dicha luz se encenderá en caso de detección de movimiento y la luz ambiental se encuentre por debajo del umbral establecido.


### Demo

TODO: introducir imagen con enlace al video


