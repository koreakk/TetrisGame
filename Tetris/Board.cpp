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
	printf(BORDER);
}

void DrawBlock(COLOR color)
{
	if (color == 0)
	{
		SetColor(WHITE);
		printf(SPACE);
	}
	else
	{
		SetColor(color);
		printf(BLOCK);
	}
}

void Draw()
{
	for (POS i = 0; i < BOARD_ROW_SIZE + 1; i++) {
		printf(SPACE);

		for (POS j = 0; j < BOARD_COL_SIZE + 2; j++)
		{
			if (!BoardSizeCheck(j - 1, i)) {
				DrawBorder();
				continue;
			}

			DrawBlock(board[i][j - 1]);
		}
		putchar('\n');
	}

	SetColor(WHITE);
}