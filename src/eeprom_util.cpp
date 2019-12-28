//
// Created by Matthias Danetzky on 03/12/2019.
//
#include <EEPROM.h>
#include <Arduino.h>

unsigned long EEPROMReadlong(int address) {
    unsigned long four = EEPROM.read(address);
    unsigned long three = EEPROM.read(address + 1);
    unsigned long two = EEPROM.read(address + 2);
    unsigned long one = EEPROM.read(address + 3);

    return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
}

void EEPROMWriteLong(int address, unsigned long value) {
    byte four = (value & 0xFF);
    byte three = ((value >> 8) & 0xFF);
    byte two = ((value >> 16) & 0xFF);
    byte one = ((value >> 24) & 0xFF);

    EEPROM.write(address, four);
    EEPROM.write(address + 1, three);
    EEPROM.write(address + 2, two);
    EEPROM.write(address + 3, one);
}