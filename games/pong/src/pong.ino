#include "Arduboy.h"
#include <MemoryFree.h>

Arduboy arduboy;

int state = 0;
int pressed = 0;
int ballx = 62;
int bally = 0;
int ballSize = 4;
int right = 1;
int down = 1;

void setup() {
    arduboy.begin();
    srand(7/8);
    arduboy.setFrameRate(60);
    arduboy.clear();
}

void loop() {
    if (!arduboy.nextFrame()) {
	return;
    }

    arduboy.clear();

    arduboy.setCursor(0, 0);
    switch (state) {
        case 0:
            arduboy.print("title");
            break;
        case 1:
            arduboy.print("game");
            play();
            break;
        case 2:
            arduboy.print("win");
            break;
        case 3:
            arduboy.print("lose");
            break;
    }
    moveToScreen();
    arduboy.display();
}

void play() {
    arduboy.fillRect(ballx, bally, ballSize, ballSize, WHITE);
    right == 1 ? ballx++ : ballx--;
    right = ballx == 0 ? 1 : ballx == 127 ? 0 : right;
    down == 1 ? bally++ : bally--;
    down = bally == 0 ? 1 : bally == 63 ? 0 : down;
}

void moveToScreen() {
    if (arduboy.pressed(A_BUTTON) && pressed == 0) {
        state = state < 3 ? state + 1 : 0;
        pressed = 1;
    }
    if (arduboy.notPressed(A_BUTTON)) {
        pressed = 0;
    }
}
