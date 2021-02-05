#pragma once
#include "State.h"
#include "Cemetery.h"

class Ball;
class Board;

class RegularBall: public State
{
private:
	enum { BLUE = 9 };
public:
	virtual void missed(Ball& ball, const Cemetery& cm) {}
	virtual int incSteps();
	int getcolor() { return BLUE; }
};

