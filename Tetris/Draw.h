#pragma once
#include "stdafx.h"
#include "Block.h"
#include "Tetromino.h"
#include "Board.h"

#define SCREEN_ROW_SIZE	50
#define SCREEN_COL_SIZE 50

void ScreenInit();
void ScreenFlipping();
void ScreenClear();
void ScreenRelease();

void GotoXY(POS x, POS y);
void SetColor(COLOR color);

void Draw(POS x, POS y, COLOR color, LPCSTR Format, ...);
void Draw(POS x, POS y, LPCSTR Format, ...);

void DrawBorder();
void DrawBlock();
void DrawTetromino(const Tetromino& t);