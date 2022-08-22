#include "stdafx.h"
#include "Tetromino.h"
#include "Board.h"

Tetromino::Tetromino(Block_Type _type)
	: x(0), y(0), type(_type), bMove(true),
	block(CreateBlockTable[_type]())
{
}

Tetromino::Tetromino(Block_Type _type, POS _x, POS _y)
	: x(_x), y(_y), type(_type), bMove(true),
	block(CreateBlockTable[_type]())
{
}

Tetromino::~Tetromino()
{
}

void Tetromino::SetBlockType(Block_Type _type)
{
	type = _type;
	block = CreateBlockTable[type]();
}

void Tetromino::Rotate(bool revers)
{
	block.Rotate(revers);
}

void Tetromino::Down()
{
	if (check(x, y + 1))
		y++;
	else {
		SaveBlock();
		SetBlockType(randomBlockType());
		SetPos();
	}
}

void Tetromino::Left()
{
	if (check(x - 1, y))
		x--;
}

void Tetromino::Right()
{
	if (check(x + 1, y))
		x++;
}


void Tetromino::DrawTetromino() const
{
	if (bMove)
		printf("x: %d\ny: %d", x, y);

	CPOSPTR dx = block.Getdx();
	CPOSPTR dy = block.Getdy();
	COLOR color = block.GetColor();

	for (int i = 0; i < 4; ++i)
		DrawBlock(x + dx[i], y + dy[i], BLOCK, color);
}

void Tetromino::DrawBlock(POS _x, POS _y, LPCSTR _ch, COLOR _Color) const
{
	COORD pos = { (_x + 1) << 1, _y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _Color);
	printf(_ch);
}

bool Tetromino::check(CPOS _x, CPOS _y) const
{
	CPOSPTR dx = block.Getdx();
	CPOSPTR dy = block.Getdy();

	POS x = 0;
	POS y = 0;

	for (int i = 0; i < 4; ++i) {
		x = _x + dx[i];
		y = _y + dy[i];

		if (!BoardSizeCheck(x, y))
			return false;

		if (board[y][x] != 0)
			return false;
	}
	
	return true;
}

void Tetromino::SaveBlock()
{
	CPOSPTR dx = block.Getdx();
	CPOSPTR dy = block.Getdy();
	COLOR color = block.GetColor();

	POS _x = 0;
	POS _y = 0;

	for (int i = 0; i < 4; ++i) {
		_x = x + dx[i];
		_y = y + dy[i];

		if (!BoardSizeCheck(_x, _y))
			continue;

		board[_y][_x] = color;
	}
}

void Tetromino::SetPos(POS _x, POS _y)
{
	x = _x;
	y = _y;
}