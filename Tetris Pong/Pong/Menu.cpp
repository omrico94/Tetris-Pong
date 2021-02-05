#include "Menu.h"

//Manage the game
void Menu::run()
{
	Game game;
	int isGameStarted = 0;
	int gameover = 0;
	char ch = '0', status;
	int levelleft = NON, levelright = NON;

	begining();
	
	while (ch != EXIT)
	{
		if (gameover)
		{
			game.reset_game();
			system("cls");
			gotoxy(24, 10);
			cout << "Game Over! Press Esc to return menu" << endl;

			do { 
				ch = _getch();
			} while (ch != ESC);

			isGameStarted = 0; // new game 
			system("cls");
		}

		if (!isGameStarted)
		{
			gameover = 0; //new game
			
			startMenu();

			do {
				ch = _getch();
			} while (ch != HUMVSHUM && ch != HUMVSCOM && ch != COMVSCOM && ch != INSTRUCTIONS && ch != EXIT);

			switch (ch)
			{
			case HUMVSHUM:
				status = HUMVSHUM;
				gameover = game.StartAGame(status, NON, NON);
				isGameStarted = 1;//we started a game
				break;
			case HUMVSCOM:
				status = HUMVSCOM;
				levelright = chooselevel("right");
				if (levelright == ESC)
					break;
				gameover = game.StartAGame(status, NON, levelright);
				isGameStarted = 1;//we started a game
				break;
			case COMVSCOM:
				status = COMVSCOM;
				levelright = chooselevel("right");
				if (levelright == ESC)
				break;
				levelleft = chooselevel("left");
				if (levelleft == ESC)
					break;
				gameover = game.StartAGame(status, levelleft, levelright);
				isGameStarted = 1;//we started a game
				break;
			case INSTRUCTIONS:
				instructions();
				break;
			}
		}

		else
		{
			secondMenu();

			do {
				ch = _getch();
			} while (ch != HUMVSHUM && ch != HUMVSCOM && ch != COMVSCOM && ch != RESUME && ch != INSTRUCTIONS && ch != EXIT);
			
			switch (ch)
			{
			case HUMVSHUM:
				status = HUMVSHUM;
				game.reset_game();
				gameover = game.StartAGame(status, NON, NON);
				break;
			case HUMVSCOM:
				status = HUMVSCOM;
				game.reset_game();
				levelright = chooselevel("right");
				if (levelright == ESC)
					break;
				gameover = game.StartAGame(status, NON, levelright);
				break;
			case COMVSCOM:
				status = COMVSCOM;
				game.reset_game();
				levelright = chooselevel("right");
				if (levelright == ESC)
					break;
				levelleft = chooselevel("left");
				if (levelleft == ESC)
					break;
				gameover = game.StartAGame(status, levelleft, levelright);
				break;
			case RESUME:
				gameover = game.StartAGame(status,levelleft,levelright);
				break;
			case INSTRUCTIONS:
				instructions();
				break;
			}
		}
	}
	system("cls");
}

void Menu::startMenu()
{
	gotoxy(39, 7);
	cout << "MENU";

	gotoxy(22, 9);
	cout << "(1) Start a new game - Human vs Human";
	gotoxy(22, 10);
	cout << "(2) Start a new game - Human vs Computer";
	gotoxy(22, 11);
	cout << "(3) Start a new game - Computer vs Computer ";
	gotoxy(22, 12);
	cout << "(8) Present instructions and keys";
	gotoxy(22, 13);
	cout << "(9) EXIT";
}

void Menu::secondMenu()
{
	gotoxy(39, 7);
	cout << "MENU";

	gotoxy(22, 9);
	cout << "(1) Start a new game - Human vs Human";
	gotoxy(22, 10);
	cout << "(2) Start a new game - Human vs Computer";
	gotoxy(22, 11);
	cout << "(3) Start a new game - Computer vs Computer ";
	gotoxy(22, 12);
	cout << "(4) Resume game";
	gotoxy(22, 13);
	cout << "(8) Present instructions and keys";
	gotoxy(22, 14);
	cout << "(9) EXIT";
}

