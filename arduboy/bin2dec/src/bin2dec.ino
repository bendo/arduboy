#include "Arduboy.h"

Arduboy arduboy;

uint8_t position{0};

char strIn[17]{"0000000000000000"};

char strOut[6]{"00000"};

void printLogo();

void updateDisplay();

void setup() {
    arduboy.beginNoLogo();
    arduboy.setFrameRate(15);
    printLogo();
    updateDisplay();
}

void loop() {
    if (!(arduboy.nextFrame()))
        return;

    if (arduboy.pressed(LEFT_BUTTON) && position > 0) {
        position--;
        updateDisplay();
    }

    if (arduboy.pressed(RIGHT_BUTTON) && position < 15) {
        position++;
        updateDisplay();
    }

    if (arduboy.pressed(UP_BUTTON) || arduboy.pressed(DOWN_BUTTON)) {
        strIn[position] ^= 0x01;
        updateDisplay();
        bin2dec();
    }

    delay(100);
}

void printLogo() {
    arduboy.clear();
    arduboy.setCursor(41, 28);
    arduboy.print(F("bin2dec"));
    arduboy.display();
    delay(2000);
}

void bin2dec() {
    // convert to dec
}

void updateDisplay() {
    arduboy.clear();
    arduboy.setCursor(16, 8);
    arduboy.print(strIn);
    arduboy.setCursor(16 + (position * 6), 16);
    arduboy.write('^');
    arduboy.setCursor(80, 32);
    arduboy.print(strOut);
    arduboy.display();
}
