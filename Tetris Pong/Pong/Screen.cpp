#include "Screen.h"
#include "Board.h"
using namespace std;


void Screen::drawLine(const Board& brLeft, const Board& brRight, int counters, int counterk)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 17);
	int i;
	for (i = 0; i < 80; i++)
	{
		if ((i <= brLeft.gettopx()) || (i >= brRight.gettopx()))
			SetConsoleTextAttribute(hConsole, 204);
		else
			SetConsoleTextAttribute(hConsole, 17);
		if ((i == 20) || (i == 59))
			SetConsoleTextAttribute(hConsole, 375);

		gotoxy(i, 3);
		cout << '-';
		SetConsoleTextAttribute(hConsole, 17);
	}

	//draws the bomb line
	SetConsoleTextAttribute(hConsole, 7);
	gotoxy(2, 0);
	cout << "BOMB";
	gotoxy(73, 0);
	cout << "BOMB";

	drawBombLine(counters, counterk);
	SetConsoleTextAttribute(hConsole, 7);

}

void Screen::drawBombLine(int counters, int counterk)
{
	int i;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (counters == 0)
	{
		SetConsoleTextAttribute(hConsole, 170);
		gotoxy(2, 1);
		cout << "    ";
	}
	else
	{
		gotoxy(2, 1);
		for (i = 0; i < counters - 1; i++)
		{
			SetConsoleTextAttribute(hConsole, 170);
			cout << " ";
		}
		for (i = counters - 1; i < 4; i++)
		{
			SetConsoleTextAttribute(hConsole, 375);
			cout << " ";
		}
	}

	if (counterk == 0)
	{
		SetConsoleTextAttribute(hConsole, 170);
		gotoxy(73, 1);
		cout << "    ";
	}
	else
	{
		gotoxy(73, 1);
		for (i = 4; i > counterk - 1; i--)
		{
			SetConsoleTextAttribute(hConsole, 375);
			cout << " ";
		}
		for (i = 0; i < counterk - 1; i++)
		{
			SetConsoleTextAttribute(hConsole, 170);
			cout << " ";
		}
	}
}