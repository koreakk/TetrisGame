#include "stdafx.h"
#include "Board.h"

extern unsigned short board[BOARD_ROW_SIZE][BOARD_COL_SIZE] = { 0, };

bool BoardSizeCheck(POS x, POS y)
{
	return x >= 0 && x < BOARD_COL_SIZE && y >= 0 && y < BOARD_ROW_SIZE;
}


bool LineCheck(POS row)
{
	for (int i = 0; i < BOARD_COL_SIZE; ++i) {
		if (board[row][i] == 0)
			return false;
	}

	return true;
}

void RemoveLine(POS row)
{
	// line clear
	for (int i = 0; i < BOARD_COL_SIZE; ++i)
		board[row][i] = 0;

	// line update
	for (int i = row; i > 0; --i)
		memcpy(board[i], board[i - 1], sizeof(board[i]));
}

int RemoveLines()
{
	int count = 0;

	for (POS i = 0; i < BOARD_ROW_SIZE; ++i) {
		if (LineCheck(i)) {
			RemoveLine(i);
			count++;
		}
	}

	return count;
}

void ClearBorad()
{
	for (POS i = 0; i < BOARD_ROW_SIZE; ++i)
		memset(board[i], 0, sizeof(board[i]));
}