#include "Arduboy.h"

Arduboy arduboy;

void printLogo();

void setup() {
    arduboy.beginNoLogo();
    arduboy.setFrameRate(15);
}

void loop() {
    if (!(arduboy.nextFrame()))
        return;
    delay(100);
}

void printLogo() {
    arduboy.clear();
    arduboy.setCursor(41,28);
    arduboy.print(F("timer"));
    arduboy.display();
    delay(2000);
}
