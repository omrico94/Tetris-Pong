#pragma once
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
#include <Windows.h>
#include <iostream>
#include "utils.h"

class Board;

class Screen {
public:
	enum {MAX_Y = 24, MIN_Y = 4, MIDDLE_X = 40 };
	enum {START_BOARD_1_X = 4, START_BOARD_1_Y = 10, START_BOARD_2_X = 75, START_BOARD_2_Y = 11};

	static void drawLine(const Board& brLeft, const Board& brRight, int counters, int counterk);
	static void drawBombLine(int counters, int counterk);
};
