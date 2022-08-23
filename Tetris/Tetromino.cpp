#include "stdafx.h"
#include "Tetromino.h"

Tetromino::Tetromino()
	: m_x(4), m_y(0), m_bHold(true),
	m_pBlock(nullptr),
	m_pHoldBlock(nullptr)
{
	EBlockType type = randomBlockType();
	m_pBlock = CreateBlockTable[type]();
}

Tetromino::Tetromino(EBlockType type)
	: m_x(4), m_y(0), m_bHold(true),
	m_pBlock(CreateBlockTable[type]()),
	m_pHoldBlock(nullptr)
{
}

Tetromino::Tetromino(EBlockType type, POS x, POS y)
	: m_x(x), m_y(y), m_bHold(true),
	m_pBlock(CreateBlockTable[type]()),
	m_pHoldBlock(nullptr)
{
}

Tetromino::~Tetromino()
{
	if (m_pBlock != nullptr)
		delete m_pBlock;
	if (m_pHoldBlock != nullptr)
		delete m_pHoldBlock;

	m_pBlock = nullptr;
	m_pHoldBlock = nullptr;
}

void Tetromino::SetPos(CPOS x, CPOS y)
{
	m_x = x;
	m_y = y;
}

void Tetromino::SetBlockType(EBlockType type)
{
	if (m_pBlock != nullptr)
		delete m_pBlock;
	m_pBlock = CreateBlockTable[type]();
	m_bHold = true;
}

void Tetromino::SetBlockType()
{
	SetBlockType(randomBlockType());
}


CPOS Tetromino::GetX() const
{
	return m_x;
}

CPOS Tetromino::GetY() const
{
	return m_y;
}

CPOSPTR Tetromino::Getdx() const
{
	return m_pBlock->Getdx();
}

CPOSPTR Tetromino::Getdy() const
{
	return m_pBlock->Getdy();
}

COLOR Tetromino::GetColor() const
{
	return m_pBlock->GetColor();
}


void Tetromino::Rotate(bool reverse)
{
	m_pBlock->Rotate(reverse);

	if (check())
		return;

	for (int i = 1; i <= 3; ++i) {
		// check left
		if (check(m_x + i, m_y)) {
			m_x += i;
			return;
		}

		// check right
		if (check(m_x - i, m_y)) {
			m_x -= i;
			return;
		}

		// check under
		if (check(m_x, m_y - i)) {
			m_y -= i;
			return;
		}
	}

	m_pBlock->Rotate(!reverse);
}

void Tetromino::Down()
{
	if (check(m_x, m_y + 1)) m_y++;

	else {
		SaveBlock();
		SetPos();
		SetBlockType();
	}
}

void Tetromino::Drop()
{
	while (check(m_x, m_y + 1)) m_y++;

	SaveBlock();
	SetPos();
	SetBlockType();
}

void Tetromino::Left()
{
	if (check(m_x - 1, m_y))
		m_x--;
}

void Tetromino::Right()
{
	if (check(m_x + 1, m_y))
		m_x++;
}

void Tetromino::Hold()
{
	if (!m_bHold)
		return;

	Block* temp = m_pBlock;
	m_pBlock = m_pHoldBlock;
	m_pHoldBlock = temp;

	if (m_pBlock == nullptr)
		SetBlockType();

	SetPos();
	m_bHold = false;
}

bool Tetromino::check(CPOS x, CPOS y) const
{
	CPOSPTR dx = m_pBlock->Getdx();
	CPOSPTR dy = m_pBlock->Getdy();

	POS _x = 0;
	POS _y = 0;

	for (int i = 0; i < 4; ++i) {
		_x = x + dx[i];
		_y = y + dy[i];

		if (!BoardSizeCheck(_x, _y))
			return false;

		if (board[_y][_x] != 0)
			return false;
	}
	
	return true;
}

bool Tetromino::check() const
{
	return check(m_x, m_y);
}

void Tetromino::SaveBlock()
{
	CPOSPTR dx = m_pBlock->Getdx();
	CPOSPTR dy = m_pBlock->Getdy();
	COLOR color = m_pBlock->GetColor();

	POS x = 0;
	POS y = 0;

	for (int i = 0; i < 4; ++i) {
		x = m_x + dx[i];
		y = m_y + dy[i];

		if (!BoardSizeCheck(x, y))
			continue;

		board[y][x] = color;
	}
}