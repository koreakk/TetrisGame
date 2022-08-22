#pragma once
#include "stdafx.h"
#include "Block.h"
#include "Board.h"

struct Tetromino
{

	POS x;
	POS y;
	bool bMove;
	Block_Type type;
	Block block;
public:
	explicit Tetromino(Block_Type _type);
	Tetromino(Block_Type _type, POS _x, POS _y);
	~Tetromino();

	void SetBlockType(Block_Type _type);
	void Rotate(bool revers = false);
	
	void Down();
	void Left();
	void Right();

	void DrawTetromino() const;
private:
	void DrawBlock(POS _x, POS _y, LPCSTR _ch, COLOR _Color) const;
	bool  check(CPOS _x, CPOS _y) const;

	void SaveBlock();
	void SetPos(POS _x = 0, POS _y = 0);
};
