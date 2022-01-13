#include "Fibaro_Wired_RC.h"

#define ACTIVATE_DEBUG

void setup()
{

      #ifdef ACTIVATE_DEBUG
            DEBUG_SERIAL.begin(9600);
            delay(3000);
            DEBUG_SERIAL.println("Init");
      #endif
      
      
      initArrayChannels();
      initAnalog();
      initMUX();
      readLedVoltajeNormal();
      ConnectWiFi_STA(true);
      InitServer();

      // Esto va?
      for (int i = 0; i<16; i++)
      {
        setMuxChannel(i);
        setChannelState(i,HIGH);
      }


      // Arranco posicionandome en las cortinas numero 1 de cada control (tiene memoria el control)
      selectChannel(cortinaActual_control2);
      //selectChannel(cortinaActual_control3);
      turnOnLedSeleccionCortina(cortinaActual_control2); // Enciendo led de seleccion de cortina actual la numero 1 (control 2)
      turnOnLedSeleccionCortina(cortinaActual_control3); // Enciendo led de seleccion de cortina actual la numero 1 (control 3)

}



void loop()
{
      server.handleClient();
      testWifiConnection();
     
      
}

void initAnalog()
{
      pinMode(CORTINA_1_ANALOG_LED,INPUT);
      pinMode(CORTINA_2_ANALOG_LED,INPUT);
      pinMode(CORTINA_3_ANALOG_LED,INPUT);
      pinMode(CORTINA_4_ANALOG_LED,INPUT);
      pinMode(CORTINA_5_ANALOG_LED,INPUT);
      pinMode(CORTINA_6_ANALOG_LED,INPUT);
      pinMode(CORTINA_7_ANALOG_LED,INPUT);
}

void readLedVoltajeNormal()
{
      for (int i = 1 ; i < 8 ; i++)
      {
            float sum = 0;
            for (int j = 0; j < 10; j++)
            {
                  sum += analogRead(channelArray[i].LEDpinADC);
                  delay(100);
            }
            // OJO ESTO!!!! AJUSTAR SEGUN LA FUENTE QUE USEEE
            //channelArray[i].normalVoltajeLED = sum / 10;
            channelArray[i].normalVoltajeLED = 4095;
            DEBUG_SERIAL.print("Voltaje normal leido en channel " + (String)i + "en pin " + (String)channelArray[i].LEDpinADC + " = ");
            DEBUG_SERIAL.println(channelArray[i].normalVoltajeLED);

      }
            
}




