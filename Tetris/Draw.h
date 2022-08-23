#pragma once
#include "stdafx.h"
#include "Block.h"
#include "Tetromino.h"
#include "Board.h"

#define TITLE "테트리스"

#define SCREEN_ROW_SIZE	28
#define SCREEN_COL_SIZE 27

void ScreenInit();
void ScreenFlipping();
void ScreenClear();
void ScreenRelease();
void SetScreenSize(unsigned int width, unsigned int height);

void GotoXY(POS x, POS y);
void SetColor(COLOR color);

void Draw(POS x, POS y, COLOR color, LPCSTR Format, ...);
void Draw(POS x, POS y, LPCSTR Format, ...);

void DrawBorder();
void DrawBlock();
void DrawTetromino(const Tetromino& t);