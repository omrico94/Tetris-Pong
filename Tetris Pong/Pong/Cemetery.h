#pragma once

class Board;

class Cemetery
{
private:
	char mat[25][20];
	int magicNumber;
	int magicDir;
	enum { MIN_ROW = 4, MAX_ROW = 24, MIN_COL = 0, MAX_COL = 19 };
public:
	Cemetery(int mN, int mD);

	int getmagicNumber() const;
	int getmagicDir() const;
	int tetris(Board& br);
	void draw_dead_board(int x, int y, char ch);
	void insert_to_mat(int x, int y, char ch);
	void erase_dead_board(int x, int y);
	bool is_there_place(int x, int y);
	bool is_full_col(int x);
	void erase_full_col(int x, int real_x);
	void draw_cemetery(int x);
	void erase_cemetery();
	void one_col_back_left(int x);
	void one_col_back_right(int x);

	char getchxy(int x, int y) const;

};
