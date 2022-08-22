#include "stdafx.h"
#include "Tetromino.h"
#include "SetText.h"
#include "Block.h"
#include "Board.h"

Tetromino::Tetromino()
	: x(4), y(0)
{
	type = randomBlockType();
	block = CreateBlockTable[type]();
}

Tetromino::Tetromino(Block_Type _type)
	: x(4), y(0), type(_type),
	block(CreateBlockTable[_type]())
{
}

Tetromino::Tetromino(Block_Type _type, POS _x, POS _y)
	: x(_x), y(_y), type(_type),
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

void Tetromino::SetBlockType()
{
	SetBlockType(randomBlockType());
}


void Tetromino::Rotate(bool reverse)
{
	block.Rotate(reverse);

	if (check())
		return;

	for (int i = 1; i <= 2; ++i) {
		// check right
		if (check(x - i, y)) {
			x -= i;
			return;
		}

		// check left
		if (check(x + i, y)) {
			x += i;
			return;
		}

		// check under
		if (check(x, y - i)) {
			y -= i;
			return;
		}
	}

	block.Rotate(!reverse);
}

void Tetromino::Down()
{
	if (check(x, y + 1))
		y++;
	else {
		SaveBlock();
		SetPos();
		SetBlockType();
	}
}

void Tetromino::Drop()
{
	while (check(x, y + 1)) y++;

	SaveBlock();
	SetPos();
	SetBlockType();
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
	
	printf("x : %d\ny : %d", x, y);

	CPOSPTR dx = block.Getdx();
	CPOSPTR dy = block.Getdy();
	COLOR color = block.GetColor();

	for (int i = 0; i < 4; ++i)
		DrawBlock(x + dx[i], y + dy[i], BLOCK, color);
}

void Tetromino::DrawBlock(POS _x, POS _y, LPCSTR _ch, COLOR _Color) const
{
	GotoXY((_x + 2) << 1, _y);
	SetColor(_Color);
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

bool Tetromino::check() const
{
	return check(x, y);
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