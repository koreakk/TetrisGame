#pragma once
#include "stdafx.h"
#include "Block.h"

#define BOARD_ROW_SIZE	20
#define BOARD_COL_SIZE	10

#define BORDER	"бр"
#define BLOCK	"бс"

extern unsigned short board[BOARD_ROW_SIZE][BOARD_COL_SIZE];

bool BoardSizeCheck(POS x, POS y);
int BoardUpdate();
void BoardClear();

