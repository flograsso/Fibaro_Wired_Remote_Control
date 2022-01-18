#include "Fibaro_Wired_RC1.h"

extern ArduinoQueue<movimiento_t> colaMovimientos;


#define ACTIVATE_DEBUG

void setup()
{

#ifdef ACTIVATE_DEBUG
      DEBUG_SERIAL.begin(9600);
      delay(3000);
      DEBUG_SERIAL.println("Init");
#endif

      // Inicializa los pines del array
      initArrayChannels();

      // Pinmode de los analogs
      initAnalog();

      // Leo voltaje actual de led de seleccion de canal
      readLedVoltajeNormal();

      // Me conecto al wifi e inicio el servidor
      ConnectWiFi_STA(true);
      InitServer();

      // Arranco posicionandome en las cortinas numero 1 de cada control (tiene memoria el control)
      selectChannel(cortinaActual_control1);

      //turnOnLedSeleccionCortina(cortinaActual_control2); // Enciendo led de seleccion de cortina actual la numero 1 (control 2)
      //turnOnLedSeleccionCortina(cortinaActual_control3); // Enciendo led de seleccion de cortina actual la numero 1 (control 3)
}

void loop()
{
      fauxmo.handle();
      if (!colaMovimientos.isEmpty())
      {
            movimiento_t mov;
            mov = colaMovimientos.dequeue();
            moverCortina(mov.cortinaNumber,mov.accion);
            Serial.print("Tomo accion de '" + (String)mov.accion + "' sobre cortina: " + (String)mov.cortinaNumber);
            
      }
      testWifiConnection();
      
}

void initAnalog()
{
      pinMode(CORTINA_1_ANALOG_LED, INPUT);
      pinMode(CORTINA_2_ANALOG_LED, INPUT);
      pinMode(CORTINA_3_ANALOG_LED, INPUT);
      pinMode(CORTINA_4_ANALOG_LED, INPUT);
}

void readLedVoltajeNormal()
{
      // Los 4 leds del control 1
      for (int i = 1; i < 5; i++)
      {
            float sum = 0;
            for (int j = 0; j < 10; j++)
            {
                  sum += analogRead(channelArray[i].LEDpinADC);
                  delay(100);
            }
            // FIXME
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

      // PINES MUX ACTUAR SOBRE BOTONES
      // Control 1
      channelArray[1].buttonUpCHShifter = CONTROL_1_UP_PIN;
      channelArray[2].buttonUpCHShifter = CONTROL_1_UP_PIN;
      channelArray[3].buttonUpCHShifter = CONTROL_1_UP_PIN;
      channelArray[4].buttonUpCHShifter = CONTROL_1_UP_PIN;
      channelArray[6].buttonUpCHShifter = CONTROL_1_UP_PIN;

      // Control 5
      channelArray[5].buttonUpCHShifter = CONTROL_5_UP_PIN;

      // Control 1
      channelArray[1].buttonDownCHShifter = CONTROL_1_DOWN_PIN;
      channelArray[2].buttonDownCHShifter = CONTROL_1_DOWN_PIN;
      channelArray[3].buttonDownCHShifter = CONTROL_1_DOWN_PIN;
      channelArray[4].buttonDownCHShifter = CONTROL_1_DOWN_PIN;
      channelArray[6].buttonDownCHShifter = CONTROL_1_DOWN_PIN;

      // Control 5
      channelArray[5].buttonDownCHShifter = CONTROL_5_DOWN_PIN;

      // Control 1
      channelArray[1].buttonStopCHShifter = CONTROL_1_STOP_PIN;
      channelArray[2].buttonStopCHShifter = CONTROL_1_STOP_PIN;
      channelArray[3].buttonStopCHShifter = CONTROL_1_STOP_PIN;
      channelArray[4].buttonStopCHShifter = CONTROL_1_STOP_PIN;
      channelArray[6].buttonStopCHShifter = CONTROL_1_STOP_PIN;

      // Control 5
      channelArray[5].buttonStopCHShifter = CONTROL_5_STOP_PIN;

      // Control 1
      channelArray[1].buttonSelectCHShifter = CONTROL_1_SELECT_PIN;
      channelArray[2].buttonSelectCHShifter = CONTROL_1_SELECT_PIN;
      channelArray[3].buttonSelectCHShifter = CONTROL_1_SELECT_PIN;
      channelArray[4].buttonSelectCHShifter = CONTROL_1_SELECT_PIN;
      channelArray[6].buttonSelectCHShifter = CONTROL_1_SELECT_PIN;

      /*
      // PINES MUX PARA ACTUAR SOBRE LEDS DE CANAL ACTUAL
      channelArray[1].LEDpinOUTCHShifter = CORTINA_1_LED_OUT_SHIFTER_CH;
      channelArray[2].LEDpinOUTCHShifter = CORTINA_2_LED_OUT_SHIFTER_CH;
      channelArray[3].LEDpinOUTCHShifter = CORTINA_3_LED_OUT_SHIFTER_CH;
      channelArray[4].LEDpinOUTCHShifter = CORTINA_4_LED_OUT_SHIFTER_CH;
      channelArray[5].LEDpinOUTCHShifter = CORTINA_5_LED_OUT_SHIFTER_CH;
      channelArray[6].LEDpinOUTCHShifter = CORTINA_6_LED_OUT_SHIFTER_CH;
      channelArray[7].LEDpinOUTCHShifter = CORTINA_7_LED_OUT_SHIFTER_CH;
      */

      channelArray[1].favouritePositionDelay = CORTINA_1_FAVOURITE_POSITION_DELAY;
      channelArray[2].favouritePositionDelay = CORTINA_2_FAVOURITE_POSITION_DELAY;
      channelArray[3].favouritePositionDelay = CORTINA_3_FAVOURITE_POSITION_DELAY;
      channelArray[4].favouritePositionDelay = CORTINA_4_FAVOURITE_POSITION_DELAY;
      channelArray[5].favouritePositionDelay = CORTINA_5_FAVOURITE_POSITION_DELAY;
      channelArray[6].favouritePositionDelay = CORTINA_6_FAVOURITE_POSITION_DELAY;

      // Control 1
      pinMode(CONTROL_1_UP_PIN, OUTPUT);
      pinMode(CONTROL_1_DOWN_PIN, OUTPUT);
      pinMode(CONTROL_1_STOP_PIN, OUTPUT);
      pinMode(CONTROL_1_SELECT_PIN, OUTPUT);

      // Control 5
      pinMode(CONTROL_5_UP_PIN, OUTPUT);
      pinMode(CONTROL_5_DOWN_PIN, OUTPUT);
      pinMode(CONTROL_5_STOP_PIN, OUTPUT);

      // Control 1
      digitalWrite(CONTROL_1_UP_PIN, HIGH);
      digitalWrite(CONTROL_1_DOWN_PIN, HIGH);
      digitalWrite(CONTROL_1_STOP_PIN, HIGH);
      digitalWrite(CONTROL_1_SELECT_PIN, HIGH);

      // Control 5
      digitalWrite(CONTROL_5_UP_PIN, HIGH);
      digitalWrite(CONTROL_5_DOWN_PIN, HIGH);
      digitalWrite(CONTROL_5_STOP_PIN, HIGH);
}
