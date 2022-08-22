#pragma once
#include "stdafx.h"
#include "SetText.h"
#include "Tetromino.h"


#define BOARD_ROW_SIZE	20
#define BOARD_COL_SIZE	10

#define BORDER	"бр"
#define SPACE	"  "
#define BLOCK	"бс"

extern unsigned short board[BOARD_ROW_SIZE][BOARD_COL_SIZE];

bool BoardSizeCheck(POS x, POS y);
int RemoveLines();
void ClearBorad();

void Draw();