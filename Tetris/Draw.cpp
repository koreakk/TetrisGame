#include "stdafx.h"
#include "Draw.h"

void GotoXY(POS x, POS y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void SetColor(COLOR color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void Draw(POS x, POS y, COLOR Color, LPCSTR Format, ...)
{
	va_list args;
	va_start(args, Format);

	int length = _vscprintf(Format, args) + 1;
	LPSTR pBuf = new CHAR[length];

	vsprintf_s(pBuf, length, Format, args);

	GotoXY(x, y);
	SetColor(Color);
	printf(pBuf);

	delete[] pBuf;
	va_end(args);
}

void Draw(POS x, POS y, LPCSTR Format, ...)
{
	va_list args;
	va_start(args, Format);

	int length = _vscprintf(Format, args) + 1;
	LPSTR pBuf = new CHAR[length];

	vsprintf_s(pBuf, length, Format, args);

	GotoXY(x, y);
	printf(pBuf);

	delete[] pBuf;
	va_end(args);
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

void DrawTetromino(const Tetromino& t)
{
	CPOS _x = t.GetX();
	CPOS _y = t.GetY();

	CPOSPTR dx = t.Getdx();
	CPOSPTR dy = t.Getdy();
	COLOR color = t.GetColor();

	POS x = 0;
	POS y = 0;
	for (int i = 0; i < 4; ++i)
	{
		x = _x + dx[i];
		y = _y + dy[i];

		Draw((x + 2) << 1, y, color, BLOCK);
	}
}