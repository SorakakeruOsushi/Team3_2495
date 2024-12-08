#include "Stage.h"
#include <cassert>
#include "Player.h"

//ステージ
#include "stageXtest.h"
//#include "stage1.h"

const int TOP_SPACE = -(CHIP_SIZE * (HEIGHT - 24)); 
const int SIDE_SPACE = CHIP_SIZE * 8; //横余白

Stage::Stage()
{
	emptyImage = LoadGraph("data/image/EmptyA1.png");
		assert(emptyImage > 0);
	blockImage = LoadGraph("data/image/Block.png");
		assert(blockImage > 0);
	goalImage = LoadGraph("data/image/Xgoal.png");
		assert(goalImage > 0);
	wallImage = LoadGraph("data/image/SideWall.png");
		assert(wallImage > 0);
	// 背景画像
	stageBGImage = LoadGraph("data/image/X/XmodeBGtetra.png");
		assert(stageBGImage > 0);
	hBGImageI = LoadGraph("data/image/Back1.JPG");
		assert(hBGImageI > 0);
	hBGImageII = LoadGraph("data/image/Back2.JPG");
		assert(hBGImageII > 0);
	hBGImageIII = LoadGraph("data/image/Back3.JPG");
		assert(hBGImageIII > 0);


	//9を探して、Playerを置く
	for (int j = 0; j < HEIGHT; j++)    //「j」縦
	{
		for (int i = 0; i < WIDTH; i++) //「i」横
		{
			if (map[j][i] == 9)//プレイヤー生成
			{
				p = Instantiate<Player>();
				p->position.x = CHIP_SIZE * i + SIDE_SPACE;
				p->position.y = CHIP_SIZE * j + TOP_SPACE;
			}
		}
	}
	scroll = 0;
	cellBG = true;
}

Stage::~Stage()
{
	DeleteGraph(emptyImage);
	DeleteGraph(blockImage);
	DeleteGraph(goalImage);
	DeleteGraph(wallImage);

	DeleteGraph(stageBGImage);
	DeleteGraph(hBGImageI);
	DeleteGraph(hBGImageII);
	DeleteGraph(hBGImageIII);
}

void Stage::Draw()
{
	//仮
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 60);
	DrawGraph(30*8, -(Screen::HEIGHT * 0), stageBGImage, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	/*
	// 背景画像表示(本当は連番pngや配列でやりたい)
	DrawGraph(0, -(Screen::HEIGHT * 0) - scroll, hBGImageI, TRUE);   //下から１番目
	DrawGraph(0, -(Screen::HEIGHT * 1) - scroll, hBGImageII, TRUE);  //下から２番目
	DrawGraph(0, -(Screen::HEIGHT * 2) - scroll, hBGImageIII, TRUE);   //下から３番目
	*/

	//壁表示(仮)
	DrawGraph(30*7, 0,  wallImage, TRUE);
	DrawGraph(30*7 + 30*25, 0,wallImage, TRUE);

	//マップタイル表示
	for (int j = 0; j < HEIGHT; j++)// 縦「j」
	{
		int y = j * CHIP_SIZE + TOP_SPACE;
		for (int i = 0; i < WIDTH; i++)// 幅「i」
		{
			int x = i * CHIP_SIZE + SIDE_SPACE;

			if (cellBG)
			{
				if (map[j][i] == 0)		// マス目「Empty.png」
				{
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 30);
					//四角を表示(左上,右下、色(R,G,B)、塗りつぶし)
					DrawGraph(x, y - scroll, emptyImage, TRUE);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //透過しない
				}
			}

			if (map[j][i] == 1)		// グレーブロック「Block.png」
			{
				DrawGraph(x, y - scroll, blockImage, TRUE);
			}
			if (map[j][i] == 8)		// ゴール「Xgoal.png」
			{
				DrawGraph(x, y - scroll, goalImage, TRUE);
			}
		}
	}
}

//ブロックの当たり判定
int Stage::IsWallRight(VECTOR2 pos)//posにはplayer座標が入る
{
	//「マップチップ→座標」の逆、「座標→マップチップ」
	int i = (pos.x - SIDE_SPACE) / CHIP_SIZE;
	int j = (pos.y - TOP_SPACE)  / CHIP_SIZE;
	if (map[j][i] == 1)
	{
		//めり込んだ分押し返す
		//★(int)少数だけどintとして扱う
		int push = ((int)pos.x - SIDE_SPACE) % CHIP_SIZE + 1;//0なら1 1なら2
		return push;
	}
	return 0;
}
int Stage::IsWallLeft(VECTOR2 pos)
{
	//「マップチップ→座標」の逆、「座標→マップチップ」
	int i = (pos.x - SIDE_SPACE) / CHIP_SIZE;
	int j = (pos.y - TOP_SPACE)  / CHIP_SIZE;
	if (map[j][i] == 1)
	{
		//めり込んだ分押し返す
		//★(int)少数だけどintとして扱う
		int push = CHIP_SIZE - ((int)pos.x - SIDE_SPACE) % CHIP_SIZE;//29なら1 28なら2
		return push;
	}
	return 0;
}
int Stage::IsWallDown(VECTOR2 pos)
{
	//「マップチップ→座標」の逆、「座標→マップチップ」
	int i = (pos.x - SIDE_SPACE) / CHIP_SIZE;
	int j = (pos.y - TOP_SPACE)  / CHIP_SIZE;
	if (map[j][i] == 1)
	{
		//めり込んだ分押し返す
		//★(int)少数だけどintとして扱う
		int push = ((int)pos.y - TOP_SPACE) % CHIP_SIZE + 1;
		return push;
	}
	return 0;
}
int Stage::IsWallUp(VECTOR2 pos)
{
	//「マップチップ→座標」の逆、「座標→マップチップ」
	int i = (pos.x - SIDE_SPACE) / CHIP_SIZE;
	int j = (pos.y - TOP_SPACE)  / CHIP_SIZE;
	if (map[j][i] == 1)
	{
		//めり込んだ分押し返す
		//★(int)少数だけどintとして扱う
		int push = CHIP_SIZE - ((int)pos.y - TOP_SPACE) % CHIP_SIZE;//29なら1 28なら2
		return push;
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