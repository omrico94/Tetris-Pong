#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Board.h"
#include "KeyboardManager.h"
#include <conio.h>
#include "Ball.h"
#include "Cemetery.h"
#include "Screen.h"
#include "UserBoard.h"
#include "PcBoard.h"

class Game
{
private:
	UserBoard brLeft, brRight;
	PcBoard pcLeft, pcRight;
	Ball ball;
	Cemetery cm[2];
	int counterk = 0;
	int counters = 0;
public:

	Game() :  brLeft{ { Screen::START_BOARD_1_X,10,'#' }, { Screen::START_BOARD_1_X,11,'#' }, { Screen::START_BOARD_1_X,12,'#' } ,"qa", 3 },
	brRight{ { Screen::START_BOARD_2_X,11,'#' },{ Screen::START_BOARD_2_X,12,'#' },{ Screen::START_BOARD_2_X,13,'#' } , "pl", 3 },
		pcLeft{ { Screen::START_BOARD_1_X,10,'#' },{ Screen::START_BOARD_1_X,11,'#' },{ Screen::START_BOARD_1_X,12,'#' } , 4 },
		pcRight{ { Screen::START_BOARD_2_X,11,'#' },{ Screen::START_BOARD_2_X,12,'#' },{ Screen::START_BOARD_2_X,13,'#' } , 4 },
		cm{ {0, -1},{60, 1} } {}

	int StartAGame(char status, int leftlevel, int rightlevel);
	void reset_game();
	void gameInitializion(Board** br, char status, KeyboardManager& kbm);

	void pcRMakesBomb(Board ** br, KeyboardManager& kbm, int distanceFromLeft);
	void pcLMakesBomb(Board ** br, KeyboardManager& kbm, int distanceFromRight);

	void middleScreen(Board** br, KeyboardManager& kbm, int& rightMistake, int& leftMistake, int rightlevel, int leftlevel, int& distanceFromRight, int& distanceFromLeft);
	void inck();
	void incs();
};

