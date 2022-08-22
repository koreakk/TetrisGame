#pragma once

#include "stdafx.h"

#define AQUA		11
#define YELLOW		14
#define RED			12
#define GREEN		10
#define BLUE		9
#define WHITE		7
#define PURPLE		13

typedef int			POSSIZE;
typedef short		POS, * POSPTR;
typedef const POS	CPOS, * CPOSPTR;
typedef WORD		COLOR;

struct Block
{
private:
	POSSIZE size;
	POSPTR* dx;
	POSPTR* dy;
	COLOR color;
	int idx;

public:
	Block();
	Block(CPOS _dx[][4], CPOS _dy[][4], POSSIZE _size, COLOR _color);
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

using CreateBlock = Block * (*)();
extern CreateBlock CreateBlockTable[7];

typedef enum {
	I_Block = 0,
	O_Block,
	Z_Block,
	S_Block,
	J_Block,
	L_Block,
	T_Block
} Block_Type;

Block_Type randomBlockType();