# Pruebas de validación

Para la realización de la actividad, primero se ha creado el código y una simulación del montaje en Wokwi. Este proyecto se encuentra disponible en los siguientes enlaces
- [Enlace](https://wokwi.com/projects/401550694219162625) para la versión que emplea fuzzy logic.
- [Enlace](https://wokwi.com/projects/401550694219162625) para la versión que no emplea fuzzy logic.

Partiendo de esa base, se ha exportado el proyecto y se le han realizado unas modificaciones al codigo para que funcione sobre la placa Arduino Uno física. Las modificaciones son:

- Cambio en el cálculo de la transformación de la lectura analógica del LDR, al ser distintos el LDR empleado en la plataforma Wokwi (con circuito acondicionador integrado) y el disponible en el kit de Arduino.
- Cambio del sensor DHT22 proporcionado en la plataforma Wokwi por el sensor DHT11.
- Cambio del sensor de temperatura al termistor LM35 disponible.
- Cambios en los tiempos de espera para la ventilación y el encendido del LCD para la grabación del video de pruebas.

Se ha incluido un apartado de mejoras en el planteamiento realizado mediante Wokwi para una visión futura del proyecto. Esto se encuentra disponible en el siguiente [enlace](https://wokwi.com/projects/399625353140785153).
