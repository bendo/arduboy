#include <Arduboy2.h>

Arduboy2 arduboy;

uint8_t position{0};

char strIn[17]{"0000000000000000"};

char strOut[6]{"00000"};

void print_logo();

void bin2dec();

void dec_to_str (char *str, uint16_t val, size_t digits);

void update_display();

uint16_t my_pow(uint8_t x, uint8_t n);

void setup()
{
	arduboy.begin();
	arduboy.setFrameRate(15);
	print_logo();
	update_display();
}

void loop()
{
	if (!(arduboy.nextFrame()))
		return;

	arduboy.pollButtons();

	if (arduboy.justPressed(LEFT_BUTTON))
		position > 0 ? position-- : position = 15;

	if (arduboy.justPressed(RIGHT_BUTTON))
		position < 15 ? position++ : position = 0;

	if (arduboy.justPressed(UP_BUTTON) || arduboy.justPressed(DOWN_BUTTON)) {
		strIn[position] ^= 0x01;
		bin2dec();
	}

	if (arduboy.justPressed(A_BUTTON)) {
		strncpy(strIn, "1111111111111111", 17);
		bin2dec();
	}

	if (arduboy.justPressed(B_BUTTON)) {
		strncpy(strIn, "0000000000000000", 17);
		bin2dec();
	}

	update_display();
}

void print_logo()
{
	arduboy.clear();
	arduboy.setCursor(41, 28);
	arduboy.print(F("bin2dec"));
	arduboy.display();
	delay(2000);
}

void bin2dec()
{
	size_t len = sizeof strIn / sizeof *strIn;
	uint16_t d = 0, j = 0;
	for (int i = len-2; i >= 0; i--) {
		d += (strIn[i] - '0') * my_pow(2, j);
		j++;
	}
	dec_to_str(strOut, d, 5);
}

void dec_to_str (char *str, uint16_t val, size_t digits)
{
	size_t i=1u;

	for (; i <= digits; i++) {
		str[digits-i] = (char)((val % 10u) + '0');
		val /= 10u;
	}
	str[i-1u] = '\0';
}

void update_display()
{
	arduboy.clear();
	arduboy.setCursor(16, 8);
	arduboy.print(strIn);
	arduboy.setCursor(16 + (position * 6), 16);
	arduboy.write('^');
	arduboy.setCursor(16, 32);
	arduboy.print(16 - position);
	arduboy.setCursor(80, 32);
	arduboy.print(strOut);
	arduboy.display();
}

uint16_t my_pow(uint8_t x, uint8_t n)
{
	uint16_t r = 1;
	if (n == 0)
		return 1;

	while (n != 0) {
		r *= x;
		n--;
	}
	return r;
}
