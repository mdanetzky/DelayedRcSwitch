//
// Created by Matthias Danetzky on 04/12/2019.
//

#include <TimerOne.h>
#include "most_frequent.h"
#include "rc_code_memory.h"
#include <Arduino.h>
#include "eeprom_util.h"

#define FAST_BLINKING 125000
#define SLOW_BLINKING 250000
#define BUFFER_SIZE 5

int ledState = LOW;
byte learnLedPin;
byte learnButtonPin;
unsigned long buffer[BUFFER_SIZE];
byte buffer_position = 0;
unsigned long mostFrequentRcCode;
unsigned long rcCodeFromEeprom = 0;

void blinkLearningLED(void);

void toggleLed();

void saveMostFrequentCode();

void initLearningLed(byte led_pin, byte button_pin) {
    learnLedPin = led_pin;
    learnButtonPin = button_pin;
    Timer1.initialize(SLOW_BLINKING);
    Timer1.attachInterrupt(blinkLearningLED);
    pinMode(learnLedPin, OUTPUT);
    digitalWrite(learnLedPin, LOW);
}

unsigned long readRcCodeFromEeprom() {
    if (rcCodeFromEeprom == 0) {
        rcCodeFromEeprom = EEPROMReadlong(0);
    }
    return rcCodeFromEeprom;
}

void blinkFaster() {
    Timer1.setPeriod(FAST_BLINKING);
}

void blinkLearningLED(void) {
    if (digitalRead(learnButtonPin)) {
        toggleLed();
    } else {
        digitalWrite(learnLedPin, LOW);
        Timer1.setPeriod(SLOW_BLINKING);
        buffer_position = 0;
    }
}

void toggleLed() {
    if (ledState == LOW) {
        ledState = HIGH;
    } else {
        ledState = LOW;
    }
    digitalWrite(learnLedPin, ledState);
}

void learnRcCode(unsigned long receivedCode) {
    Serial.println(F("Learn button pressed"));
    if (buffer_position == BUFFER_SIZE) {
        Serial.println(F("Learning done"));
        return;
    }
    if (buffer_position == (BUFFER_SIZE - 1)) {
        buffer_position = BUFFER_SIZE;
        blinkFaster();
        saveMostFrequentCode();
    }
    if (buffer_position < BUFFER_SIZE) {
        buffer[buffer_position++] = receivedCode;
    }
}

void saveMostFrequentCode() {
    mostFrequentRcCode = mostFrequent(buffer, BUFFER_SIZE);
    if (rcCodeFromEeprom == mostFrequentRcCode) {
        Serial.print(F("New RC code is the same as memorized one: "));
        Serial.println(mostFrequentRcCode);
    } else {
        Serial.print(F("Learned new RC code: "));
        Serial.println(mostFrequentRcCode);
        EEPROMWriteLong(0, mostFrequentRcCode);
        rcCodeFromEeprom = mostFrequentRcCode;
    }
}
