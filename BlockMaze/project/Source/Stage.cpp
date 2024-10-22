#include "Stage.h"
#include "Player.h"


const int WIDTH = 10;
const int HEIGHT = 10;

const int CHIP_SIZE = 40;
int map[HEIGHT][WIDTH] = {
   //1, 2, 3, 4, 5, 6, 7, 8, 9, 10
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},//1
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},//2
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},//3
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},//4
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},//5
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},//6
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},//7
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},//8
	{0, 0, 0, 0, 9, 2, 0, 0, 0, 0},//9
	{0, 0, 0, 0, 1, 1, 0, 0, 0, 0},//10
};

Stage::Stage()
{
	hImage = LoadGraph("data/image/parts.png");
	for (int j = 0; j < HEIGHT; j++)//縦「j」
	{
		for (int i = 0; i < WIDTH; i++)//横「i」
		{
			if (map[j][i] == 9) {
				Player* p = Instantiate<Player>();
				p->position.x = i * CHIP_SIZE + 100;
				p->position.y = j * CHIP_SIZE + 100;
			}
		}
	}
}

Stage::~Stage()
{
	DeleteGraph(hImage);
}

void Stage::Draw()
{
	for (int j = 0; j < HEIGHT; j++)//縦「j」
	{
		int y = j * CHIP_SIZE + 100;
		for (int i = 0; i < WIDTH; i++)//横「i」
		{
			int x = i * CHIP_SIZE + 100;
			if (map[j][i] == 1) {	//赤レンガ
				DrawRectGraph(x, y, CHIP_SIZE * 0, CHIP_SIZE * 1, CHIP_SIZE, CHIP_SIZE, hImage, TRUE);
			}
			if (map[j][i] == 2) {	//コイン
				DrawRectGraph(x, y, CHIP_SIZE * 3, CHIP_SIZE * 0, CHIP_SIZE, CHIP_SIZE, hImage, TRUE);
			}
		}
	}
}

//右は壁があるか
int Stage::IsWallRight(VECTOR2 pos)
{
	int i = (pos.x - 100) / CHIP_SIZE;
	int j = (pos.y - 100) / CHIP_SIZE;
	if (map[j][i]==1)
	{
		int push = ((int)pos.x - 100) % CHIP_SIZE + 1;
		return push;
	}
	return 0;
}
//下は壁があるか
int Stage::IsWallDown(VECTOR2 pos)
{
	int i = (pos.x - 100) / CHIP_SIZE;
	int j = (pos.y - 100) / CHIP_SIZE;
	if (map[j][i] == 1)
	{
		int push = ((int)pos.y - 100) % CHIP_SIZE + 1;
		return push;
	}
	return 0;
}
//左は壁があるか
int Stage::IsWallLeft(VECTOR2 pos)
{
	int i = (pos.x - 100) / CHIP_SIZE;
	int j = (pos.y - 100) / CHIP_SIZE;
	if (map[j][i] == 1)
	{
		int push = 40 -((int)pos.x - 100) % CHIP_SIZE;
		return push;
	}
	return 0;
}
//上は壁があるか
int Stage::IsWallUp(VECTOR2 pos)
{
	int i = (pos.x - 100) / CHIP_SIZE;
	int j = (pos.y - 100) / CHIP_SIZE;
	if (map[j][i] == 1)
	{
		int push = 40-((int)pos.y - 100) % CHIP_SIZE;
		return push;
	}
	return 0;
}
	
