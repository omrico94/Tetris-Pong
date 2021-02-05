#include "State.h"
#include "Cemetery.h"
#include "Board.h"

int State::bombSteps = 0;
int State::coltoerase = -1;

void State::missed(Ball & ball, const Cemetery & cm)
{
	while (coltoerase == -1)
	{
		if (incSteps() == 8)
			ball.changeState(Ball::BOMB);

		ball.move();
		Sleep(50);

		coltoerase = hitdeadb(ball, cm);
	}
}

int State::hitdeadb(Ball& ball, const Cemetery& cm)
{
	if ((ball.getLeftx() - 1 == 0) || (ball.getRightx() + 1 == 79))
	{
		if (ball.getLeftx() < Screen::MIDDLE_X)
			return 0;
		else
			return 19;
	}
	if (ball.getLeftx() < Screen::MIDDLE_X)
	{
		if ((cm.getchxy(ball.getNextLefty(), ball.getLeftx() - 1) == '#') || (cm.getchxy(ball.getNextLefty() + ball.getdir_y(), ball.getLeftx() - 1) == '#'))
			return (ball.getLeftx() - 1);
		else if ((cm.getchxy(ball.getNextLefty(), ball.getLeftx() - 2) == '#') || (cm.getchxy(ball.getLefty(), ball.getLeftx() - 2) == '#'))
			return (ball.getLeftx() - 2);
		else
			return -1;
	}
	else
	{
		if ((cm.getchxy(ball.getNextLefty(), ball.getRightx() + 1 - 60) == '#') || (cm.getchxy(ball.getNextLefty() + ball.getdir_y(), ball.getRightx() + 1 - 60) == '#'))
			return (ball.getRightx() + 1 - 60);
		else if ((cm.getchxy(ball.getNextLefty(), ball.getRightx() + 2 - 60) == '#') || (cm.getchxy(ball.getLefty(), ball.getRightx() + 2 - 60) == '#'))
			return (ball.getRightx() + 2 - 60);
		else
			return -1;
	}
}

int State::hit(int pos, Ball& ball, Cemetery& cm, Board* br)
{
	switch (pos)
	{
	case 2: // corner hit away
		ball.move();
		Sleep(50);
		ball.changedir_y();
		ball.changedir_x();
		ball.move();
		Sleep(50);
		break;
	case 3: // corner hit
		ball.animationMove(ball.getdir_y(), 0);
		break;
	case 1: // center hit
		ball.animationMove(0, ball.getdir_y());
		break;
	}

	ball.changeState(Ball::REGULAR);
	return 0;
}

int State::tetris(Cemetery & cm, Board * br)
{
	setColToErase();

	if (!(cm.tetris(*br)))//if there wasn't a full line
		br->move_aside(-cm.getmagicDir(), 1);//the oposite of magic dir is the dir the board need to go.


	if ((br->gettopx() >= 20) && (br->gettopx() <= 59))
		return 1;
	else
		return 0;
}

int State::incSteps()
{
	return (++bombSteps);
}
