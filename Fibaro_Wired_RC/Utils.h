
#ifndef UTILS_H
#define UTILS_H

#include "Arduino.h"

void moverCortina(uint8_t cortinaNumber, char action);
bool selectChannel(uint8_t cortinaNumber);
void turnOnLedSeleccionCortina(uint8_t cortinaActual);

#endif
