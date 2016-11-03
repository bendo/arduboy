#include "Arduboy.h"

Arduboy arduboy;

void setup() {
    arduboy.begin();
    arduboy.setFrameRate(15);
}

void loop() {
    if (!(arduboy.nextFrame()))
        return;

    if (arduboy.pressed(A_BUTTON)) {
        clearDisplay();
        arduboy.print("Hello!");    
    }

    if (arduboy.pressed(B_BUTTON)) {
        clearDisplay();
        arduboy.print("World!");    
    }

    arduboy.display();
}

void clearDisplay() {
    arduboy.clear();
    arduboy.setCursor(0, 0);
}
