#pragma once
#include "State.h"

class Ball;
class Board;

class BombBall: public State
{
private:
	enum { RED = 4 };
public:

	virtual int tetris(Cemetery& cm, Board* br);
	int getcolor() { return RED; }
	virtual int hit(int pos, Ball& ball, Cemetery& cm, Board* br);
};
