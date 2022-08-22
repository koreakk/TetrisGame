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