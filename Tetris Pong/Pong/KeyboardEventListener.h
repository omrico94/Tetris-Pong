#pragma once
#define KBSIZE 2

struct KeyboardEventListener {
	virtual void handleKey(char k) = 0;
	virtual const char* getKbChars() = 0;

	virtual ~KeyboardEventListener() {} 
};