#include "stdafx.h"
#include "Block.h"


Block::Block()
	: m_dx(nullptr), m_dy(nullptr), m_count(0), m_index(0), m_color(0)
{
}

Block::Block(CPOS dx[][4], CPOS dy[][4], int count, COLOR color)
	: m_dx(nullptr), m_dy(nullptr), m_count(count), m_index(0), m_color(color)
{
	m_dx = new POSPTR[m_count];
	m_dy = new POSPTR[m_count];

	for (int i = 0; i < m_count; i++) {
		m_dx[i] = new short[4];
		memcpy(m_dx[i], dx[i], sizeof(short) * 4);

		m_dy[i] = new short[4];
		memcpy(m_dy[i], dy[i], sizeof(short) * 4);
	}
}

Block::Block(const Block& rhs)
	:m_dx(nullptr), m_dy(nullptr), m_count(0), m_index(0), m_color(0)
{
	m_dx = new POSPTR[m_count];
	m_dy = new POSPTR[m_count];

	for (int i = 0; i < m_count; i++) {
		m_dx[i] = new short[4];
		memcpy(m_dx[i], rhs.m_dx[i], sizeof(short) * 4);

		m_dy[i] = new short[4];
		memcpy(m_dy[i], rhs.m_dy[i], sizeof(short) * 4);
	}
}

Block::Block(Block&& rhs) noexcept
	:m_dx(nullptr), m_dy(nullptr), m_count(0), m_index(0), m_color(0)
{
	m_count = rhs.m_count;
	m_color = rhs.m_color;
	m_index = rhs.m_index;

	m_dx = rhs.m_dx;
	m_dy = rhs.m_dy;

	rhs.m_dx = nullptr;
	rhs.m_dy = nullptr;
}

Block& Block::operator=(const Block& rhs)
{
	Release();

	m_count = rhs.m_count;
	m_color = rhs.m_color;
	m_index = rhs.m_index;

	m_dx = new POSPTR[m_count];
	m_dy = new POSPTR[m_count];

	for (int i = 0; i < m_count; i++) {
		m_dx[i] = new short[4];
		memcpy(m_dx[i], rhs.m_dx[i], sizeof(short) * 4);

		m_dy[i] = new short[4];
		memcpy(m_dy[i], rhs.m_dy[i], sizeof(short) * 4);
	}

	return *this;
}

Block& Block::operator=(Block&& rhs) noexcept
{
	Release();

	m_count = rhs.m_count;
	m_color = rhs.m_color;
	m_index = rhs.m_index;

	m_dx = rhs.m_dx;
	m_dy = rhs.m_dy;

	rhs.m_dx = nullptr;
	rhs.m_dy = nullptr;

	return *this;
}

Block::	~Block()
{
	Release();
}

void Block::Release()
{
	if (m_dx != nullptr)
		delete[] m_dx;
	if (m_dy != nullptr)
		delete[] m_dy;
	
	m_dx = nullptr;
	m_dy = nullptr;
}

COLOR Block::GetColor() const 
{ 
	return m_color;
}

CPOSPTR Block::Getdx() const
{ 
	if (m_dx == nullptr)
		return nullptr;

	return m_dx[m_index];
}


CPOSPTR Block::Getdy() const
{
	if (m_dy == nullptr)
		return nullptr;

	return m_dy[m_index];
}

void Block::Rotate(bool reverse)
{
	m_index += (reverse) ? -1 : 1;
	m_index %= m_count;
}

Block* Block::CreateIBlock()
{
	int count = 2;
	CPOS dx[][4] = { {0,0,0,0}, {0,1,2,3} };
	CPOS dy[][4] = { {0,1,2,3}, {0,0,0,0} };
	COLOR color = AQUA;

	return new Block(dx, dy, count, color);
}

Block* Block::CreateOBlock()
{
	int count = 1;
	CPOS dx[][4] = { {0,1,0,1} };
	CPOS dy[][4] = { {0,0,1,1} };
	COLOR color = YELLOW;

	return new Block(dx, dy, count, color);
}

Block* Block::CreateZBlock()
{
	int count = 2;
	CPOS dx[][4] = { {0,1,1,2}, {1,0,1,0} };
	CPOS dy[][4] = { {0,0,1,1}, {0,1,1,2} };
	COLOR color = RED;

	return new Block(dx, dy, count, color);
}

Block* Block::CreateSBlock()
{
	int count = 2;
	CPOS dx[][4] = { {1,2,0,1}, {0,0,1,1} };
	CPOS dy[][4] = { {0,0,1,1}, {0,1,1,2} };
	COLOR color = GREEN;

	return new Block(dx, dy, count,color);
}

Block* Block::CreateJBlock()
{
	int count = 4;
	CPOS dx[][4] = { {1,1,0,1}, {0,0,1,2}, {0,1,0,0}, {0,1,2,2} };
	CPOS dy[][4] = { {0,1,2,2}, {0,1,1,1}, {0,0,1,2}, {0,0,0,1} };
	COLOR color = BLUE;

	return new Block(dx, dy, count, color);
}

Block* Block::CreateLBlock()
{
	int count = 4;
	CPOS dx[][4] = { {0,0,0,1}, {0,1,2,0}, {0,1,1,1}, {2,0,1,2} };
	CPOS dy[][4] = { {0,1,2,2}, {0,0,0,1}, {0,0,1,2}, {0,1,1,1} };
	COLOR color = WHITE;

	return new Block(dx, dy, count, color);
}

Block* Block::CreateTBlock()
{
	int count = 4;
	CPOS dx[][4] = { {0,1,2,1}, {1,0,1,1}, {1,0,1,2}, {0,0,1,0} };
	CPOS dy[][4] = { {0,0,0,1}, {0,1,1,2}, {0,1,1,1}, {0,1,1,2} };
	COLOR color = PURPLE;

	return new Block(dx, dy, count, color);
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