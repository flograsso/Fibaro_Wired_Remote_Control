#include "Utils.h"
#include "Fibaro_Wired_RC.h"


Channel channelArray[CORTINA_NUMBERS];
uint8_t cortinaActual_control2 = 1;
uint8_t cortinaActual_control3 = 5;

void moverCortina(uint8_t cortinaNumber, char action)
{     
      // Valido cortina number
      if (cortinaNumber >= 1 && cortinaNumber <= CORTINA_NUMBERS - 1)
      {
            // Si pude seleccionar el canal en el control
            if (cortinaActual_control2 == cortinaNumber || cortinaActual_control3 == cortinaNumber || selectChannel(cortinaNumber))
            {
                  DEBUG_SERIAL.print("Tomo accion de '" + (String)action + "' sobre cortina: " +cortinaNumber) ;
                  DEBUG_SERIAL.println(cortinaNumber);     
                  switch(action)
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
                              delay(channelArray[1].favouritePositionDelay);
                              blinkChannel(channelArray[cortinaNumber].buttonStopCHShifter);
                              break;

                  }
            }

      }

}


/*
{
// TODO
      uint8_t LEDpinADC; // para elegir
      uint8_t LEDpinOUTCHShifter;// para indicar cual estoy manejando
}
*/
bool selectChannel(uint8_t cortinaNumber)
{

      // OJO que tengo que medir varias veces ya que tititla
      // Hacer test midiendo los 4 analog seguidido a ver si lo veo
      // funcion con cortinas en simultaneo? enciendo todos los leds. tendria que crear una nueva cortina
      //Y tengo que ver que los otros leds no esten encendidos tmb

      DEBUG_SERIAL.print("Select channel actual: ");
      DEBUG_SERIAL.println(cortinaNumber);


      uint8_t cortinaActual;
      unsigned long timeout;



      blinkChannel(channelArray[cortinaNumber].buttonSelectCHShifter);
      DEBUG_SERIAL.print("Blinkeo canal: ");
      DEBUG_SERIAL.println(channelArray[cortinaNumber].buttonSelectCHShifter);
      timeout = millis();
 
            switch(cortinaNumber)
            {
                  case 1:
                  case 2:
                  case 3:
                        while (!readAnalogUntil(cortinaNumber,4) && (millis()-timeout) < 30000) blinkChannel(channelArray[cortinaNumber].buttonSelectCHShifter);
                        break;
                  case 4:
                        while (!readAnalogUntil(cortinaNumber,3) && (millis()-timeout) < 30000)  blinkChannel(channelArray[cortinaNumber].buttonSelectCHShifter);
                        break;
                  case 5:
                  case 6:
                        while (!readAnalogUntil(cortinaNumber,7) && (millis()-timeout) < 30000) blinkChannel(channelArray[cortinaNumber].buttonSelectCHShifter);
                        break;
                  case 7:
                        while (!readAnalogUntil(cortinaNumber,5) && (millis()-timeout) < 30000) blinkChannel(channelArray[cortinaNumber].buttonSelectCHShifter);
                        break;
                  case 8:   
                        while (!read4AnalogUntil() && (millis()-timeout) < 30000) blinkChannel(channelArray[cortinaNumber].buttonSelectCHShifter);
                        break;
                  case 9:
                        while (!read3AnalogUntil() && (millis()-timeout) < 30000) blinkChannel(channelArray[cortinaNumber].buttonSelectCHShifter);
                        break;
            }


            if ((cortinaNumber > 1 && cortinaNumber <=4) || cortinaNumber == 8 )
                        cortinaActual_control2 = cortinaNumber;
            else if ((cortinaNumber >= 5 && cortinaNumber <=7 ) || cortinaNumber == 9)
                        cortinaActual_control3 = cortinaNumber;

            //turnOnLedSeleccionCortina(cortinaNumber);

            return true;

      
      
}