void initArrayChannels()
{
      
      // PINES PLACA ANALOGICOS PARA LEER ESTADO LED
      channelArray[1].LEDpinADC = CORTINA_1_ANALOG_LED;
      channelArray[2].LEDpinADC = CORTINA_2_ANALOG_LED;
      channelArray[3].LEDpinADC = CORTINA_3_ANALOG_LED;
      channelArray[4].LEDpinADC = CORTINA_4_ANALOG_LED;
      channelArray[5].LEDpinADC = CORTINA_5_ANALOG_LED;
      channelArray[6].LEDpinADC = CORTINA_6_ANALOG_LED;
      channelArray[7].LEDpinADC = CORTINA_7_ANALOG_LED;

      // PINES MUX ACTUAR SOBRE BOTONES
      // Control 2
      channelArray[1].buttonUpCHShifter = CONTROL_2_UP_SHIFTER_CH;
      channelArray[2].buttonUpCHShifter = CONTROL_2_UP_SHIFTER_CH;
      channelArray[3].buttonUpCHShifter = CONTROL_2_UP_SHIFTER_CH;
      channelArray[4].buttonUpCHShifter = CONTROL_2_UP_SHIFTER_CH;
      channelArray[8].buttonUpCHShifter = CONTROL_2_UP_SHIFTER_CH;

      // Control 3
      channelArray[5].buttonUpCHShifter = CONTROL_3_UP_SHIFTER_CH;
      channelArray[6].buttonUpCHShifter = CONTROL_3_UP_SHIFTER_CH;
      channelArray[7].buttonUpCHShifter = CONTROL_3_UP_SHIFTER_CH;
      channelArray[9].buttonUpCHShifter = CONTROL_3_UP_SHIFTER_CH;

      // Control 2
      channelArray[1].buttonDownCHShifter = CONTROL_2_DOWN_SHIFTER_CH;
      channelArray[2].buttonDownCHShifter = CONTROL_2_DOWN_SHIFTER_CH;
      channelArray[3].buttonDownCHShifter = CONTROL_2_DOWN_SHIFTER_CH;
      channelArray[4].buttonDownCHShifter = CONTROL_2_DOWN_SHIFTER_CH;
      channelArray[8].buttonDownCHShifter = CONTROL_2_DOWN_SHIFTER_CH;

      // Control 3
      channelArray[5].buttonDownCHShifter = CONTROL_3_DOWN_SHIFTER_CH;
      channelArray[6].buttonDownCHShifter = CONTROL_3_DOWN_SHIFTER_CH;
      channelArray[7].buttonDownCHShifter = CONTROL_3_DOWN_SHIFTER_CH;
      channelArray[9].buttonDownCHShifter = CONTROL_3_DOWN_SHIFTER_CH;

      // Control 2
      channelArray[1].buttonStopCHShifter = CONTROL_2_STOP_SHIFTER_CH;
      channelArray[2].buttonStopCHShifter = CONTROL_2_STOP_SHIFTER_CH;
      channelArray[3].buttonStopCHShifter = CONTROL_2_STOP_SHIFTER_CH;
      channelArray[4].buttonStopCHShifter = CONTROL_2_STOP_SHIFTER_CH;
      channelArray[8].buttonStopCHShifter = CONTROL_2_STOP_SHIFTER_CH;

      // Control 3
      channelArray[5].buttonStopCHShifter = CONTROL_3_STOP_SHIFTER_CH;
      channelArray[6].buttonStopCHShifter = CONTROL_3_STOP_SHIFTER_CH;
      channelArray[7].buttonStopCHShifter = CONTROL_3_STOP_SHIFTER_CH;
      channelArray[9].buttonStopCHShifter = CONTROL_3_STOP_SHIFTER_CH;

      // Control 2
      channelArray[1].buttonSelectCHShifter = CONTROL_2_SELECT_SHIFTER_CH;
      channelArray[2].buttonSelectCHShifter = CONTROL_2_SELECT_SHIFTER_CH;
      channelArray[3].buttonSelectCHShifter = CONTROL_2_SELECT_SHIFTER_CH;
      channelArray[4].buttonSelectCHShifter = CONTROL_2_SELECT_SHIFTER_CH;
      channelArray[8].buttonSelectCHShifter = CONTROL_2_SELECT_SHIFTER_CH;

      // Control 3
      channelArray[5].buttonSelectCHShifter = CONTROL_3_SELECT_SHIFTER_CH;
      channelArray[6].buttonSelectCHShifter = CONTROL_3_SELECT_SHIFTER_CH;
      channelArray[7].buttonSelectCHShifter = CONTROL_3_SELECT_SHIFTER_CH;
      channelArray[9].buttonSelectCHShifter = CONTROL_3_SELECT_SHIFTER_CH;


      // PINES MUX PARA ACTUAR SOBRE LEDS DE CANAL ACTUAL
      channelArray[1].LEDpinOUTCHShifter = CORTINA_1_LED_OUT_SHIFTER_CH;
      channelArray[2].LEDpinOUTCHShifter = CORTINA_2_LED_OUT_SHIFTER_CH;
      channelArray[3].LEDpinOUTCHShifter = CORTINA_3_LED_OUT_SHIFTER_CH;
      channelArray[4].LEDpinOUTCHShifter = CORTINA_4_LED_OUT_SHIFTER_CH;
      channelArray[5].LEDpinOUTCHShifter = CORTINA_5_LED_OUT_SHIFTER_CH;
      channelArray[6].LEDpinOUTCHShifter = CORTINA_6_LED_OUT_SHIFTER_CH;
      channelArray[7].LEDpinOUTCHShifter = CORTINA_7_LED_OUT_SHIFTER_CH;


      channelArray[1].favouritePositionDelay = CORTINA_1_FAVOURITE_POSITION_DELAY;
      channelArray[2].favouritePositionDelay = CORTINA_2_FAVOURITE_POSITION_DELAY;
      channelArray[3].favouritePositionDelay = CORTINA_3_FAVOURITE_POSITION_DELAY;
      channelArray[4].favouritePositionDelay = CORTINA_4_FAVOURITE_POSITION_DELAY;
      channelArray[5].favouritePositionDelay = CORTINA_5_FAVOURITE_POSITION_DELAY;
      channelArray[6].favouritePositionDelay = CORTINA_6_FAVOURITE_POSITION_DELAY;
      channelArray[7].favouritePositionDelay = CORTINA_7_FAVOURITE_POSITION_DELAY;

}



