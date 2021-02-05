#include "UserBoard.h"

//This function gets a diraction.
//The function sets and draws the point.

const char* UserBoard::getKbChars()
{
	return kbChars;
}

void UserBoard::handleKey(char k)
{
	if (k == kbChars[0])
		Board::move(UP);
	else if (k == kbChars[1])
		Board::move(DOWN);
}