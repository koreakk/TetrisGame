#include "stdafx.h"
#include "Block.h"
#include "Tetromino.h"
#include "Board.h"
#include "Draw.h"

#define TITLE "테트리스"

Tetromino tetromino;
int score = 0;


void Init();
bool GameOver();
bool Pause();

void Run()
{
	int n = 0;
	while (1)
	{
		system("cls");

		if (_kbhit())
		{
			switch (_getch())
			{
			case 'w':
				tetromino.Rotate();
				break;
			case 'a':
				tetromino.Left();
				break;
			case 'd':
				tetromino.Right();
				break;
			case 's':
				tetromino.Down();
				break;
			case ' ':
				tetromino.Drop();
				break;
			case 'c':
				tetromino.Hold();
				break;
			case 'z':
				if (Pause())
					return;
				break;
			default:
				break;
			}
		}
		if (n++ % 5 == 0)
			tetromino.Down();
		
		if (!tetromino.check())
		{
			if (GameOver())
				return;
		}

		score += RemoveLines();

		DrawBorder();
		DrawBlock();
		DrawTetromino(tetromino);

		Draw(0, BOARD_ROW_SIZE + 2, WHITE, "score : %d", score);
		Sleep(100);
	}
}



int main()
{
	Init();
	Run();

	system("cls");
	SetColor(WHITE);

	return 0;
}

bool GameOver()
{
	bool bEnd = false;

	system("cls");
	SetColor(WHITE);

	Draw(10, 10, "GAME OVER");
	Draw(8, 14, "play again [x]");
	Draw(8, 15, "exit       [z]");
	Draw(17, 20, "score : %d", score);

	while (true) {
		if (_kbhit())
		{
			switch (_getch())
			{
			case 'z':
				bEnd = true;
				goto exitloop;

			case 'x':
				goto exitloop;

			default:
				break;
			}
		}
	}

exitloop:
	score = 0;
	ClearBorad();
	tetromino.SetBlockType();
	tetromino.SetPos();

	system("cls");
	SetColor(WHITE);
	return bEnd;
}
bool Pause()
{
	bool bEnd = false;

	system("cls");
	SetColor(WHITE);

	Draw(10, 10, "Pause");
	Draw(8, 14, "play again [x]");
	Draw(8, 15, "exit       [z]");
	Draw(17, 20, "score : %d", score);

	while (true) {
		if (_kbhit())
		{
			switch (_getch())
			{
			case 'z':
				bEnd = true;
				goto exitloop;

			case 'x':
				goto exitloop;

			default:
				break;
			}
		}
	}

exitloop:
	system("cls");
	SetColor(WHITE);
	return bEnd;
}
void Init()
{
	system(" mode  con lines=26   cols=28 ");
	SetConsoleTitleA(TITLE);
}