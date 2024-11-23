#include "Stage.h"
#include "Player.h"
#include <cassert>


const int CHIP_SIZE = 30;   //チップサイズ
//ステージ
#include "stage1.h"


Stage::Stage()
{
	emptyImage = LoadGraph("data/image/EmptyA1.png");
		assert(emptyImage > 0);
	blockImage = LoadGraph("data/image/Block.png");
		assert(blockImage > 0);

	//9を探して、Playerを置く
	for (int j = 0; j < HEIGHT; j++)    //「j」縦
	{
		for (int i = 0; i < WIDTH; i++) //「i」横
		{
			if (map[j][i] == 9)//プレイヤー生成
			{
				Player* p = Instantiate<Player>();
				p->position.x = CHIP_SIZE * i + CHIP_SIZE * 0;
				p->position.y = CHIP_SIZE * j + CHIP_SIZE * 0;
			}
		}
	}
	scroll = 0;
}

Stage::~Stage()
{
	DeleteGraph(emptyImage);
	DeleteGraph(blockImage);
}

void Stage::Draw()
{
	//マップセル(マス目)固定表示
	//DrawGraph(CHIP_SIZE * 0, CHIP_SIZE * 0, cellBGImage, TRUE);

	//マップタイル表示
	for (int j = 0; j < HEIGHT; j++)// 縦「j」
	{
		int y = j * CHIP_SIZE + (CHIP_SIZE * 0);
		for (int i = 0; i < WIDTH; i++)// 幅「i」
		{
			int x = i * CHIP_SIZE + (CHIP_SIZE * 0);

			if (map[j][i] == 0)		// 基礎タイル「Empty.png」
			{
				DrawGraph(x, y - scroll, emptyImage, TRUE);
			}

			if (map[j][i] == 1)		// 基礎タイル「Block.png」
			{
				DrawGraph(x, y - scroll, blockImage, TRUE);
			}
		}
	}
}

//ブロックの当たり判定
int Stage::IsWallRight(VECTOR2 pos)//posにはplayer座標が入る
{
	//「マップチップ→座標」の逆、「座標→マップチップ」
	int i = (pos.x - CHIP_SIZE * 0) / 30;
	int j = (pos.y - CHIP_SIZE * 0) / 30;
	if (map[j][i] == 1)
	{
		//めり込んだ分押し返す
		//★(int)少数だけどintとして扱う
		int push = ((int)pos.x - CHIP_SIZE * 0) % 30 + 1;//0なら1 1なら2
		return push;
	}
	return 0;
}
int Stage::IsWallLeft(VECTOR2 pos)
{
	//「マップチップ→座標」の逆、「座標→マップチップ」
	int i = (pos.x - CHIP_SIZE * 0) / 30;
	int j = (pos.y - CHIP_SIZE * 0) / 30;
	if (map[j][i] == 1)
	{
		//めり込んだ分押し返す
		//★(int)少数だけどintとして扱う
		int push = 30 - ((int)pos.x - CHIP_SIZE * 0) % 30;//29なら1 28なら2
		return push;
	}
	return 0;
}
int Stage::IsWallDown(VECTOR2 pos)
{
	//「マップチップ→座標」の逆、「座標→マップチップ」
	int i = (pos.x - CHIP_SIZE * 0) / 30;
	int j = (pos.y - CHIP_SIZE * 0) / 30;
	if (map[j][i] == 1)
	{
		//めり込んだ分押し返す
		//★(int)少数だけどintとして扱う
		int push = ((int)pos.y - CHIP_SIZE * 0) % 30 + 1;
		return push;
	}
	return 0;
}
int Stage::IsWallUp(VECTOR2 pos)
{
	//「マップチップ→座標」の逆、「座標→マップチップ」
	int i = (pos.x - CHIP_SIZE * 0) / 30;
	int j = (pos.y - CHIP_SIZE * 0) / 30;
	if (map[j][i] == 1)
	{
		//めり込んだ分押し返す
		//★(int)少数だけどintとして扱う
		int push = 30 - ((int)pos.y - CHIP_SIZE * 0) % 30;//29なら1 28なら2
		return push;
	}
	return 0;
}
