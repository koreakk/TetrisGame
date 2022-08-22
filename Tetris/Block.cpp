#include "stdafx.h"
#include "Block.h"


Block::Block()
	: dx(nullptr), dy(nullptr), size(0), color(0), idx(0)
{
}

Block::Block(CPOS _dx[][4], CPOS _dy[][4], POSSIZE _size, COLOR _color)
	: dx(nullptr), dy(nullptr), size(_size), color(_color), idx(0)
{
	dx = new POSPTR[size];
	dy = new POSPTR[size];

	for (int i = 0; i < size; i++) {
		dx[i] = new short[4];
		memcpy(dx[i], _dx[i], sizeof(short) * 4);

		dy[i] = new short[4];
		memcpy(dy[i], _dy[i], sizeof(short) * 4);
	}
}

Block::Block(const Block& rhs)
	:dx(nullptr), dy(nullptr), size(0), color(0), idx(0)
{
	dx = new POSPTR[size];
	dy = new POSPTR[size];

	for (int i = 0; i < size; i++) {
		dx[i] = new short[4];
		memcpy(dx[i], rhs.dx[i], sizeof(short) * 4);

		dy[i] = new short[4];
		memcpy(dy[i], rhs.dy[i], sizeof(short) * 4);
	}
}

Block::Block(Block&& rhs) noexcept
	:dx(nullptr), dy(nullptr), size(0), color(0), idx(0)
{
	size = rhs.size;
	color = rhs.color;
	idx = rhs.idx;

	dx = rhs.dx;
	dy = rhs.dy;

	rhs.dx = nullptr;
	rhs.dy = nullptr;
}

Block& Block::operator=(const Block& rhs)
{
	Release();

	size = rhs.size;
	color = rhs.color;
	idx = rhs.idx;

	dx = new POSPTR[size];
	dy = new POSPTR[size];

	for (int i = 0; i < size; i++) {
		dx[i] = new short[4];
		memcpy(dx[i], rhs.dx[i], sizeof(short) * 4);

		dy[i] = new short[4];
		memcpy(dy[i], rhs.dy[i], sizeof(short) * 4);
	}

	return *this;
}

Block& Block::operator=(Block&& rhs) noexcept
{
	Release();

	size = rhs.size;
	color = rhs.color;
	idx = rhs.idx;

	dx = rhs.dx;
	dy = rhs.dy;

	rhs.dx = nullptr;
	rhs.dy = nullptr;

	return *this;
}

Block::	~Block()
{
	Release();
}

void Block::Release()
{
	if (dx != nullptr)
		delete[] dx;
	if (dy != nullptr)
		delete[] dy;
	
	dx = nullptr;
	dy = nullptr;
}

COLOR Block::GetColor() const 
{ 
	return color;
}

CPOSPTR Block::Getdx() const
{ 
	if (dx == nullptr)
		return nullptr;

	return dx[idx];
}


CPOSPTR Block::Getdy() const
{
	if (dy == nullptr)
		return nullptr;

	return dy[idx];
}

void Block::Rotate(bool reverse)
{
	idx += (reverse) ? -1 : 1;
	idx %= size;
}

Block* Block::CreateIBlock()
{
	POSSIZE size = 2;
	CPOS _dx[][4] = { {0,0,0,0}, {0,1,2,3} };
	CPOS _dy[][4] = { {0,1,2,3}, {0,0,0,0} };
	COLOR _color = AQUA;

	return new Block(_dx, _dy, size, _color);
}

Block* Block::CreateOBlock()
{
	POSSIZE size = 1;
	CPOS _dx[][4] = { {0,1,0,1} };
	CPOS _dy[][4] = { {0,0,1,1} };
	COLOR _color = YELLOW;

	return new Block(_dx, _dy, size, _color);
}

Block* Block::CreateZBlock()
{
	POSSIZE size = 2;
	CPOS _dx[][4] = { {0,1,1,2}, {1,0,1,0} };
	CPOS _dy[][4] = { {0,0,1,1}, {0,1,1,2} };
	COLOR _color = RED;

	return new Block(_dx, _dy, size, _color);
}

Block* Block::CreateSBlock()
{
	POSSIZE size = 2;
	CPOS _dx[][4] = { {1,2,0,1}, {0,0,1,1} };
	CPOS _dy[][4] = { {0,0,1,1}, {0,1,1,2} };
	COLOR _color = GREEN;

	return new Block(_dx, _dy, size, _color);
}

Block* Block::CreateJBlock()
{
	POSSIZE size = 4;
	CPOS _dx[][4] = { {1,1,0,1}, {0,0,1,2}, {0,1,0,0}, {0,1,2,2} };
	CPOS _dy[][4] = { {0,1,2,2}, {0,1,1,1}, {0,0,1,2}, {0,0,0,1} };
	COLOR _color = BLUE;

	return new Block(_dx, _dy, size, _color);
}

Block* Block::CreateLBlock()
{
	POSSIZE size = 4;
	CPOS _dx[][4] = { {0,0,0,1}, {0,1,2,0}, {0,1,1,1}, {2,0,1,2} };
	CPOS _dy[][4] = { {0,1,2,2}, {0,0,0,1}, {0,0,1,2}, {0,1,1,1} };
	COLOR _color = WHITE;

	return new Block(_dx, _dy, size, _color);
}

Block* Block::CreateTBlock()
{
	POSSIZE size = 4;
	CPOS _dx[][4] = { {0,1,2,1}, {1,0,1,1}, {1,0,1,2}, {0,0,1,0} };
	CPOS _dy[][4] = { {0,0,0,1}, {0,1,1,2}, {0,1,1,1}, {0,1,1,2} };
	COLOR _color = PURPLE;

	return new Block(_dx, _dy, size, _color);
}

extern CreateBlock CreateBlockTable[7] = {
	Block::CreateIBlock,
	Block::CreateOBlock,
	Block::CreateZBlock,
	Block::CreateSBlock,
	Block::CreateJBlock,
	Block::CreateLBlock,
	Block::CreateTBlock
};

Block_Type randomBlockType() {
	return (Block_Type)(rand() % 7);
}