#include "Arduboy.h"

Arduboy arduboy;

int state = 0;
int pressed = 0;
int ballx = 62;
int bally = 0;
int ballSize = 4;
int right = 1;
int down = 1;
int paddleWidth = 4;
int paddleHeight = 9;
int playerx = 0;
int playery = 0;
int computerx = 127 - paddleWidth;
int computery = 0;
int playerScore = 0;
int computerScore = 0;

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
            printScore();
            play();
            countScore();
            break;
        case 2:
            arduboy.print("win");
            resetScore();
            break;
        case 3:
            arduboy.print("lose");
            resetScore();
            break;
    }
    moveToScreen();
    arduboy.display();
}

void printScore() {
    arduboy.setCursor(20, 0);
    arduboy.print(playerScore);
    arduboy.setCursor(101, 0);
    arduboy.print(computerScore);
}

void play() {
    // move the ball
    arduboy.fillRect(ballx, bally, ballSize, ballSize, WHITE);
    right == 1 ? ballx++ : ballx--;
    boolean playerHit = ballx == playerx + paddleWidth && playery < bally +
    ballSize && playery + paddleHeight > bally;
    boolean computerHit = ballx + ballSize == computerx && computery < bally +
    ballSize && computery + paddleHeight > bally;
    right = playerHit ? 1 : computerHit ? 0 : right;
    down == 1 ? bally++ : bally--;
    down = bally == 0 ? 1 : bally + ballSize == 63 ? 0 : down;
    // move player's paddle
    arduboy.fillRect(playerx, playery, paddleWidth, paddleHeight, WHITE);
    if (arduboy.pressed(UP_BUTTON) && playery > 0) {
        playery--;
    }
    if (arduboy.pressed(DOWN_BUTTON) && playery + paddleHeight < 63) {
        playery++;
    }
    // move computer's paddle
    arduboy.fillRect(computerx, computery, paddleWidth, paddleHeight, WHITE);
    if (ballx > 80 || rand() % 20 == 1) {
        bally < computery ? computery-- : bally + ballSize > computery +
        paddleHeight ? computery++ : computery = computery;
    }
}

void countScore() {
    if (ballx < - 10) {
        ballx = 64;
        right = 1;
        computerScore++;
    }
    if (ballx > 138) {
        ballx = 64;
        right = 0;
        playerScore++;
    }
    state = playerScore == 5 ? 2 : computerScore == 5 ? 3 : state;
}

void resetScore() {
    playerScore = 0;
    computerScore = 0;
    ballx = 64;
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
