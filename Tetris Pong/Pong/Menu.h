#pragma once
#include "Game.h"
class Menu
{
public:
	void begining();
	void run();
	void startMenu();
	void secondMenu();
	void instructions();
	int chooselevel(char* side);
	enum { HUMVSHUM = '1', HUMVSCOM = '2', COMVSCOM = '3', RESUME = '4', INSTRUCTIONS = '8', EXIT = '9' };
	enum { NON = 1, BEST = 1, GOOD = 40, NOVICE = 10 };
};