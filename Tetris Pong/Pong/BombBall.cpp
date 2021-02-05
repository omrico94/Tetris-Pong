#include "BombBall.h"
#include "Ball.h"
#include "Cemetery.h"
#include "Board.h"

int BombBall::tetris(Cemetery & cm, Board * br)
{
	cm.erase_full_col(getcoltoerase(), cm.getmagicNumber() + getcoltoerase());

	if (cm.getmagicNumber() == 0)
		cm.one_col_back_left(getcoltoerase());
	else
		cm.one_col_back_right(getcoltoerase());

	cm.draw_cemetery(cm.getmagicNumber());
	br->drawBoard();
	setColToErase();

	if((br->gettopx() > Screen::START_BOARD_1_X)&&(br->gettopx() < Screen::START_BOARD_2_X))//if the board is in his start place dont go back!
		br->move_aside(cm.getmagicDir(), 1);

	return 0;
}

int BombBall::hit(int pos, Ball& ball, Cemetery& cm, Board* br)
{
	int gameover;
	ball.erase();
	ball.resetBall();
	gameover = ball.tetris(cm, br);
	ball.draw();

	if (!gameover)
	{
		br->move_aside(-cm.getmagicDir(), 1);

		if ((br->gettopx() >= 20) && (br->gettopx() <= 59))
			gameover = 1;
		else
		{
			br->move_aside(-cm.getmagicDir(), 1);

			if ((br->gettopx() >= 20) && (br->gettopx() <= 59))
				gameover = 1;
		}
	}
	return gameover;
}
