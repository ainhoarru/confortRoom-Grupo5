#include "ConfortRoom.h"

// Configurar el display LCD, de tamaño 16 col x 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);
// Definimos el modo del LCD, para conocer información que se muestra
volatile int lcdMode = 0;
// Variable que guarda que modo se esta mostrando para gestionar cuando se limpia el LCD
int displayedLCDMode = lcdMode;

// Humedad - https://maxpromer.github.io/LCD-Character-Creator/
byte humIcon[8] = {
  B00100, B00100, B01010, B01010, B10001, B10001, B10001, B01110
};
// Temperatura - https://maxpromer.github.io/LCD-Character-Creator/
byte tempIcon[8] = {
  B00100, B01010, B01010, B01110, B01110, B11111, B11111, B01110
};
// Luz - https://maxpromer.github.io/LCD-Character-Creator/
byte bulbIcon[8] = {
  B01110, B10001, B10101, B10101, B01110, B01010, B01110, B00000
};
// Presencia - https://maxpromer.github.io/LCD-Character-Creator/
byte personIcon[8] = {
  B01110, B01010, B01110, B00100, B01110, B10101, B01010, B01010
};
// Smiley - https://maxpromer.github.io/LCD-Character-Creator/
byte smileyIcon[8] = {
  B00000, B01010, B01010, B00000, B10001, B01110, B00000, B00000
};
// Sad - https://maxpromer.github.io/LCD-Character-Creator/
byte sadIcon[8] = {
  B00000, B01010, B01010, B00000, B01110, B10001, B00000, B00000
};

// Función que inicializa los elementos necesarios para que funcione el LCD y el boton
void initLCD() {
  // Inicializa el LCD
  lcd.init();

  // Inicializa los caracteres custom con los iconos
  lcd.createChar(1, humIcon);
  lcd.createChar(2, tempIcon);
  lcd.createChar(3, bulbIcon);
  lcd.createChar(4, personIcon);
  lcd.createChar(5, smileyIcon);
  lcd.createChar(6, sadIcon);

  // Boton para el cambio del modo del LCD
  pinMode(BUTTON_PIN, INPUT);
  // Se asigna la interrupción al momento en el que el botón se está soltando
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonPressHandler, FALLING);
}

// Función para el encendido del LCD
void turnLCDOn() {
  lcd.backlight();
}

// Función para el apagado del LCD, también elimina los datos
void turnLCDOff() {
  lcd.clear();
  lcd.noBacklight();
}

// Función que gestiona los valores que se muestran en el LCD dependiendo del valor
// de la variable lcdMode
void printLCDValues(int temperature, int humidity, int light, bool presence) {
  // Si el modo ha cambiado, se eliminan todos los datos del LCD
  if (displayedLCDMode != lcdMode) {
    lcd.clear();  // limpiar el LCD
    displayedLCDMode = lcdMode;
  }
  // El siguiente codigo gestiona el contenido del LCD
  if (lcdMode == 0) {
    lcd.setCursor(0, 0);
    lcd.write(2);
    lcd.setCursor(3, 0);
    lcd.print(temperature);
    lcd.print(" C   ");
    lcd.setCursor(0, 1);
    lcd.write(1);
    lcd.setCursor(3, 1);
    lcd.print(humidity);
    lcd.print(" %   ");
  } else if (lcdMode == 1) {
    lcd.setCursor(0, 0);
    lcd.write(3);
    lcd.setCursor(3, 0);
    lcd.print(light);
    lcd.print(" lux    ");
    lcd.setCursor(0, 1);
    lcd.write(4);
    lcd.setCursor(3, 1);
    if (presence) {
      lcd.write(5);
    } else {
      lcd.write(6);
    }
  }
}

// Función asociada a la interrupción del boton. Cuenta con un código "debouncer", que
// permite que el cambio de modo solo se de una vez cada 200ms. Esto se debe a que las
// inestabilidades en la corriente pueden hacer que una interrupción se ejecute una o
// más veces por cada vez que se pulsa el boton
void buttonPressHandler() {
  static int lastInterruptTime = 0;
  int interruptTime = millis();
  // Cambia el modo del LCD
  if (interruptTime - lastInterruptTime > 400) {
    lcdMode++;
    lcdMode = lcdMode % 2;  // Limita los modos del LCD a 2
    Serial.println(lcdMode);
  }

  lastInterruptTime = interruptTime;
}
