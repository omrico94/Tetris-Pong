#include "Game.h"

int Game::StartAGame(char status, int leftlevel, int rightlevel)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	KeyboardManager kbm;
	int Esc = false;
	int gameover = 0;
	int leftMistake = 0, rightMistake = 0;
	int isBomb = 0;
	int distanceFromRight = 0, distanceFromLeft = 0; //Where the pc decide to make bomb
	Board::BallPosition state[2];
	Board* br[2];
	
	gameInitializion(br, status, kbm);
	
	while (true)//Breaks when game over or ESC
	{
		for (int i = 0; (i < 10 && !Esc); i++)
		{
			Esc = kbm.handleKeyboard(counters, counterk);
			Sleep(5);
		}

		if (Esc)
			break;

		middleScreen(br, kbm, rightMistake, leftMistake, rightlevel, leftlevel, distanceFromRight, distanceFromLeft);

		pcRMakesBomb(br, kbm, distanceFromLeft);
		pcLMakesBomb(br, kbm, distanceFromRight);

		br[0]->nextMove(ball, leftMistake);
		br[1]->nextMove(ball, rightMistake);

		state[0] = br[0]->check_hit(ball);
		state[1] = br[1]->check_hit(ball);

		for (int i = 0; i < 2; i++)
		{
			switch (state[i])
			{
			case Board::BallPosition::AWAY:
				break;
			case Board::BallPosition::MISSED:
				ball.missed(cm[i]);
				ball.erase();
				gameover = ball.tetris(cm[i], br[i]);
				
				if (typeid(*ball.getState()) == typeid(BombBall))
					isBomb = 1;

				ball.resetBall();
				ball.draw();

				if (isBomb)//if the board missed a bomb ball the direction changes to the opponent.
					ball.setDirX(-cm[i].getmagicDir());

				if (gameover)
					return gameover;
				break;
			default:
				gameover = ball.hit((int)state[i], cm[i], br[i]);
				if (gameover)
					return gameover;
				break;
			}
		}

		ball.incSteps();
		ball.move();
	}
	system("cls");
	return gameover;
}

void Game::reset_game()
{
	brLeft = { { Screen::START_BOARD_1_X,10,'#' },{ Screen::START_BOARD_1_X,11,'#' },{ Screen::START_BOARD_1_X,12,'#' } , "qa", 3 };
	brRight = { { Screen::START_BOARD_2_X,11,'#' },{ Screen::START_BOARD_2_X,12,'#' },{ Screen::START_BOARD_2_X,13,'#' } , "pl", 3 };
	pcLeft = { { Screen::START_BOARD_1_X,10,'#' },{ Screen::START_BOARD_1_X,11,'#' },{ Screen::START_BOARD_1_X,12,'#' } , 4 };
	pcRight = { { Screen::START_BOARD_2_X,11,'#' },{ Screen::START_BOARD_2_X,12,'#' },{ Screen::START_BOARD_2_X,13,'#' } , 4 };
	ball.resetBall();
	cm[0].erase_cemetery();
	cm[1].erase_cemetery();
	counters = 0;
	counterk = 0;
}

void Game::gameInitializion(Board ** br, char status, KeyboardManager& kbm)
{

	system("cls");
	gotoxy(35, 1);
	cout << "PONG TETRIS";

	cm[0].draw_cemetery(cm[0].getmagicNumber());
	cm[1].draw_cemetery(cm[1].getmagicNumber());
	
	if (status == '1')
	{
		kbm.registerKbListener(&brLeft);
		kbm.registerKbListener(&brRight);
		br[0] = &brLeft;
		br[1] = &brRight;
		ball.setkbChars("sk");
	}
	if (status == '2')
	{
		kbm.registerKbListener(&brLeft);
		br[0] = &brLeft;
		br[1] = &pcRight;
		ball.setkbChars("s");
	}
	if (status == '3')
	{
		br[0] = &pcLeft;
		br[1] = &pcRight;
		ball.setkbChars("");
	}

	Screen::drawLine(*br[0], *br[1], counters, counterk);

	br[0]->drawBoard();
	br[1]->drawBoard();

	ball.draw();
	kbm.registerKbListener(&ball);
}


void Game::pcRMakesBomb(Board** br, KeyboardManager& kbm, int distanceFromLeft)
{ 
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if ((typeid(*br[1]) == typeid(PcBoard)) && (ball.getLeftx() == distanceFromLeft) && (ball.getDirX() == -1))
	{
		if (counterk == 0)
		{
			if (rand() % 4 == 0)
			{
				ball.changeState(Ball::BECOMING);
				SetConsoleTextAttribute(hConsole, 375);
				gotoxy(73, 1);
				cout << "    ";
				SetConsoleTextAttribute(hConsole, 7);
				counterk = 1;
			}
		}
	}
}

void Game::pcLMakesBomb(Board** br, KeyboardManager& kbm, int distanceFromRight)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if ((typeid(*br[0]) == typeid(PcBoard)) && (ball.getRightx() == distanceFromRight) && (ball.getDirX() == 1))
	{
		if (counters == 0)
		{
			if (rand() % 4 == 0)
			{
				ball.changeState(Ball::BECOMING);
				SetConsoleTextAttribute(hConsole, 375);
				gotoxy(2, 1);
				cout << "    ";
				SetConsoleTextAttribute(hConsole, 7);
				counters = 1;
			}
		}	
	}
}

void Game::middleScreen(Board ** br, KeyboardManager & kbm, int & rightMistake, int & leftMistake, int rightlevel, int leftlevel, int& distanceFromRight, int& distanceFromLeft)
{
	if ((ball.getRightx() == Screen::MIDDLE_X + 1) && (ball.getDirX() == 1))//the ball is in the middle of the screen and moves right.
	{
		rightMistake = rand() % rightlevel;//rand num only once in a game iteration, if the right board needs to miss the ball.
										   //count the iteretions that the ball is a bomb for every board.
		inck();
		incs();

		//The right pc decide where to make the bomb.
		if (leftlevel == 1)
			distanceFromRight = br[1]->gettopx() - 12; //if it's the best level - a wise decision.
		else
			distanceFromRight = rand() % (br[1]->gettopx() - ball.getRightx()) + ball.getRightx();
	}

	else if ((ball.getRightx() == Screen::MIDDLE_X - 1) && (ball.getDirX() == -1))//the ball is in the middle of the screen and moves left.
	{
		leftMistake = rand() % leftlevel;//rand num only once in game iteration, if the left board needs to miss the ball.
										 //count the iteretions that the ball is a bomb for every board.
		inck();
		incs();

		//The left pc decide where to make the bomb.
		if (rightlevel == 1)
			distanceFromLeft = br[0]->gettopx() + 12;//if it's the best level - a wise decision.
		else
			distanceFromLeft = rand() % (ball.getLeftx() - br[0]->gettopx()) + br[0]->gettopx();
	}
}

void Game::inck()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (counterk != 0)
	{
		SetConsoleTextAttribute(hConsole, 170);
		gotoxy(79 - counterk - 2, 1);
		counterk++;
		cout << " ";
	}
	if (counterk == 5)
		counterk = 0;
}

void Game::incs()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if ((counters != 0) && (counters != 5))
	{
		SetConsoleTextAttribute(hConsole, 170);
		gotoxy(counters + 1, 1);
		counters++;
		cout << " ";
	}
	if (counters == 5)
		counters = 0;
}
