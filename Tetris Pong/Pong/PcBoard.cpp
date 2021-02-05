#include "PcBoard.h"

void PcBoard::nextMove(const Ball & ball, int mistake)
{
	int nextY;

	if (gettopx() < Screen::MIDDLE_X)
	{
		if (ball.getLeftx() <= Screen::MIDDLE_X)
		{
			if (ball.getDirX() == -1)
			{
				if (mistake == 5)
					nextY = (calc(ball.getLeftx(), ball.getLefty(), (-1) * ball.getdir_y()) + mistake) % 21 + 4;
				else
					nextY = calc(ball.getLeftx(), ball.getLefty(), (-1) * ball.getdir_y());

				if (nextY < gettopy())
					Board::move(UP);
				else if (nextY > getbottomy())
					Board::move(DOWN);
			}
		}
	}

	else
	{
		if (ball.getRightx() >= Screen::MIDDLE_X)
		{
			if (ball.getDirX() == 1)
			{
				if (mistake == 5)
					nextY = (calc(ball.getRightx(), ball.getLefty(), ball.getdir_y()) + mistake) % 21 + 4;
				else
					nextY = calc(ball.getRightx(), ball.getLefty(), ball.getdir_y());

				if (nextY < gettopy())
					Board::move(UP);
				else if (nextY > getbottomy())
					Board::move(DOWN);
			}
		}
	}
}

int PcBoard::calc(int x, int y, int m)
{
	int hitY;
	hitY = y + m * (gettopx() - x);

	if (hitY < Screen::MIN_Y)
	{
		return ((Screen::MIN_Y - (hitY - Screen::MIN_Y)) % 24);
	}
	else if (hitY > Screen::MAX_Y)
	{
		return ((Screen::MAX_Y - (hitY - Screen::MAX_Y)) % 24);
	}
	else
	{
		return hitY;
	}
}
