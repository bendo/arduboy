#include "Arduboy.h"

Arduboy arduboy;

void setup() {
    arduboy.begin();
    arduboy.clear();
}

void loop() {
    arduboy.clear();
    arduboy.display();
}

