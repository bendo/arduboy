#include <Arduboy2.h>
#include "bitmaps.h"

Arduboy2 arduboy;

int state = 0;
int ball_x = 62;
int ball_y = 0;
int ball_size = 4;
int right = 1;
int down = 1;
int paddle_width = 4;
int paddle_height = 9;
int player_x = 0;
int player_y = 0;
int computer_x = WIDTH - paddle_width;
int computer_y = 0;
int player_score = 0;
int computer_score = 0;

void setup()
{
	arduboy.begin();
	arduboy.setFrameRate(60);
	arduboy.initRandomSeed();
}

void loop()
{
	if (!arduboy.nextFrame())
		return;

	arduboy.pollButtons();
	arduboy.clear();

	switch (state) {
		case 0:
			arduboy.drawBitmap(0, 0, intro, 128, 64, WHITE);
			reset_score();
			break;
		case 1:
			print_score(20, 0, 101, 0, 0);
			play();
			count_score();
			break;
		case 2:
			arduboy.drawBitmap(0, 0, win, 128, 64, WHITE);
			print_score(52, 37, 69, 37, 1);
			break;
		case 3:
			arduboy.drawBitmap(0, 0, lose, 128, 64, WHITE);
			print_score(52, 37, 69, 37, 1);
			break;
	}
	move_screen();
	arduboy.display();
}

void print_score(int px, int py, int cx, int cy, int final_score)
{
	arduboy.setCursor(px, py);
	arduboy.print(player_score);
	arduboy.setCursor(cx, cy);
	arduboy.print(computer_score);

	if (final_score) {
		arduboy.drawPixel(63, 39);
		arduboy.drawPixel(63, 42);
	}
}

void play()
{
	// move the ball
	arduboy.fillRect(ball_x, ball_y, ball_size, ball_size, WHITE);
	right == 1 ? ball_x++ : ball_x--;
	boolean playerHit = ball_x == player_x + paddle_width && player_y < ball_y +
	ball_size && player_y + paddle_height > ball_y;
	boolean computerHit = ball_x + ball_size == computer_x && computer_y < ball_y +
	ball_size && computer_y + paddle_height > ball_y;
	right = playerHit ? 1 : computerHit ? 0 : right;
	down == 1 ? ball_y++ : ball_y--;
	down = ball_y == 0 ? 1 : ball_y + ball_size == HEIGHT ? 0 : down;

	// move player's paddle
	arduboy.fillRect(player_x, player_y, paddle_width, paddle_height, WHITE);
	if (arduboy.pressed(UP_BUTTON) && player_y > 0)
		player_y--;

	if (arduboy.pressed(DOWN_BUTTON) && player_y + paddle_height < HEIGHT)
		player_y++;

	// move computer's paddle
	arduboy.fillRect(computer_x, computer_y, paddle_width, paddle_height, WHITE);
	if (ball_x > 110 || rand() % 20 == 1) {
		ball_y < computer_y ? computer_y-- : ball_y + ball_size > computer_y +
		paddle_height ? computer_y++ : computer_y = computer_y;
	}
}

void count_score()
{
	if (ball_x < -10) {
		ball_x = 64;
		right = 1;
		computer_score++;
	}
	if (ball_x > 138) {
		ball_x = 64;
		right = 0;
		player_score++;
	}
	state = player_score == 5 ? 2 : computer_score == 5 ? 3 : state;
}

void reset_score()
{
	player_score = 0;
	computer_score = 0;
	ball_x = 64;
}

void move_screen()
{
	if (arduboy.justPressed(A_BUTTON) && state != 1)
		state = state == 0 ? 1 : 0;
}
