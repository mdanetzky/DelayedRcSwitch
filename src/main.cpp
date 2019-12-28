#include <Arduino.h>
#include <RCSwitch.h>
#include "most_frequent.h"
#include "rc_code_memory.h"

RCSwitch rcSwitch;

void learnRcCode();

void output(unsigned long decimal, unsigned int length, unsigned int delay, unsigned int *raw, unsigned int protocol);

#define DELAY_TIME 2000
#define RELAY_PIN 7
#define RELAY_DELAYED_PIN 8
#define LEARN_BUTTON_PIN 10
#define LEARN_LED_PIN 11
#define SWITCHED_OFF 0
#define SWITCHED_ON 1

byte state = SWITCHED_OFF;

void setup() {
    pinMode(RELAY_PIN, OUTPUT);
    pinMode(RELAY_DELAYED_PIN, OUTPUT);
    pinMode(LEARN_BUTTON_PIN, INPUT);
    digitalWrite(RELAY_PIN, HIGH);
    digitalWrite(RELAY_DELAYED_PIN, HIGH);
    Serial.begin(9600);
    rcSwitch = RCSwitch();
    rcSwitch.enableReceive(0); // Receiver on interrupt 0 => that is pin #2
    initLearningLed(LEARN_LED_PIN, LEARN_BUTTON_PIN);
}

void loop() {
    if (rcSwitch.available()) {
        if (digitalRead(LEARN_BUTTON_PIN)) {
            learnRcCode(rcSwitch.getReceivedValue());
        } else {
            if (readRcCodeFromEeprom() == rcSwitch.getReceivedValue()) {
                if (state == SWITCHED_OFF) {
                    digitalWrite(RELAY_PIN, LOW);
                    delay(DELAY_TIME);
                    digitalWrite(RELAY_DELAYED_PIN, LOW);
                    state = SWITCHED_ON;
                } else {
                    digitalWrite(RELAY_DELAYED_PIN, HIGH);
                    delay(DELAY_TIME);
                    digitalWrite(RELAY_PIN, HIGH);
                    state = SWITCHED_OFF;
                }
            }
        }
        output(rcSwitch.getReceivedValue(), rcSwitch.getReceivedBitlength(), rcSwitch.getReceivedDelay(),
               rcSwitch.getReceivedRawdata(), rcSwitch.getReceivedProtocol());
        rcSwitch.resetAvailable();
    }
}

void output(unsigned long decimal, unsigned int length, unsigned int delay, unsigned int *raw, unsigned int protocol) {
    Serial.print(F("Decimal: "));
    Serial.print(decimal);
    Serial.print(" (");
    Serial.print(length);
    Serial.print(F("Bit) PulseLength: "));
    Serial.print(delay);
    Serial.print(F(" microseconds"));
    Serial.print(F(" Protocol: "));
    Serial.println(protocol);
    Serial.print(F("Raw data: "));
    for (unsigned int i = 0; i <= length * 2; i++) {
        Serial.print(raw[i]);
        Serial.print(",");
    }
    Serial.println();
    Serial.println();
}