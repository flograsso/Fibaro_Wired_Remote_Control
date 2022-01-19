
#ifndef FIBARO_WIRED_H
#define FIBARO_WIRED_H


#include <WiFi.h>
#include <WebServer.h>
#include "WiFIFunctions.h"
#include "ServerFunctions.h"
#include "MUX.h"


// Control 2

#define CORTINA_1_ANALOG_LED        32          //CTRL3 - CH1
#define CORTINA_2_ANALOG_LED        33          //CTRL3 - CH2
#define CORTINA_3_ANALOG_LED        25          //CTRL3 - CH3
#define CORTINA_4_ANALOG_LED        35          //CTRL2 - CH4

#define CONTROL_2_UP_SHIFTER_CH           4        
#define CONTROL_2_DOWN_SHIFTER_CH         5    
#define CONTROL_2_STOP_SHIFTER_CH         6    
#define CONTROL_2_SELECT_SHIFTER_CH       7  

#define CORTINA_1_LED_OUT_SHIFTER_CH      8    
#define CORTINA_2_LED_OUT_SHIFTER_CH      9   
#define CORTINA_3_LED_OUT_SHIFTER_CH      10   
#define CORTINA_4_LED_OUT_SHIFTER_CH      11   

// Control 3
#define CORTINA_5_ANALOG_LED        36          //CTRL2 - CH1
#define CORTINA_6_ANALOG_LED        39          //CTRL2 - CH2
#define CORTINA_7_ANALOG_LED        34          //CTRL2 - CH3


#define CONTROL_3_UP_SHIFTER_CH           0          
#define CONTROL_3_DOWN_SHIFTER_CH         1    
#define CONTROL_3_STOP_SHIFTER_CH         2    
#define CONTROL_3_SELECT_SHIFTER_CH       3   

#define CORTINA_5_LED_OUT_SHIFTER_CH      12    
#define CORTINA_6_LED_OUT_SHIFTER_CH      13   
#define CORTINA_7_LED_OUT_SHIFTER_CH      14   


#define COMMAMND_SEND_LED_OUT_SHIFTER_CH   15   
 
// Tiempo funcionando para una posicion determinada (en sec) partiendo desde CORTINA ABIERTA
#define CORTINA_1_FAVOURITE_POSITION_DELAY            5
#define CORTINA_2_FAVOURITE_POSITION_DELAY            5
#define CORTINA_3_FAVOURITE_POSITION_DELAY            5
#define CORTINA_4_FAVOURITE_POSITION_DELAY            5
#define CORTINA_5_FAVOURITE_POSITION_DELAY            5
#define CORTINA_6_FAVOURITE_POSITION_DELAY            5
#define CORTINA_7_FAVOURITE_POSITION_DELAY            5


#define CORTINA_NUMBERS       10 // +1 del largo (arranco en 1) Son 7 cortinas mas 2 estados que manejan todo el grupo de cortinas (todos los leds titilantes)


extern WebServer server;



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
extern uint8_t cortinaActual_control2;
extern uint8_t cortinaActual_control3;



#endif