#include "stdafx.h"
#include "Tetromino.h"

Tetromino::Tetromino()
	: x(4), y(0), bHold(true),
	block(nullptr),
	HoldBlock(nullptr)
{
	Block_Type type = randomBlockType();
	block = CreateBlockTable[type]();

}

Tetromino::Tetromino(Block_Type _type)
	: x(4), y(0), bHold(true),
	block(CreateBlockTable[_type]()),
	HoldBlock(nullptr)
{
}

Tetromino::Tetromino(Block_Type _type, POS _x, POS _y)
	: x(_x), y(_y), bHold(true),
	block(CreateBlockTable[_type]()),
	HoldBlock(nullptr)
{
}

Tetromino::~Tetromino()
{
	if (block != nullptr)
		delete block;
	if (HoldBlock != nullptr)
		delete HoldBlock;

	block = nullptr;
	HoldBlock = nullptr;
}

void Tetromino::SetPos(CPOS _x, CPOS _y)
{
	x = _x;
	y = _y;
}

void Tetromino::SetBlockType(Block_Type _type)
{
	if (block != nullptr)
		delete block;
	block = CreateBlockTable[_type]();
	bHold = true;
}

void Tetromino::SetBlockType()
{
	SetBlockType(randomBlockType());
}


CPOS Tetromino::GetX() const
{
	return x;
}

CPOS Tetromino::GetY() const
{
	return y;
}

CPOSPTR Tetromino::Getdx() const
{
	return block->Getdx();
}

CPOSPTR Tetromino::Getdy() const
{
	return block->Getdy();
}

COLOR Tetromino::GetColor() const
{
	return block->GetColor();
}


void Tetromino::Rotate(bool reverse)
{
	block->Rotate(reverse);

	if (check())
		return;

	for (int i = 1; i <= 3; ++i) {
		// check left
		if (check(x + i, y)) {
			x += i;
			return;
		}

		// check right
		if (check(x - i, y)) {
			x -= i;
			return;
		}

		// check under
		if (check(x, y - i)) {
			y -= i;
			return;
		}
	}

	block->Rotate(!reverse);
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

void Tetromino::Hold()
{
	if (!bHold)
		return;

	Block* temp = block;
	block = HoldBlock;
	HoldBlock = temp;

	if (block == nullptr)
		SetBlockType();

	SetPos();
	bHold = false;
}

bool Tetromino::check(CPOS _x, CPOS _y) const
{
	CPOSPTR dx = block->Getdx();
	CPOSPTR dy = block->Getdy();

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
	CPOSPTR dx = block->Getdx();
	CPOSPTR dy = block->Getdy();
	COLOR color = block->GetColor();

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