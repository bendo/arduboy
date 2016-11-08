#include "Arduboy.h"

Arduboy arduboy;

uint8_t position{0};

char strIn[17]{"0000000000000000"};

char strOut[6]{"00000"};

void printLogo();

void bin2dec();

void dec_to_str (char* str, uint32_t val, size_t digits);

void updateDisplay();

uint32_t my_pow(uint32_t x, uint32_t n);

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
        bin2dec();
        updateDisplay();
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
    int len = sizeof strIn / sizeof *strIn;
    int d, j = 0;
    for (int i = len-2; i >= 0; i--) {
        d += (strIn[i] - '0') * my_pow(2, j);
        j++;
    }
    dec_to_str(strOut, d, 5);
}

void dec_to_str (char* str, uint32_t val, size_t digits) {
    size_t i=1u;

    for (; i <= digits; i++) {
        str[digits-i] = (char)((val % 10u) + '0');
        val /= 10u;
    }
    str[i-1u] = '\0';
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

uint32_t my_pow(uint32_t x, uint32_t n) {
    uint32_t r = 1;
    if (n == 0)
        return 1;

    while (n != 0) {
        r *= x;
        n--;
    }
    return r;
}
