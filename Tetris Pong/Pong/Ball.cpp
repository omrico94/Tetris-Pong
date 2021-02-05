#include "Ball.h"
#include "Board.h"
#include "Cemetery.h"


void Ball::missed(const Cemetery& cm)
{
	state->missed(*this, cm);
}

int Ball::hit(int pos, Cemetery& cm, Board* br)
{
	return state->hit(pos, *this, cm, br);
}

int Ball::tetris(Cemetery& cm, Board * br)
{
	return (state->tetris(cm, br));
}

void Ball::incSteps()
{
	int steps = state->incSteps();
	if (steps == 8)
		state = &bomb;
	else if (steps == 12)
	{
		state->setSteps();
		state = &regb;
	}
}

void Ball::changeState(int newstate)
{
	switch (newstate)
	{
	case REGULAR:
		state = &regb;
		break;
	case BECOMING:
		state = &bebomb;
		break;
	case BOMB:
		state = &bomb;
		break;
	}
}

void Ball::draw(char ch)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, state->getcolor());
	Point tempLeft = pLeft;
	Point tempRight = pRight;

	pLeft.draw(ch);
	pRight.draw(ch);
	
	tempLeft.move(0, UP);
	tempRight.move(0, UP);
	tempLeft.draw(ch);
	tempRight.draw(ch);

	tempLeft.move(LEFT, DOWN);
	tempRight.move(RIGHT, DOWN);

	
	tempLeft.draw(ch);
	tempRight.draw(ch);

	tempLeft.move(RIGHT, DOWN);
	tempRight.move(LEFT, DOWN);
	tempLeft.draw(ch);
	tempRight.draw(ch);
	SetConsoleTextAttribute(hConsole, 7);
}

void Ball::erase()
{
	draw(' ');
}

void Ball::move()
{
	if ((pLeft.gety() > Screen::MAX_Y - 2) || (pLeft.gety() < Screen::MIN_Y + 2))
	{
		dir_y *= (-1);
	}

	erase();
	pLeft.move(dir_x, dir_y);
	pRight.move(dir_x, dir_y);
	draw();
}

void Ball::resetBall()
{
	int y = rand() % 16 + 6;
	pLeft = { Screen::MIDDLE_X - 1, y,'O' };
	pRight = { Screen::MIDDLE_X, y,'O' };
	dir_x = rand() % 2 * 2 - 1;
	dir_y = rand() % 2 * 2 - 1;
	state->setSteps();
	state = &regb;
}

int Ball::getLeftx() const
{
	return pLeft.getx();
}

int Ball::getRightx() const
{
	return pRight.getx();
}

int Ball::getLefty() const
{
	return pLeft.gety();
}

int Ball::getNextLefty() const
{
	return getLefty() + dir_y;
}

int Ball::getDirX() const
{
	return dir_x;
}

void Ball::changedir_x()
{
	dir_x *= (-1);
}

void Ball::changedir_y()
{

	dir_y *= (-1);
}

void Ball::setDirX(int dir)
{
	dir_x = dir;
}

int Ball::getdir_y() const 
{
	return dir_y;
}

void Ball::animationMove(int diry1, int diry2)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (getLefty() > 5 && getLefty() < 23)
	{
		erase();
		SetConsoleTextAttribute(hConsole, state->getcolor());
		pLeft.move(dir_x, diry1);
		pRight.move(dir_x, diry1);

		drawfirst();
		Sleep(50);
		erasefirst();
	}

	changedir_x();
	if (diry2 == 0)
		changedir_y();

	if (getLefty() > 5 && getLefty() < 23)
	{
		pLeft.move(dir_x, diry2);
		pRight.move(dir_x, diry2);

		drawsecond();
		Sleep(50);
		erasesecond();
		SetConsoleTextAttribute(hConsole, 7);
	}
}

void Ball::drawfirst(char ch)
{

	Point tempLeft = pLeft;
	Point tempRight = pRight;

	pLeft.draw(ch);
	pRight.draw(ch);

	tempLeft.move(0, DOWN*dir_y);
	tempRight.move(0, DOWN*dir_y);
	tempLeft.draw(ch);
	tempRight.draw(ch);

	tempLeft.move(LEFT, UP*dir_y);
	tempRight.move(RIGHT, UP*dir_y);

	if (dir_x == 1)
	{
		tempLeft.draw(ch);
		tempLeft.move(RIGHT, UP*dir_y);
		tempRight.move(LEFT, UP*dir_y);
		tempRight.draw(ch);

	}
	else
	{
		tempRight.draw(ch);
		tempLeft.move(RIGHT, UP*dir_y);
		tempRight.move(LEFT, UP*dir_y);
		tempLeft.draw(ch);
	}
}

void Ball::drawsecond(char ch)
{
	Point tempLeft = pLeft;
	Point tempRight = pRight;

	pLeft.draw(ch);
	pRight.draw(ch);

	if (dir_y == 1)
	{
		tempLeft.move(0, DOWN);
		tempRight.move(0, DOWN);
		tempLeft.draw(ch);
		tempRight.draw(ch);

		tempLeft.move(LEFT, UP);
		tempRight.move(RIGHT, UP);
		tempLeft.draw(ch);
		tempRight.draw(ch);

		tempLeft.move(RIGHT, UP);
		tempRight.move(LEFT, UP);

		if (dir_x == -1)
		{
			tempRight.draw(ch);
			tempRight.move(RIGHT, 0);
			tempRight.draw(ch);
		}
		else
		{
			tempLeft.draw(ch);
			tempLeft.move(LEFT, 0);
			tempLeft.draw(ch);
		}
	}
	else
	{
		tempLeft.move(0, UP);
		tempRight.move(0, UP);
		tempLeft.draw(ch);
		tempRight.draw(ch);

		tempLeft.move(LEFT, DOWN);
		tempRight.move(RIGHT, DOWN);
		tempLeft.draw(ch);
		tempRight.draw(ch);

		tempLeft.move(RIGHT, DOWN);
		tempRight.move(LEFT, DOWN);

		if (dir_x == -1)
		{
			tempRight.draw(ch);
			tempRight.move(RIGHT, 0);
			tempRight.draw(ch);
		}
		else
		{
			tempLeft.draw(ch);
			tempLeft.move(LEFT, 0);
			tempLeft.draw(ch);
		}
	}
}

void Ball::erasefirst()
{
	drawfirst(' ');
}

void Ball::erasesecond()
{
	drawsecond(' ');
}

const char* Ball::getKbChars()
{
	return kbChars;
}

void Ball::setkbChars(char * ch)
{
	kbChars[0] = ch[0];
	kbChars[1] = ch[1];
}

void Ball::handleKey(char k)
{
	if (typeid(*state) == typeid(regb))
	{
		state = &bebomb;
	}
}

