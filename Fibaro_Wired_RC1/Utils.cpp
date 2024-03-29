#include "Utils.h"
#include "Fibaro_Wired_RC1.h"

Channel channelArray[CORTINA_NUMBERS];

// Cortinas seleccionadas actualmente
uint8_t cortinaActual_control1 = 1;
uint8_t cortinaActual_control5 = 5;

/*
      Actuo sobre cortina.
      Accion:  U (Subir) | D (bajar) | S (stop) | F (fauvorite)
      Canal: 
*/
void moverCortina(uint8_t cortinaNumber, char action)
{
      // Valido cortina number
      if (cortinaNumber >= 1 && cortinaNumber <= CORTINA_NUMBERS - 1)
      {     
            DEBUG_SERIAL.print("Mover cortina sobre cortina: " + cortinaNumber);

            // Si no tengo ya seleccionada la cortina
            if (!(cortinaActual_control1 == cortinaNumber || cortinaActual_control5 == cortinaNumber))
                  selectChannel(cortinaNumber);
            
            DEBUG_SERIAL.print("Tomo accion de '" + (String)action + "' sobre cortina: " + cortinaNumber);
            switch (action)
            {
                  case 'U':
                        blinkChannel(channelArray[cortinaNumber].buttonUpCHShifter);
                        break;

                  case 'D':
                        blinkChannel(channelArray[cortinaNumber].buttonDownCHShifter);
                        break;

                  case 'S':
                        blinkChannel(channelArray[cortinaNumber].buttonStopCHShifter);
                        break;

                  case 'F':
                        blinkChannel(channelArray[cortinaNumber].buttonDownCHShifter);
                        delay(channelArray[1].favouritePositionDelay * 1000);
                        blinkChannel(channelArray[cortinaNumber].buttonStopCHShifter);
                        break;
            }
      }
}

void blinkChannel(uint8_t channel)
{
      DEBUG_SERIAL.print("Simulo pulsación boton en el pin Nro: ");
      DEBUG_SERIAL.println(channel);

      digitalWrite(channel, LOW);
      delay(1000);
      digitalWrite(channel, HIGH);
      delay(1000);

}

