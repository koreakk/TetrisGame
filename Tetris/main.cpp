#include "stdafx.h"
#include "Board.h"
#include "Block.h"
#include "Tetromino.h"

void DrawBorder()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	printf(BORDER);
}

void DrawBlock(unsigned short c)
{
	if (c == 0)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		printf(SPACE);
	}
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
		printf(BLOCK);
	}
}

void Draw()
{
	for (int i = 0; i < BOARD_ROW_SIZE + 1; i++) {
		for (int j = 0; j < BOARD_COL_SIZE + 2; j++)
		{
			if (!BoardSizeCheck(j - 1, i)) {
				DrawBorder();
				continue;
			}

			DrawBlock(board[i][j - 1]);
		}
		putchar('\n');
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
}

int _tmain(int argc, TCHAR* argv[])
{
	Tetromino A(I_Block);
	A.SetBlockType(L_Block);
	while (1)
	{
		system("cls");

		if (_kbhit())
		{
			switch (_getch())
			{
			case 'w':
				A.Rotate();
				break;
			case 'a':
				A.Left();
				break;
			case 's':
				A.Down();
				break;
			case 'd':
				A.Right();
				break;
			case 'q':
				A.SetBlockType(randomBlockType());
				break;
			case 'z':
				goto exitloop;
			default:
				break;
			}
		}
		//A.Down();
		Draw();
		A.DrawTetromino();
		Sleep(100);
	}

exitloop:
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	return 0;
}