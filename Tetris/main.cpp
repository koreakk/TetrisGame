#include "stdafx.h"
#include "SetText.h"
#include "Board.h"
#include "Block.h"
#include "Tetromino.h"

#define TITLE "테트리스"

Tetromino tetromino;
int score = 0;

void Init()
{
	system(" mode  con lines=26   cols=28 ");
	SetConsoleTitleA(TITLE);
}

void Run()
{
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
			case 'z':
				return;
			default:
				break;
			}
		}

		tetromino.Down();
		if (!tetromino.check())
			return;

		score += RemoveLines();

		Draw();
		printf("\nscore : %d\n", score);
		tetromino.DrawTetromino();
		Sleep(100);
	}
}



int _tmain(int argc, TCHAR* argv[])
{
	Init();

	while (true)
	{
		Run();

		system("cls");
		SetColor(WHITE);

		GotoXY(10, 10);
		printf("GAME OVER");

		GotoXY(8, 14);
		printf("play again [x]");

		GotoXY(8, 15);
		printf("exit       [z]");

		GotoXY(17, 20);
		printf("score : %d", score);

		while (true) {
			if (_kbhit())
			{
				switch (_getch())
				{
				case 'z':
					goto exit;

				case 'x':
					goto play;

				default:
					break;
				}
			}
		}
		
	play:
		score = 0;
		ClearBorad();
		tetromino.SetBlockType();
		tetromino.SetPos();
	}

exit:
	system("cls");
	SetColor(WHITE);
	return 0;
}