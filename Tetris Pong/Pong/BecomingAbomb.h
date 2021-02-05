#pragma once
#include "State.h"
#include "Cemetery.h"

class Ball;
class Board;

class BecomingAbomb: public State
{
private:
	enum {ORANGE=6};
public:
	int getcolor() { return ORANGE; }

};
