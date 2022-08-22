#include "stdafx.h"
#include "Board.h"

extern unsigned short board[BOARD_ROW_SIZE][BOARD_COL_SIZE] = { 0, };

bool BoardSizeCheck(short x, short y)
{
	return x >= 0 && x < BOARD_COL_SIZE && y >= 0 && y < BOARD_ROW_SIZE;
}