void turnOnLedSeleccionCortina(uint8_t cortinaSeleccionada)
{
      if (cortinaSeleccionada == 8) // Manejador de multiples cortinas 
      {
            setChannelState(channelArray[5].LEDpinOUTCHShifter,HIGH); // Enciendo led de seleccion de cortina actual 
            setChannelState(channelArray[6].LEDpinOUTCHShifter,HIGH); // Enciendo led de seleccion de cortina actual 
            setChannelState(channelArray[7].LEDpinOUTCHShifter,HIGH); // Enciendo led de seleccion de cortina actual 

            setChannelState(channelArray[1].LEDpinOUTCHShifter,LOW); // Enciendo led de seleccion de cortina actual 
            setChannelState(channelArray[2].LEDpinOUTCHShifter,LOW); // Enciendo led de seleccion de cortina actual 
            setChannelState(channelArray[3].LEDpinOUTCHShifter,LOW); // Enciendo led de seleccion de cortina actual 
            setChannelState(channelArray[4].LEDpinOUTCHShifter,LOW); // Enciendo led de seleccion de cortina actual 
                  

      }
      else
            if (cortinaSeleccionada == 9) // Manejador de multiples cortinas 
            {
                  setChannelState(channelArray[1].LEDpinOUTCHShifter,HIGH); // Enciendo led de seleccion de cortina actual 
                  setChannelState(channelArray[2].LEDpinOUTCHShifter,HIGH); // Enciendo led de seleccion de cortina actual 
                  setChannelState(channelArray[3].LEDpinOUTCHShifter,HIGH); // Enciendo led de seleccion de cortina actual 
                  setChannelState(channelArray[4].LEDpinOUTCHShifter,HIGH); // Enciendo led de seleccion de cortina actual 
                  
                  setChannelState(channelArray[5].LEDpinOUTCHShifter,LOW); // Enciendo led de seleccion de cortina actual 
                  setChannelState(channelArray[6].LEDpinOUTCHShifter,LOW); // Enciendo led de seleccion de cortina actual 
                  setChannelState(channelArray[7].LEDpinOUTCHShifter,LOW); // Enciendo led de seleccion de cortina actual 
            }
            else
            {
                  for (int i = 1 ; i <CORTINA_NUMBERS - 2 ; i++)
                  {
                        if( i == cortinaSeleccionada )
                              setChannelState(channelArray[i].LEDpinOUTCHShifter,HIGH); // Enciendo led de seleccion de cortina actual 
                        else
                              setChannelState(channelArray[i].LEDpinOUTCHShifter,LOW); // Enciendo led de seleccion de cortina actual 
                  }
            }

}


bool readAnalogUntil(uint8_t pinNumber, uint8_t controlPin)
{
      unsigned long timeout = millis();
      while ((millis() - timeout) < 1000 && (analogRead(channelArray[pinNumber].LEDpinADC) > (channelArray[pinNumber].normalVoltajeLED * 0.6)) || (analogRead(channelArray[controlPin].LEDpinADC) < (channelArray[controlPin].normalVoltajeLED * 0.6) )) 
      {
            //Serial.println("Pin: " + (String)pinNumber + " con voltaje: " + (String)analogRead(channelArray[pinNumber].LEDpinADC));
            //Serial.println("Pin: " + (String)controlPin + " con voltaje: " + (String)analogRead(channelArray[controlPin].LEDpinADC));
            delay(50);
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
      (analogRead(channelArray[4].LEDpinADC) > (channelArray[4].normalVoltajeLED * 0.6)) ));
      if ((millis() - timeout) >= 1000)
            return false;  
      else 
            return true;    
}

bool read3AnalogUntil()
{
      unsigned long timeout = millis();
      while ((millis() - timeout) < 1000 && ((analogRead(channelArray[5].LEDpinADC) > (channelArray[5].normalVoltajeLED * 0.6)) || 
      (analogRead(channelArray[6].LEDpinADC) > (channelArray[6].normalVoltajeLED * 0.6))  ||
      (analogRead(channelArray[7].LEDpinADC) > (channelArray[7].normalVoltajeLED * 0.6))  ));
      if ((millis() - timeout) >= 1000)
            return false;  
      else 
            return true;    
}