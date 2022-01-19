
#ifndef FIBARO_WIRED_H
#define FIBARO_WIRED_H


#include <WiFi.h>
#include <WebServer.h>
#include <ESPAsyncWebServer.h>
#include "fauxmoESP.h"
#include "WiFIFunctions.h"
#include <ArduinoQueue.h>
#include "ServerFunctions.h"



// Control 1
#define CORTINA_1_ANALOG_LED        36          //CTRL1 - CH1
#define CORTINA_2_ANALOG_LED        39          //CTRL1 - CH2
#define CORTINA_3_ANALOG_LED        34          //CTRL1 - CH3
#define CORTINA_4_ANALOG_LED        35          //CTRL1 - CH4

#define CONTROL_1_UP_PIN            32          
#define CONTROL_1_DOWN_PIN          33   
#define CONTROL_1_STOP_PIN          25   
#define CONTROL_1_SELECT_PIN        26    

// Control 5

#define CONTROL_5_UP_PIN            27          
#define CONTROL_5_DOWN_PIN          14   
#define CONTROL_5_STOP_PIN          13   
  

// Tiempo funcionando para una posicion determinada (en sec) partiendo desde CORTINA ABIERTA
#define CORTINA_1_FAVOURITE_POSITION_DELAY            5
#define CORTINA_2_FAVOURITE_POSITION_DELAY            5
#define CORTINA_3_FAVOURITE_POSITION_DELAY            5
#define CORTINA_4_FAVOURITE_POSITION_DELAY            5
#define CORTINA_5_FAVOURITE_POSITION_DELAY            5
#define CORTINA_6_FAVOURITE_POSITION_DELAY            5



#define CORTINA_NUMBERS       7 // +1 del largo (arranco en 1) Son 7 cortinas mas 2 estados que manejan todo el grupo de cortinas (todos los leds titilantes)


extern fauxmoESP fauxmo;



// Variables

struct Channel
{
      uint8_t LEDpinADC;
      uint8_t LEDpinOUTCHShifter;
      uint8_t buttonUpCHShifter;
      uint8_t buttonDownCHShifter;
      uint8_t buttonStopCHShifter;
      uint8_t buttonSelectCHShifter;
      float normalVoltajeLED;
      uint8_t favouritePositionDelay;
};

extern Channel channelArray[CORTINA_NUMBERS];
extern uint8_t cortinaActual_control1;
extern uint8_t cortinaActual_control5;




#endif