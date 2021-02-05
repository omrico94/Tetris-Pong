#pragma once
#include "Point.h"
#include "Screen.h"
#include "KeyboardEventListener.h"
#include "RegularBall.h"
#include "State.h"
#include "BombBall.h"
#include "BecomingAbomb.h"

class Cemetery;
class Board;

class Ball: public KeyboardEventListener
{
private:
	State* state;
	RegularBall regb;
	BombBall bomb;
	BecomingAbomb bebomb;
	Point pLeft, pRight;
	int dir_x, dir_y;
	char kbChars[KBSIZE] = "";
	
public:
	enum { REGULAR, BECOMING, BOMB };

	Ball() : pLeft{ Screen::MIDDLE_X - 1, 10,'O' }, pRight{ Screen::MIDDLE_X, 10,'O' }, state(&regb)
	{
		dir_x = (rand() % 2) * 2 - 1;
		dir_y = (rand() % 2) * 2 - 1;
	}

	void missed(const Cemetery& cm);
	int hit(int state, Cemetery& cm, Board* br);
	int tetris(Cemetery& cm, Board* br);
	void incSteps();
	void changeState(int newstate); 
	State* getState() { return state; }

	void draw(char ch = 'O');
	void erase();
	void move();
	void resetBall();
	int getLeftx() const;
	int getRightx() const;
	int getLefty() const;
	int getNextLefty() const;
	int getDirX() const;
	void changedir_x();
	void changedir_y();
	void setDirX(int dir);

	void animationMove(int diry1, int diry2);
	void drawfirst(char ch = 'O');
	void drawsecond(char ch = 'O');
	void erasefirst();
	void erasesecond();
	int getdir_y() const;

	const char* getKbChars();
	virtual void setkbChars(char* ch);
	virtual void handleKey(char k);

};

