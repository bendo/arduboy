#include "Arduboy.h"

Arduboy arduboy;


void setup() {
    arduboy.beginNoLogo();
    arduboy.setFrameRate(15);
}

void loop() {
    arduboy.clear();
    arduboy.setCursor(41, 28);
    arduboy.print(F("bin2dec"));
    arduboy.display();
}
