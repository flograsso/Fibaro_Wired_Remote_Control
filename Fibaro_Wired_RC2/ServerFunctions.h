#ifndef SERVERFUNCTIONS_H
#define SERVERFUNCTIONS_H
#include <ESPAsyncWebServer.h>
#include "fauxmoESP.h"
#include "Utils.h"
#include <ArduinoQueue.h>



#define DEBUG_SERIAL Serial

#define SENDING_LED_PIN       27

struct movimiento
{
    char accion;
    uint8_t cortinaNumber;
};
typedef struct movimiento movimiento_t;


void InitServer();


#endif