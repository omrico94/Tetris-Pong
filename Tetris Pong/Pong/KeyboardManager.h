#pragma once

#include <list>
#include "Board.h"
#include "UserBoard.h"
#include "KeyboardEventListener.h"

class KeyboardManager
{
	// TODO: in the future we will hold KeyboardEventListener
	// but since we didn't learn inheritance yet, we just hold the actual type for now
	enum {NUM_CHARS = 26};
	// an array of 'char' => list of kbListener
	std::list<KeyboardEventListener*> kbListeners[NUM_CHARS];

	// helper method - get index in array per a given char
	int getIndex(char c)
	{
		int index = c - 'a';
		if (index < 0 || index >= NUM_CHARS) 
		{
			index = c - 'A';
			if (index < 0 || index >= NUM_CHARS)
			{
				if (c == ESC)
					return ESC;
				else
					return -1;
			}
		}
		return index;
	}
public:
	void registerKbListener(KeyboardEventListener* pKbListener);
	int handleKeyboard(int & counters, int & counterk);
};