#include "stdafx.h"
#include "Block.h"
#include "Board.h"
#include "Tetromino.h"
#include "Draw.h"

#define TITLE "테트리스"

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
				brunning = !Pause();
				break;
			default:
				break;
			}
		}
		if (n++ % 3 == 0)
			tetromino.Down();
		
		if (!tetromino.check())
			brunning = !GameOver();

		score += BoardUpdate();

		DrawBorder();
		DrawBlock();
		DrawTetromino(tetromino);
		Draw(0, BOARD_ROW_SIZE + 2, WHITE, "score : %d", score);

		Sleep(100);
		ScreenFlipping();
	}
}

int main()
{
	SetConsoleTitleA(TITLE);
	ScreenInit();
	//system("mode con:cols=26 lines=28");
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