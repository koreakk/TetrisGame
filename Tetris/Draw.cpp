#include "stdafx.h"
#include "Draw.h"

static HANDLE	ScreenBuffer[2];
static int		ScreenIndex;

void ScreenInit()
{
	COORD size = { SCREEN_COL_SIZE, SCREEN_ROW_SIZE };
	SMALL_RECT rect;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	rect.Bottom = SCREEN_ROW_SIZE - 1;
	rect.Right  = SCREEN_COL_SIZE - 1;
	rect.Top    = 0;
	rect.Left   = 0;

	ConsoleCursor.bVisible = FALSE;
	ConsoleCursor.dwSize   = 1;
	
	ScreenBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	ScreenBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	SetConsoleScreenBufferSize(ScreenBuffer[0], size);
	SetConsoleScreenBufferSize(ScreenBuffer[1], size);

	SetConsoleWindowInfo(ScreenBuffer[0], TRUE, &rect);
	SetConsoleWindowInfo(ScreenBuffer[1], TRUE, &rect);
	
	SetConsoleCursorInfo(ScreenBuffer[0], &ConsoleCursor);
	SetConsoleCursorInfo(ScreenBuffer[1], &ConsoleCursor);
}

void ScreenFlipping()
{
	SetConsoleActiveScreenBuffer(ScreenBuffer[ScreenIndex]);
	ScreenIndex = (ScreenIndex + 1) % 2;
}

void ScreenClear()
{
	COORD pos = { 0, 0 };
	DWORD dw;
	FillConsoleOutputCharacterA(ScreenBuffer[ScreenIndex], ' ', SCREEN_ROW_SIZE * SCREEN_COL_SIZE, pos, &dw);
}

void ScreenRelease()
{
	CloseHandle(ScreenBuffer[0]);
	CloseHandle(ScreenBuffer[1]);
}

void GotoXY(POS x, POS y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(ScreenBuffer[ScreenIndex], pos);
}

void SetColor(COLOR color)
{
	SetConsoleTextAttribute(ScreenBuffer[ScreenIndex], color);
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

	DWORD dw;
	WriteFile(ScreenBuffer[ScreenIndex], pBuf, length - 1, &dw, NULL);

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

	DWORD dw;
	WriteFile(ScreenBuffer[ScreenIndex], pBuf, length - 1, &dw, NULL);

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