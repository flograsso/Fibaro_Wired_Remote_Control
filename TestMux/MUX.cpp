#include "MUX.h"


void initMUX()
{
      pinMode(MUX_ACT_PIN, OUTPUT);
      pinMode(MUX_S0_PIN, OUTPUT);
      pinMode(MUX_S1_PIN, OUTPUT);
      pinMode(MUX_S2_PIN, OUTPUT);
      pinMode(MUX_S3_PIN, OUTPUT);
}
void setMuxChannel(uint8_t channel)
{
      digitalWrite(MUX_S0_PIN, bitRead(channel, 0));
      digitalWrite(MUX_S1_PIN, bitRead(channel, 1));
      digitalWrite(MUX_S2_PIN, bitRead(channel, 2));
      digitalWrite(MUX_S3_PIN, bitRead(channel, 3));
}

void setChannelState(uint8_t channel,uint8_t state)
{
      setMuxChannel(channel);
      digitalWrite(MUX_ACT_PIN, state);
}

void blinkChannel(uint8_t channel)
{
      setMuxChannel(channel);
      digitalWrite(MUX_ACT_PIN, LOW);
      delay(2000);
      digitalWrite(MUX_ACT_PIN, HIGH);
}
