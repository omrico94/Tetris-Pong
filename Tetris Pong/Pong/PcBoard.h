#pragma once
#include "Board.h"

class PcBoard: public Board
{
public:
	PcBoard(const Point& p0, const Point& p1, const Point& p2, int cl) : Board(p0, p1, p2, cl) {}
	void nextMove(const Ball& ball, int mistake);
	int calc(int x, int y, int m);
};
