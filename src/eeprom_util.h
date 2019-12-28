//
// Created by Matthias Danetzky on 03/12/2019.
//


#ifndef DELAY_SWITCH_EEPROM_UTIL_H
#define DELAY_SWITCH_EEPROM_UTIL_H

unsigned long EEPROMReadlong(int address);

void EEPROMWriteLong(int address, unsigned long value);

#endif //DELAY_SWITCH_EEPROM_UTIL_H