void Menu::instructions()
{
	char ch;
	system("cls");
	cout << "Hello Players!" << endl;
	cout << "Wellcome to our little game called Pong Tetris!" << endl << endl;
	cout << "In this game you can compete each other, play against the computer " << endl << "or watch the computer play against itself." << endl;
	cout << "In addition you can choose the level of the computer - Novice, Good or Best." << endl;
	cout << "Don't be so competitive, this is only a game ;)" << endl << endl;

	cout << "Lets start with some instructions :" << endl;
	cout << "Each player will have a board - small line on the left and on the right." << endl;
	cout << "You will see a ball running side to side on the screen and you will have to hit it with the help of your board." << endl;
	cout << "If you miss the ball, a copy of your board will drop to your side" << endl << "as in Tetris game." << endl;
	cout << "And then your board will move one step forward to the middle of the screen." << endl;
	cout << "If your board pass 1/4 of the screen you will lose the game!" << endl << endl;
	cout << "As in Tetris game, if you fill a full line with the \"dead\" boards the line will" << endl;
	cout << "disapear and the \"dead\" boards will go back one step backwards." << endl;
	cout << "If you succeed, your board will gain back five lines." << endl << endl;

	cout << "Furthermore, there is a trick that you and the computer can use :" << endl;
	cout << "turning the Ball into a Bomb!" << endl;
	cout << "Once you press on the right key, or if the computer decides -" << endl << "the Ball will turn into \"becoming a Bomb\" state for 8 movements." << endl;
	cout << "Then the ball will turn into a Bomb for 4 movements." << endl;
	cout << "When it's a \"becoming a Bomb\" state you can still hit it. If it's a Bomb you" << endl << "have to avoid it." << endl;
	cout << "If you couldn't avoid the Bomb your board will move 3 steps forward," << endl;
	cout << "and a copy of your board will drop to your side." << endl;
	cout << "If you succeded to avoid the bomb, the ball will continue its way till it" << endl << "hits a \"dead\" board." << endl;
	cout << "The column of the \"dead\" board that was hited will disappear and your" << endl << "board will gain back one line." << endl << endl;

	cout << "We are sure you want to know how to move your board and to use the bomb :" << endl;
	cout << "Left player :" << endl;
	cout << "UP - Q key" << endl << "DOWN - A key" << endl << "BOMB - S key" << endl;
	cout << "Right player :" << endl;
	cout << "UP - P key" << endl << "DOWN - L key" << endl << "BOMB - K key" << endl << endl;

	cout << "Thats it! We think you are ready to play Pong Tetris." << endl;
	cout << "have fun and enjoy the game!" << endl;
	cout << "press Esc to return to menu..." << endl;
	gotoxy(0, 0);

	do {
		ch = _getch();
	} while (ch != ESC);
	system("cls");
}

int Menu::chooselevel(char* side)
{
	char level;

	system("cls");
	gotoxy(22,7);
	cout << "Please choose a level to the " << side << " player:";
	gotoxy(37, 9);
	cout << "(1) Best";
	gotoxy(37, 10);
	cout << "(2) Good";
	gotoxy(37, 11);
	cout << "(3) Novice";
	gotoxy(37, 12);
	cout << "(ESC) MENU";

	level = _getch();
	while (true)
	{
		switch (level)
		{
		 case '1':
			 system("cls");
			return BEST;
		 case '2':
			 system("cls");
			 return GOOD;
		 case '3':
			 system("cls");
			 return NOVICE;
		 case ESC:
			 system("cls");
			 return ESC;
		 default:
			 level = _getch();
			 break;
		}	
	}
}

void Menu::begining()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 7);

	setcursor(0, 0);
	gotoxy(33, 10);
	cout << "P";
	Sleep(200);
	cout << "O";
	Sleep(200);
	cout << "N";
	Sleep(200);
	cout << "G";
	Sleep(200);
	cout << "  ";
	cout << "T";
	Sleep(200);
	cout << "E";
	Sleep(200);
	cout << "T";
	Sleep(200);
	cout << "R";
	Sleep(200);
	cout << "I";
	Sleep(200);
	cout << "S";
	Sleep(300);

	for (int i = 0; i < 14; i++)
	{
		SetConsoleTextAttribute(hConsole, i);
		system("cls");
		gotoxy(33, 10);
		cout << "PONG TETRIS";
		Sleep(100);
	}
	SetConsoleTextAttribute(hConsole, 7);
	Sleep(500);
	system("cls");
}
