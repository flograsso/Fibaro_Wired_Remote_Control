#include "Utils.h"
#include "Fibaro_Wired_RC.h"


Channel channelArray[CORTINA_NUMBERS];

void moverCortina(uint8_t cortinaNumber, char action)
{     
      // Valido cortina number
      if (cortinaNumber >= 1 && cortinaNumber <= CORTINA_NUMBERS - 1)
      {
            // Si pude seleccionar el canal en el control
            if (selectChannel(cortinaNumber))
            {
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



{
// TODO
      uint8_t LEDpinADC; // para elegir
      uint8_t LEDpinOUTCHShifter;// para indicar cual estoy manejando
}

bool selectChannel(uint8_t cortinaNumber)
{

      // OJO que tengo que medir varias veces ya que tititla
      // Hacer test midiendo los 4 analog seguidido a ver si lo veo
      // funcion con cortinas en simultaneo? enciendo todos los leds. tendria que crear una nueva cortina
      Y tengo que ver que los otros leds no esten encendidos tmb
      unsigned long init = millis();
      while ((millis() - init < 4000) && (analogRead(channelArray[channel].LEDpinADC) > (channelArray[channel].normalVoltajeLED * 0.6) ));
      
      if Ok
      return 1;
      else
      return 0
}