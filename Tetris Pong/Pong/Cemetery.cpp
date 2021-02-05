#include "Cemetery.h"
#include "Board.h"

Cemetery::Cemetery(int mN, int mD)
{
	for (int i = 0; i <= MAX_ROW; i++)
		for (int j = MIN_COL; j <= MAX_COL; j++)
			mat[i][j] = ' ';
	magicNumber = mN;
	magicDir = mD;
}

int Cemetery::getmagicNumber() const
{
	return magicNumber;
}

int Cemetery::getmagicDir() const
{
	return magicDir;
}

//This function manage the part of the tetris.
int Cemetery::tetris(Board & br)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	int x, y, real_x;
	bool flag = true;
	x = br.gettopx();
	y = br.gettopy();

	x -= magicNumber;

	x += magicDir;
	real_x = br.gettopx() + magicDir;

	while (flag)
	{
		draw_dead_board(real_x, y, '#');
		insert_to_mat(x, y, '#');

		flag = is_there_place(x + magicDir, y);
		if (flag)
		{
			erase_dead_board(real_x, y);
			insert_to_mat(x, y, ' ');
			x += magicDir;
			real_x += magicDir;
		}
	}

	if (is_full_col(x))
	{
		
		erase_full_col(x, real_x);

		if(magicNumber == 0)
			one_col_back_left(x);
		else
			one_col_back_right(x);

		draw_cemetery(magicNumber);

		br.move_aside(magicDir, 5);

		SetConsoleTextAttribute(hConsole, 7);

		return 1; //Full line
	}
	return 0;//There wasn't a full line
}

void Cemetery::insert_to_mat(int x, int y, char ch)
{
	int i;
	for (i = y; i < (y + 3); i++)
	{
		mat[i][x] = ch;
	}
}

void Cemetery::draw_dead_board(int x, int y, char ch)
{
	int i;
	for (i = y; i < (y + 3); i++)
	{
		gotoxy(x, i);
		cout << ch;
		Sleep(5);
	}
}

void Cemetery::erase_dead_board(int x, int y)
{
	draw_dead_board(x, y, ' ');
}

//This function checks if the dead board can fall one more step back
bool Cemetery::is_there_place(int x, int y)
{
	bool flag = true;
	if (x < MIN_COL || x > MAX_COL)
		flag = false;
	for (int i = y; i < (y + 3) && flag; i++)
	{
		if (mat[i][x] == '#')
			flag = false;
	}
	return flag;
}

bool Cemetery::is_full_col(int x)
{
	int i;
	bool flag = true;
	for (i = MIN_ROW; i <= MAX_ROW && flag; i++)
	{
		if (mat[i][x] != '#')
			flag = false;
	}
	return flag;
}

void Cemetery::erase_full_col(int x, int real_x)
{
	int i;
	for (i = MIN_ROW; i <= MAX_ROW; i++)
	{
		mat[i][x] = ' ';
		gotoxy(real_x, i);
		cout << ' ';
	}
}

void Cemetery::draw_cemetery(int x)
{
	int i, j;

	for (i = MIN_ROW; i <= MAX_ROW; i++)
	{
		gotoxy(x, i);
		for (j = MIN_COL; j <= MAX_COL; j++)
		{
			cout << mat[i][j];
		}
	}
}

void Cemetery::erase_cemetery()
{
	int i, j;
	for (i = MIN_ROW; i <= MAX_ROW; i++)
		for (j = MIN_COL; j <= MAX_COL; j++)
			mat[i][j] = ' ';
}

//When tere is a full line moves all the boards one step back for the left player
void Cemetery::one_col_back_left(int x)
{
	int i, j;
	for(i = MIN_ROW; i <= MAX_ROW; i++)
		for (j = x; j < MAX_COL; j++)
		{
			mat[i][j] = mat[i][j + 1];
		}
	erase_full_col(MAX_COL, MAX_COL);
}

//When tere is a full line moves all the boards one step back for the right player
void Cemetery::one_col_back_right(int x)
{
	int i, j;
	for (i = MIN_ROW; i <= MAX_ROW; i++)
		for (j = x; j > 1; j--)
		{
			mat[i][j] = mat[i][j - 1];
		}
	erase_full_col(MIN_COL, magicNumber);
}

char Cemetery::getchxy(int x, int y) const
{
	return mat[x][y];
}
