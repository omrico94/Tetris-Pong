#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Board.h"
#include "KeyboardEventListener.h"

class UserBoard : public Board, public KeyboardEventListener
{
private:
	enum{kbdown, kbup};
	char kbChars[KBSIZE];
	
public:
	UserBoard(const Point& p0, const Point& p1, const Point& p2, char kb[], int cl) : Board( p0, p1, p2 , cl)  
	{
		kbChars[0] = kb[0];
		kbChars[1] = kb[1];
	}
	
	const char* getKbChars();
	void handleKey(char k);
};

