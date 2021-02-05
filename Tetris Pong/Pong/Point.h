#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "utils.h"
using namespace std;
#define UP -1
#define DOWN 1
#define LEFT -1
#define RIGHT 1

class Point
{
private:
	int x, y;
	char ch;
public:
	Point(int x, int y, char ch) : x(x), y(y), ch(ch) {}
	void draw();
	void erase();
	void draw(char ch);
	void move(int dir_x, int dir_y);
	int getx() const { return x; }
	int gety() const { return y; }

};