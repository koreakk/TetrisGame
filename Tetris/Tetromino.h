#pragma once
#include "stdafx.h"
#include "Block.h"
#include "Board.h"
#include "SetText.h"
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

	void SetBlockType(Block_Type _type);
	void SetBlockType();
	void Rotate(bool reverse = false);
	
	void Down();
	void Drop();
	void Left();
	void Right();

	void HoldBlockSwap();

	void SetPos(POS _x = 4, POS _y = 0);

	void DrawTetromino() const;
	bool  check() const;
	bool  check(CPOS _x, CPOS _y) const;

private:
	void DrawBlock(POS _x, POS _y, LPCSTR _ch, COLOR _Color) const;
	void SaveBlock();
};
