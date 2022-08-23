#pragma once

#include "stdafx.h"

#define AQUA		11
#define YELLOW		14
#define RED			12
#define GREEN		10
#define BLUE		9
#define WHITE		7
#define PURPLE		13

typedef short		POS, * POSPTR;
typedef const POS	CPOS, * CPOSPTR;
typedef WORD		COLOR;

struct Block
{
private:
	int m_count;
	int m_index;
	POSPTR* m_dx;
	POSPTR* m_dy;
	COLOR m_color;

public:
	Block();
	Block(CPOS dx[][4], CPOS dy[][4], int count, COLOR color);
	Block(const Block& rhs);
	Block(Block&& rhs) noexcept;
	~Block();

	Block& operator=(const Block& rhs);
	Block& operator=(Block&& rhs) noexcept;

	void Release();

	COLOR GetColor() const;
	CPOSPTR Getdx() const;
	CPOSPTR Getdy() const;
	void Rotate(bool reverse);

public:
	static Block* CreateIBlock();
	static Block* CreateOBlock();
	static Block* CreateZBlock();
	static Block* CreateSBlock();
	static Block* CreateJBlock();
	static Block* CreateLBlock();
	static Block* CreateTBlock();
};

using  CreateBlockFunc = Block * (*)();
extern CreateBlockFunc CreateBlockTable[7];

enum EBlockType{
	I_Block = 0,
	O_Block,
	Z_Block,
	S_Block,
	J_Block,
	L_Block,
	T_Block
};

EBlockType randomBlockType();