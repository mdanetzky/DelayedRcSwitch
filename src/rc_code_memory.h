//
// Created by Matthias Danetzky on 04/12/2019.
//

#ifndef DELAY_SWITCH_RC_CODE_MEMORY_H
#define DELAY_SWITCH_RC_CODE_MEMORY_H

void blinkFaster();

void initLearningLed(byte led_pin, byte button_pin);

unsigned long readRcCodeFromEeprom();

void learnRcCode(unsigned long receivedCode);

#endif //DELAY_SWITCH_RC_CODE_MEMORY_H
