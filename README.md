# confortRoom-Grupo5

A contiuación se listarán los componentes necesarios para la realización de la simulación. 

1) Arduino UNO: se trata de una placa de microcontrolador con alimentada por el chip ATmega328p, que tiene 32kB de memoria de proograma Flash, 2kB de SRAM y 1kB de EEPROM. Esta incluye pines y leds distribuidos de la siguiente manera:
   - Tiene pines GPIO digitales del 0 al 13. Los pines desde el A0 hasta el A5 funcionan además como entrada analógica. Los pines digitales 3, 5, 6, 9, 10 y 11 tienen soporte de hardware PWM.
   - Tiene tres pines de tierra, GND.1, GND.2 y GND.3
   - Los pines VIN/5V están conectados a la fuente de alimentación positiva
   - Los pines 3.3V / IOREF / AREF / RESET no están disponibles en la simulación

La placa incluye cuatro LEDs:
   - Condujo I - conectado al pin digital 13
   - Condujo RX - cuya función es la actividad de RX en serie
   - Condujo Texas- cuya función es la actividad de TX
   - Condujo EN - se trata de un LED que siempre está encendidoo mientras se esté ejecutando la simulación


2) Módulo sensor de fotorresistor (LDR): este módulo incluye un LDR, es decir, una resistencia dependiente de la luz; conectado en serie, mediante del pin A0, con una resistencia de 10K. El voltaje de este pin depende de la cantidad de luz que incide sobre el sensor (se puede leer conectando el pin A0 a un pin de entrada analógica y empleando la función analogRead()).
  La sensibilidad del LDR se controla a través de dos parámetro,s r|10, que es la resistencia del LDr a un nivel de iluminación de 10lux, y el valor gamma, el cual determina la pendiente del gráfico log(R)/log(llux) (estos datos vienen especificados en al hoja de datos del LDR).
  El pin digital de salida D0 podemos establecer el umbral, ajustando el potenciómetro integrado, para que cuando esté oscuro se ponga alto y cuando haya luz se ponga bajo. El umbral que viene predeterminado es 2,5V / 100lux aproximádamente.

3) Pantalla LCD de 2 líneas y 16 caracteres por línea (LCD 1602): este componente tiene dos configuraciones posibles, la estándar y la I2C. Emplea el chip controlador LCD Hitachi HD44780, el cual viene con una fuente incorporada y con la capaciddad de definición de hasta 8 caracteres personalizados.
   Se trata de una pantalla que proyecta los resultados configurados en el código y que dspone de 256 caracteres con lo siguientes rangos:
     - 0-7: caracteres definidos por el usuario
     - 8-31: caracteres en blanco
     - 32-127: caracteres ASCII estándar
     - 128-255: caracteres y símbbolos de Europa occidental y cirílicos


