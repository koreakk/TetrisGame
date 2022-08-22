#include "stdafx.h"
#include "Board.h"
#include "SetText.h"
#include "Tetromino.h"

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


void DrawBorder()
{
	SetColor(WHITE);
	for (POS i = 0; i < BOARD_ROW_SIZE; ++i)
	{
		Draw(2, i, BORDER);
		Draw((BOARD_COL_SIZE + 2) << 1, i, BORDER);
	}

	for (POS i = 0; i < BOARD_COL_SIZE + 2; ++i)
	{
		Draw((i + 1) << 1, BOARD_ROW_SIZE, BORDER);
	}
}

void DrawBlock()
{
	for (POS i = 0; i < BOARD_ROW_SIZE; ++i) {
		for (POS j = 0; j < BOARD_COL_SIZE; ++j) {
			if (board[i][j] == 0)
				continue;

			Draw((j + 2) << 1, i, (COLOR)board[i][j], BLOCK);
		}
	}
}