void selectChannel(uint8_t cortinaNumber)
{
      uint8_t cortinaActual;
      unsigned long timeout;

      DEBUG_SERIAL.print("Función de seleccion de canal. Canal a elegir: ");
      DEBUG_SERIAL.println(cortinaNumber);

      // Presiono SELECT button para que blinkee el led del canal actual, con el primer pulso no cambia de canal.
      blinkChannel(channelArray[cortinaNumber].buttonSelectCHShifter);

      DEBUG_SERIAL.println("Presiono SELECT button");
      
      timeout = millis();

      // Aca tengo que constatar que blinkee el led de canal a elegir y que no blinkee otro canal
      // ya que en ese caso estoy en el multicanal (maneja todos los canales a la vez)
      // El canal 1,2 y 3 lo constato con el 4 (que el 4 este OFF) y el 4 lo constato con el 3.
      // En 6 chequeo que todos los leds blinckeen y 5 no hago nada que es monocanal
      switch (cortinaNumber)
      {
            case 1:
            case 2:
            case 3:
                  while (!readAnalogUntil(cortinaNumber, 4) && (millis() - timeout) < 30000)
                        blinkChannel(channelArray[cortinaNumber].buttonSelectCHShifter);
                  break;
            case 4:
                  while (!readAnalogUntil(cortinaNumber, 3) && (millis() - timeout) < 30000)
                        blinkChannel(channelArray[cortinaNumber].buttonSelectCHShifter);
                  break;
            case 5:
                  break;
            case 6:
                  while (!read4AnalogUntil() && (millis() - timeout) < 30000)
                        blinkChannel(channelArray[cortinaNumber].buttonSelectCHShifter);
                  break;
      }
      
      // Seteo cortina actual segun control.
      if ((cortinaNumber > 1 && cortinaNumber <= 4) || cortinaNumber == 6)
            cortinaActual_control1 = cortinaNumber;

      //turnOnLedSeleccionCortina(cortinaNumber);
}
/*
void turnOnLedSeleccionCortina(uint8_t cortinaSeleccionada)
{
      if (cortinaSeleccionada == 8) // Manejador de multiples cortinas
      {
            setChannelState(channelArray[5].LEDpinOUTCHShifter, HIGH); // Enciendo led de seleccion de cortina actual
            setChannelState(channelArray[6].LEDpinOUTCHShifter, HIGH); // Enciendo led de seleccion de cortina actual
            setChannelState(channelArray[7].LEDpinOUTCHShifter, HIGH); // Enciendo led de seleccion de cortina actual

            setChannelState(channelArray[1].LEDpinOUTCHShifter, LOW); // Enciendo led de seleccion de cortina actual
            setChannelState(channelArray[2].LEDpinOUTCHShifter, LOW); // Enciendo led de seleccion de cortina actual
            setChannelState(channelArray[3].LEDpinOUTCHShifter, LOW); // Enciendo led de seleccion de cortina actual
            setChannelState(channelArray[4].LEDpinOUTCHShifter, LOW); // Enciendo led de seleccion de cortina actual
      }
      else if (cortinaSeleccionada == 9) // Manejador de multiples cortinas
      {
            setChannelState(channelArray[1].LEDpinOUTCHShifter, HIGH); // Enciendo led de seleccion de cortina actual
            setChannelState(channelArray[2].LEDpinOUTCHShifter, HIGH); // Enciendo led de seleccion de cortina actual
            setChannelState(channelArray[3].LEDpinOUTCHShifter, HIGH); // Enciendo led de seleccion de cortina actual
            setChannelState(channelArray[4].LEDpinOUTCHShifter, HIGH); // Enciendo led de seleccion de cortina actual

            setChannelState(channelArray[5].LEDpinOUTCHShifter, LOW); // Enciendo led de seleccion de cortina actual
            setChannelState(channelArray[6].LEDpinOUTCHShifter, LOW); // Enciendo led de seleccion de cortina actual
            setChannelState(channelArray[7].LEDpinOUTCHShifter, LOW); // Enciendo led de seleccion de cortina actual
      }
      else
      {
            for (int i = 1; i < CORTINA_NUMBERS - 2; i++)
            {
                  if (i == cortinaSeleccionada)
                        setChannelState(channelArray[i].LEDpinOUTCHShifter, HIGH); // Enciendo led de seleccion de cortina actual
                  else
                        setChannelState(channelArray[i].LEDpinOUTCHShifter, LOW); // Enciendo led de seleccion de cortina actual
            }
      }
}
*/

bool readAnalogUntil(uint8_t pinNumber, uint8_t controlPin)
{
      unsigned long timeout = millis();
      while ((millis() - timeout) < 1000 && (analogRead(channelArray[pinNumber].LEDpinADC) > (channelArray[pinNumber].normalVoltajeLED * 0.6)) || (analogRead(channelArray[controlPin].LEDpinADC) < (channelArray[controlPin].normalVoltajeLED * 0.6)))
      {
            //Serial.println("Pin: " + (String)pinNumber + " con voltaje: " + (String)analogRead(channelArray[pinNumber].LEDpinADC));
            //Serial.println("Pin: " + (String)controlPin + " con voltaje: " + (String)analogRead(channelArray[controlPin].LEDpinADC));
            delay(100);
      }

      if ((millis() - timeout) >= 1000)
            return false;
      else
            return true;
}

bool read4AnalogUntil()
{
      unsigned long timeout = millis();
      while ((millis() - timeout) < 1000 && ((analogRead(channelArray[1].LEDpinADC) > (channelArray[1].normalVoltajeLED * 0.6)) ||
                                             (analogRead(channelArray[2].LEDpinADC) > (channelArray[2].normalVoltajeLED * 0.6)) ||
                                             (analogRead(channelArray[3].LEDpinADC) > (channelArray[3].normalVoltajeLED * 0.6)) ||
                                             (analogRead(channelArray[4].LEDpinADC) > (channelArray[4].normalVoltajeLED * 0.6))))

            delay(100);
      if ((millis() - timeout) >= 1000)
            return false;
      else
            return true;
}

