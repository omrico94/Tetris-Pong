#pragma once

class Ball;
class Cemetery;
class Board;

class State
{
private:
	static int bombSteps;
	static int coltoerase;
public:
	State() { bombSteps = 0; }
	virtual void missed(Ball& ball, const Cemetery& cm);
	virtual int tetris(Cemetery& cm, Board* br);
	virtual int incSteps();
	void setSteps() { bombSteps = 0; }
	void setColToErase() { coltoerase = -1; }
	int hitdeadb(Ball& ball, const Cemetery& cm);
	int getcoltoerase() { return coltoerase; }
	virtual int getcolor() = 0;
	virtual int hit(int pos, Ball& ball, Cemetery& cm, Board* br);

	virtual ~State() {}
	
};

