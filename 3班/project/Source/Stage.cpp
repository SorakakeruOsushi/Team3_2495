#include "Stage.h"
#include <cassert>
#include "Player.h"
#include "Block.h"


//開始時にステージをランダムでロードしたい
#include "stageXtest.h"
//#include "stage1.h"

const int TOP_SPACE = -(CHIP_SIZE * (HEIGHT - 24)); 
const int SIDE_SPACE = CHIP_SIZE * 8; //横余白

int map[HEIGHT][WIDTH];

Stage::Stage()
{
	for (int y = 0; y < HEIGHT; y++) 
	{
		for (int x = 0; x < WIDTH; x++) 
		{
			map[y][x] = orgmap[y][x];
		}
	}
	
	// 画像 ミノ画像
	MinoImage[2] = LoadGraph("data/image/Lmino_One.png");
	MinoImage[3] = LoadGraph("data/image/Jmino_One.png");
	MinoImage[4] = LoadGraph("data/image/Tmino_One.png");
	MinoImage[5] = LoadGraph("data/image/Omino_One.png");
	for (int i = 2; i < 6; i++) {
 		assert(MinoImage[i] > 0);
	}

	emptyImage = LoadGraph("data/image/EmptyA1.png");
		assert(emptyImage > 0);
	blockImage = LoadGraph("data/image/BlockA2.png");
		assert(blockImage > 0);
	goalImage = LoadGraph("data/image/GoalLineShort.png");
		assert(goalImage > 0);
	wallImage = LoadGraph("data/image/WallA1Long.png");
		assert(wallImage > 0);

	//9を探して、Playerを置く
	for (int j = 0; j < HEIGHT; j++)    //「j」縦
	{
		for (int i = 0; i < WIDTH; i++) //「i」横
		{
			if (map[j][i] == 9) //プレイヤー生成
			{
				p = Instantiate<Player>();
				p->position.x = CHIP_SIZE * i + SIDE_SPACE;
				p->position.y = CHIP_SIZE * j + TOP_SPACE;
			}
			if (map[j][i] == 7) //コイン生成
			{
				c = Instantiate<Coin>();
				c->position.x = CHIP_SIZE * i + SIDE_SPACE;
				c->position.y = CHIP_SIZE * j + TOP_SPACE;
			}
		}
	}
	scroll = 0;
	cellBG = true;

	
	b = FindGameObject<Block>();
}

Stage::~Stage()
{
	DeleteGraph(emptyImage);
	DeleteGraph(blockImage);
	DeleteGraph(goalImage);
	DeleteGraph(wallImage);
}

void Stage::Draw()
{
	//壁表示(仮)
	DrawGraph(30*7, 0,  wallImage, TRUE);
	DrawGraph(30*7 + 30*25, 0,wallImage, TRUE);

	//マップタイル表示
	for (int j = 0; j < HEIGHT; j++)	// 縦「j」
	{
		int y = j * CHIP_SIZE + TOP_SPACE;
		for (int i = 0; i < WIDTH; i++) // 幅「i」
		{
			int x = i * CHIP_SIZE + SIDE_SPACE;

			if (cellBG)
			{
				if (map[j][i] == 0)	// マス目「EmptyA1.png」
				{
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 30);
					//四角を表示(左上,右下、色(R,G,B)、塗りつぶし)
					DrawGraph(x, y - scroll, emptyImage, TRUE);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //透過しない
				}
			}

			/*
			if (map[j][i] == 1)		
			{
				DrawGraph(x, y - scroll, blockImage, TRUE);
			}
			if (map[j][i] == 8)	
			*/

			int chip = map[j][i];
			if (chip == 1)		     // グレーブロック「BlockA3.png」
			{
				DrawGraph(x, y - scroll, blockImage, TRUE);
			}
			else if (chip >= 2 && chip < 6) {
				DrawGraph(x, y - scroll, MinoImage[chip], TRUE);
			}
			else if (map[j][i] == 8) // ゴール「GoalLineShort.png」

			{
				DrawGraph(x, y - scroll, goalImage, TRUE);
			}
		}
	}
}

//########################################################
// 使うかもしれない
//if (map[j][i] == 1)
//if ( (map[j][i] == 1)|| (map[j][i] == 2) || (map[j][i] == 3) || (map[j][i] == 4) || (map[j][i] == 5) )

//ブロックの当たり判定
int Stage::IsWallRight(VECTOR2 pos)//posにはplayer座標が入る
{
	//「マップチップ→座標」の逆、「座標→マップチップ」
	int i = (pos.x - SIDE_SPACE) / CHIP_SIZE;
	int j = (pos.y - TOP_SPACE)  / CHIP_SIZE;
	for (int x = 1; x < 6; x++) {
		if (map[j][i] == x)
		{
			//めり込んだ分押し返す
			//★(int)少数だけどintとして扱う
			int push = ((int)pos.x - SIDE_SPACE) % CHIP_SIZE + 1;//0なら1 1なら2
			return push;
		}
	}
	return 0;
}
int Stage::IsWallLeft(VECTOR2 pos)
{
	//「マップチップ→座標」の逆、「座標→マップチップ」
	int i = (pos.x - SIDE_SPACE) / CHIP_SIZE;
	int j = (pos.y - TOP_SPACE)  / CHIP_SIZE;
	for (int x = 1; x < 6; x++) {
		if (map[j][i] == x)
		{
			//めり込んだ分押し返す
			//★(int)少数だけどintとして扱う
			int push = CHIP_SIZE - ((int)pos.x - SIDE_SPACE) % CHIP_SIZE;//29なら1 28なら2
			return push;
		}
	}
	return 0;
}
int Stage::IsWallDown(VECTOR2 pos)
{
	//「マップチップ→座標」の逆、「座標→マップチップ」
	int i = (pos.x - SIDE_SPACE) / CHIP_SIZE;
	int j = (pos.y - TOP_SPACE)  / CHIP_SIZE;
	for (int x = 1; x < 6; x++) {
		if (map[j][i] == x)
		{
			//めり込んだ分押し返す
			//★(int)少数だけどintとして扱う
			int push = ((int)pos.y - TOP_SPACE) % CHIP_SIZE + 1;
			return push;
		}
	}
	return 0;
}
int Stage::IsWallUp(VECTOR2 pos)
{
	//「マップチップ→座標」の逆、「座標→マップチップ」
	int i = (pos.x - SIDE_SPACE) / CHIP_SIZE;
	int j = (pos.y - TOP_SPACE)  / CHIP_SIZE;
	for (int x = 1; x < 6; x++) {
		if (map[j][i] == x)
		{
			//めり込んだ分押し返す
			//★(int)少数だけどintとして扱う
			int push = CHIP_SIZE - ((int)pos.y - TOP_SPACE) % CHIP_SIZE;//29なら1 28なら2
			return push;
		}
	}
	return 0;
}

bool Stage::IsGoal(VECTOR2 pos)
{
	//「マップチップ→座標」の逆、「座標→マップチップ」
	int i = (pos.x - SIDE_SPACE) / CHIP_SIZE;
	int j = (pos.y - TOP_SPACE)  / CHIP_SIZE;
	if (map[j][i] == 8)
	{
		return true;
	}
	return false;
}