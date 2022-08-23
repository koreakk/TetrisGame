#include "stdafx.h"
#include "Draw.h"

static HANDLE	g_hScreenBuffer[2];
static int		g_ScreenIndex;

void ScreenInit()
{
	CONSOLE_CURSOR_INFO ConsoleCursor;

	ConsoleCursor.bVisible = FALSE;
	ConsoleCursor.dwSize   = 1;
	
	g_hScreenBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	g_hScreenBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	
	SetConsoleCursorInfo(g_hScreenBuffer[0], &ConsoleCursor);
	SetConsoleCursorInfo(g_hScreenBuffer[1], &ConsoleCursor);

	SetConsoleTitleA(TITLE);
	SetScreenSize(SCREEN_COL_SIZE, SCREEN_ROW_SIZE);
}

void ScreenFlipping()
{
	SetConsoleActiveScreenBuffer(g_hScreenBuffer[g_ScreenIndex]);
	g_ScreenIndex = (g_ScreenIndex == 0) ? 1 : 0;
}

void ScreenClear()
{
	unsigned int size = 100 * 100;

	DWORD dw = 0;
	COORD pos = { 0, 0 };

	FillConsoleOutputCharacterA(g_hScreenBuffer[g_ScreenIndex], ' ', size, pos, &dw);
	FillConsoleOutputAttribute(g_hScreenBuffer[g_ScreenIndex], 0, size, pos, &dw);
}

void ScreenRelease()
{
	CloseHandle(g_hScreenBuffer[0]);
	CloseHandle(g_hScreenBuffer[1]);
}

void SetScreenSize(unsigned int width, unsigned int height)
{
	CHAR buffer[50] = { 0, };
	sprintf_s(buffer, 50, "mode con cols=%d lines=%d", width, height);
	system(buffer);

	COORD size = { static_cast<SHORT>(width), static_cast<SHORT>(height) };
	SMALL_RECT rect = { 0, };

	rect.Right  = size.X - 1;
	rect.Bottom = size.Y - 1;
	rect.Left   = 0;
	rect.Top    = 0;

	SetConsoleScreenBufferSize(g_hScreenBuffer[0], size);
	SetConsoleScreenBufferSize(g_hScreenBuffer[1], size);

	SetConsoleWindowInfo(g_hScreenBuffer[0], TRUE, &rect);
	SetConsoleWindowInfo(g_hScreenBuffer[1], TRUE, &rect);
}

void GotoXY(POS x, POS y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(g_hScreenBuffer[g_ScreenIndex], pos);
}

void SetColor(COLOR color)
{
	SetConsoleTextAttribute(g_hScreenBuffer[g_ScreenIndex], color);
}

void Draw(POS x, POS y, COLOR Color, LPCSTR Format, ...)
{
	va_list args;
	va_start(args, Format);

	int length = _vscprintf(Format, args);
	LPSTR pBuf = new CHAR[length + 1];

	vsprintf_s(pBuf, (size_t)length + 1, Format, args);

	SetColor(Color);
	GotoXY(x, y);
	HANDLE hCurrentBuffer = g_hScreenBuffer[g_ScreenIndex];

	DWORD dw;
	//COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };

	//FillConsoleOutputAttribute(hCurrentBuffer, 0, length, pos, &dw);
	//WriteConsoleOutputCharacterA(hCurrentBuffer, pBuf, length, pos, &dw);

	WriteFile(hCurrentBuffer, pBuf, length, &dw, NULL);

	delete[] pBuf;
	va_end(args);
}

void Draw(POS x, POS y, LPCSTR Format, ...)
{
	va_list args;
	va_start(args, Format);

	int length = _vscprintf(Format, args);
	LPSTR pBuf = new CHAR[length + 1];

	vsprintf_s(pBuf, (size_t)length + 1, Format, args);

	GotoXY(x, y);

	HANDLE hCurrentBuffer = g_hScreenBuffer[g_ScreenIndex];

	DWORD dw;
	//COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };

	//FillConsoleOutputAttribute(hCurrentBuffer, 0, length, pos, &dw);
	//WriteConsoleOutputCharacterA(hCurrentBuffer, pBuf, length, pos, &dw);
	
	WriteFile(hCurrentBuffer, pBuf, length, &dw, NULL);

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