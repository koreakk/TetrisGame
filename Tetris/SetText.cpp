#include "stdafx.h"
#include "Block.h"
#include "Board.h"
#include "Tetromino.h"
#include "SetText.h"


void GotoXY(POS x, POS y)
{
	COORD pos = {x, y};
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
