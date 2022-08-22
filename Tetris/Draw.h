#pragma once
#include "stdafx.h"
#include "Block.h"
#include "Tetromino.h"
#include "Board.h"

void GotoXY(POS x, POS y);
void SetColor(COLOR color);

void Draw(POS x, POS y, COLOR color, LPCSTR Format, ...);
void Draw(POS x, POS y, LPCSTR Format, ...);

void DrawBorder();
void DrawBlock();
void DrawTetromino(const Tetromino& t);