#pragma once
#include "stdafx.h"
#include "Block.h"
#include "Board.h"

struct Tetromino
{
private:
	POS x;
	POS y;

	Block* block;
	Block* HoldBlock;

	bool bHold;
public:
	Tetromino();
	explicit Tetromino(Block_Type _type);
	Tetromino(Block_Type _type, POS _x, POS _y);
	~Tetromino();

	void SetPos(CPOS _x = 4, CPOS _y = 0);
	void SetBlockType(Block_Type _type);
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
	bool check(CPOS _x, CPOS _y) const;

private:
	void SaveBlock();
};
