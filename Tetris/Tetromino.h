#pragma once
#include "stdafx.h"
#include "Block.h"
#include "Board.h"

struct Tetromino
{
private:
	POS m_x;
	POS m_y;

	Block* m_pBlock;
	Block* m_pHoldBlock;

	bool m_bHold;
public:
	Tetromino();
	explicit Tetromino(EBlockType type);
	Tetromino(EBlockType type, POS x, POS y);
	~Tetromino();

	void SetPos(CPOS x = 4, CPOS y = 0);
	void SetBlockType(EBlockType type);
	void SetBlockType();

	CPOS GetX() const;
	CPOS GetY() const;
	CPOSPTR Getdx() const;
	CPOSPTR Getdy() const;
	COLOR GetColor() const;

	void Rotate(bool reverse = false);
	void Down();
	void Drop();
	void Left();
	void Right();
	void Hold();

	bool check() const;
	bool check(CPOS x, CPOS y) const;

private:
	void SaveBlock();
};
