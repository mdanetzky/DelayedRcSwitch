# Delay switch

An Arduino mains switch which reacts to RC signal (433MHz) received by
a [https://github.com/sui77/rc-switch](https://github.com/sui77/rc-switch)
compatible receiver and toggles two relays in sequence.
Main purpose for this device is to gracefully power up and down the audio equipment,
to avoid the pop sound caused by the current spike coming from audio equipment and going to amplifier.

## How does it work

Arduino receives a 433 MHz code through a receiver connected on pin 2 (interrupt 0).
It then compares it with the one stored in EEPROM. If they match, then the two relays are toggled in following sequence:
first on -> delay -> second on, or second off -> delay -> first off.

### Learning the RC code

To learn a new code set the level of the pin defined in main.cpp as LEARN_BUTTON_PIN to HIGH.
Then start to repeatedly sending the signal to be learned. After five successfully received codes, the program will
find the most frequent one and store it in the EEPROM. The end of operation wil be marked
by faster blinking of the LED connected to LEARN_LED_PIN.

## Setting up

- Download and install [https://platformio.org/](https://platformio.org/).\
- Edit platformio.ini to match your board and programmer connection.\
- Change the defines in src/main.cpp to be reflect your setup:\
  - DELAY_TIME 2000 // Delay between switching of relay pins in milliseconds\
  - RELAY_PIN 7 // Connect the undelayed relay to this pin\
  - RELAY_DELAYED_PIN 8 // Connect the delayed relay to this pin\
  - LEARN_BUTTON_PIN 10 // Connect it to ground and to a button, which connects to Vcc via a big value resistor (eg. 10k)\
  - LEARN_LED_PIN 11 // Don't forget the 200 Ohm resistor\
\
Compile and upload as described in [https://platformio.org/](https://platformio.org/)\
\
Enjoy!

## License

This project is licensed under the MIT License - see the [LICENSE.md](http://opensource.org/licenses/MIT) file for details
