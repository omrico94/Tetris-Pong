#include "Board.h"
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void Board::move(int diry)
{
	SetConsoleTextAttribute(hConsole, color);

	int i;
	if(diry == UP)
	{
		if (br[0].gety() > Screen::MIN_Y)
		{
			br[2].erase();
			for (i = BOARD_SIZE - 1; i > 0; i--)
			{
				br[i] = br[i - 1];
			}
			br[0].move(0, UP);
			br[0].draw();
		}
	}
	else if (diry == DOWN)
	{
		if (br[2].gety() < Screen::MAX_Y)
		{
			br[0].erase();
			for (i = 0; i < BOARD_SIZE - 1; i++)
			{
				br[i] = br[i + 1];
			}
			br[2].move(0, DOWN);
			br[2].draw();
		}
	}
	SetConsoleTextAttribute(hConsole, 7);
}

void Board::drawBoard(char ch)
{
	int i;
	SetConsoleTextAttribute(hConsole, color);
	for (i = 0; i < BOARD_SIZE; i++)
	{
		br[i].draw(ch);
	}
	SetConsoleTextAttribute(hConsole, 7);
}

void Board::eraseBord()
{
	drawBoard(' ');
}


int Board::gettopx() const
{
	return br[0].getx();
}

int Board::gettopy() const
{
	return br[0].gety();
}

int Board::getbottomy() const
{
	return br[2].gety();
}

void Board::move_aside(int dir, int steps)
{
	int i;
	if ((gettopx() > 0) && (gettopx() < 79))
	{
		eraseBord();

		if ((steps == 5)||(gettopx() < Screen::MIDDLE_X && dir * steps == -1)||((gettopx() > Screen::MIDDLE_X) && (dir * steps == 1)))//draw the line in blue
		{
			SetConsoleTextAttribute(hConsole, 17);
			gotoxy(gettopx(), 3);
			cout << '-';
		}
		else//draw the line in red
			SetConsoleTextAttribute(hConsole, 204);

		for (i = 0; i < steps; i++)
		{
			br[0].move(dir, 0);
			br[1].move(dir, 0);
			br[2].move(dir, 0);

			gotoxy(gettopx(), 3);
			cout << '-';
		}

		drawBoard();

		SetConsoleTextAttribute(hConsole, 204);//paint the line in red
		gotoxy(gettopx(), 3);
		cout << '-';

		SetConsoleTextAttribute(hConsole, 7);

	}
}

//This function checks if and where the ball hits the board.
Board::BallPosition Board::check_hit(Ball & ball)
{
	int ball_pos;
	if (br[0].getx() <= 40)
		ball_pos = ball.getLeftx() - gettopx();
	else
		ball_pos = gettopx() - ball.getRightx();

	if (ball_pos == 2)
	{
		if ((ball.getLefty() >= gettopy()) && (ball.getLefty() <= getbottomy()))
			return BallPosition::CENTER_HIT;

		else if ((ball.getLefty() >= gettopy() - 1) && (ball.getLefty() <= getbottomy() + 1))
		{
			if ((ball.getNextLefty() >= gettopy()) && (ball.getNextLefty() <= getbottomy()))
				return BallPosition::CORNER_HIT;
			else if ((ball.getLefty() + 1 == Screen::MAX_Y) || (ball.getLefty() - 1 == Screen::MIN_Y))//center hit in the corner
				return BallPosition::CENTER_HIT;
			else
				return BallPosition::AWAY;
		}

		else if ((ball.getLefty() >= gettopy() - 2) && (ball.getLefty() <= getbottomy() + 2))
		{
			if ((ball.getNextLefty() >= gettopy() - 1) && (ball.getNextLefty() <= getbottomy() + 1))
				return BallPosition::CORNER_HIT_AWAY;
			else
				return BallPosition::AWAY;
		}

		else if ((ball.getLefty() >= gettopy() - 3) && (ball.getLefty() <= getbottomy() + 3))
		{
			if ((ball.getNextLefty() >= gettopy() - 2) && (ball.getNextLefty() <= getbottomy() + 2))
				return BallPosition::CORNER_HIT_AWAY;
			else
				return BallPosition::AWAY;
		}
		else
			return BallPosition::AWAY;
	}

	else if (ball_pos <= 1)
		return BallPosition::MISSED;

	else
		return BallPosition::AWAY;
}