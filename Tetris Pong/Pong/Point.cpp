#include "Point.h"

void Point::draw()
{
	draw(ch);
}

void Point::draw(char ch)
{
	setcursor(0, 0);
	gotoxy(x, y);
	cout << ch;
}

void Point::move(int dir_x = 0, int dir_y = 0)
{
	x += dir_x;
	y += dir_y;
}

void Point::erase()
{
	draw(' ');
}