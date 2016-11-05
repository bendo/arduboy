#include "Arduboy.h"

Arduboy arduboy;

int16_t x, y;
uint8_t r;

void setup() {
    arduboy.beginNoLogo();
    arduboy.setFrameRate(15);
    centerCircle();
}

void loop() {
    if (!(arduboy.nextFrame()))
        return;

    if (arduboy.pressed(A_BUTTON) && (r > 0)) {
        r--;
    }

    if (arduboy.pressed(B_BUTTON) && fitIn()) {
        r++;
    }

    if (arduboy.pressed(LEFT_BUTTON) && (x > r)) {
        x--;
    }

    if (arduboy.pressed(RIGHT_BUTTON) && (x + r < WIDTH - 1)) {
        x++;
    }

    if (arduboy.pressed(UP_BUTTON) && (y > r)) {
        y--;
    }

    if (arduboy.pressed(DOWN_BUTTON) && (y + r < HEIGHT - 1)) {
        y++;
    }

    if (arduboy.pressed(A_BUTTON + B_BUTTON)) {
        centerCircle();
    }

    arduboy.clear();
    arduboy.drawCircle(x, y, r, 1);
    arduboy.display();
}

void centerCircle() {
    x = WIDTH / 2;
    y = HEIGHT / 2;
    r = 5;
}

boolean fitIn() {
    return (x > r) && (y > r) && (x + r < WIDTH - 1) && (y + r < HEIGHT - 1);
}
