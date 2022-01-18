
#ifndef UTILS_H
#define UTILS_H

#include "Arduino.h"

void moverCortina(uint8_t cortinaNumber, char action);
void selectChannel(uint8_t cortinaNumber);
//void turnOnLedSeleccionCortina(uint8_t cortinaActual);
bool readAnalogUntil(uint8_t pinNumber, uint8_t controlPin);
bool read4AnalogUntil();
void blinkChannel(uint8_t channel);
#endif
