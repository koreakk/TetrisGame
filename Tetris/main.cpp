#include "stdafx.h"
#include "Block.h"
#include "Board.h"
#include "Tetromino.h"
#include "Draw.h"

#define UP		72
#define LEFT	75
#define RIGHT	77
#define DOWN	80
#define SPACE	32

Tetromino tetromino;
int score = 0;

void Init();
bool GameOver();
bool Pause();

void Run()
{
	bool brunning = true;

	int n = 0;
	while (brunning)
	{
		ScreenClear();

		if (_kbhit())
		{
			switch (_getch())
			{
			case UP:
				tetromino.Rotate();
				break;
			case LEFT:
				tetromino.Left();
				break;
			case RIGHT:
				tetromino.Right();
				break;
			case DOWN:
				tetromino.Down();
				break;
			case SPACE:
				tetromino.Drop();
				break;
			case 'c':
				tetromino.Hold();
				break;
			case 'z':
				brunning = !Pause();
				break;
			default:
				break;
			}
		}
		if (n++ == 250)
			tetromino.Down(), n = 0;
		
		if (!tetromino.check())
			brunning = !GameOver();

		score += BoardUpdate();

		DrawBorder();
		DrawBlock();
		DrawTetromino(tetromino);
		Draw(0, BOARD_ROW_SIZE + 2, WHITE, "score : %d", score);

		ScreenFlipping();
	}
}

int main()
{
	ScreenInit();
	Run();

	ScreenRelease();
	return 0;
}

bool GameOver()
{
	bool bEnd = false;
	ScreenClear();

	SetColor(WHITE);

	Draw(10, 10, "GAME OVER");
	Draw(8, 14, "play again [x]");
	Draw(8, 15, "exit       [z]");
	Draw(17, 20, "score : %d", score);
	ScreenFlipping();

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
	BoardClear();
	tetromino.SetBlockType();
	tetromino.SetPos();

	ScreenClear();
	return bEnd;
}
bool Pause()
{
	bool bEnd = false;
	
	ScreenClear();

	SetColor(WHITE);

	Draw(10, 10, "Pause");
	Draw(8, 14, "play again [x]");
	Draw(8, 15, "exit       [z]");
	Draw(17, 20, "score : %d", score);
	ScreenFlipping();

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
	ScreenClear();
	return bEnd;
}