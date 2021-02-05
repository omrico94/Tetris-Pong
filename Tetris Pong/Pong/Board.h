#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include "Point.h"
#include "Ball.h"

#define BOARD_SIZE 3

class Board
{
private:	
	Point br[BOARD_SIZE];
	int color;

public:
	enum class BallPosition { MISSED, CENTER_HIT, CORNER_HIT_AWAY, CORNER_HIT, AWAY };
	Board(const Point& p0, const Point& p1, const Point& p2, int cl) : br{ p0, p1, p2 }, color(cl) {}
	
	void move(int diry);
	void drawBoard(char ch = '#');
	void eraseBord();
	int gettopx() const;
	int gettopy() const;
	int getbottomy() const;
	void move_aside(int dir, int steps);
	BallPosition check_hit(Ball& ball);
	virtual void nextMove(const Ball& ball, int mistake) {};

	virtual ~Board() {}
};
