#include "Stage.h"
#include "Player.h"
#include <cassert>

const int WIDTH = 24;		//ステージ 幅
const int HEIGHT = 24;		//ステージ 高
const int CHIP_SIZE = 30;   //チップサイズ
int map[HEIGHT][WIDTH];

Stage::Stage()
{
	emptyImage = LoadGraph("data/image/Empty.png");
		assert(emptyImage > 0);
	blockImage = LoadGraph("data/image/Block.png");
		assert(blockImage > 0);
}

Stage::~Stage()
{
	DeleteGraph(emptyImage);
	DeleteGraph(blockImage);
}

void Stage::Draw()
{
	//マップタイル表示
	for (int j = 0; j < HEIGHT; j++)// 縦「j」
	{
		int y = j * CHIP_SIZE + (CHIP_SIZE*0);
		for (int i = 0; i < WIDTH; i++)// 幅「i」
		{
			int x = i * CHIP_SIZE + (CHIP_SIZE*0);

			// 空マス「Empty.png」を描画
			DrawGraph(x, y, emptyImage, TRUE);
		}
	}
}