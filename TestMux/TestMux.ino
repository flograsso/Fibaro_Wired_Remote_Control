#include "MUX.h"

void setup()
{
    Serial.begin(9600);
    initMUX();
        for (int i = 0; i<8; i++)
    {
        setMuxChannel(i);
        setChannelState(i,HIGH);
    }
    
}

void loop()
{

    for (int i = 0; i<8; i++)
    {
        Serial.println(i);
        setMuxChannel(i);
        blinkChannel(i);
    }
}
