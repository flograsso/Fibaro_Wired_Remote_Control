#ifndef MUX_H
#define MUX_H

#include "Arduino.h"


#define MUX_S0_PIN            23
#define MUX_S1_PIN            22
#define MUX_S2_PIN            21
#define MUX_S3_PIN            19
#define MUX_ACT_PIN           18

void setMuxChannel(uint8_t channel);
void initMUX();
void setChannelState(uint8_t channel, uint8_t state);
void blinkChannel(uint8_t channel);


#endif
