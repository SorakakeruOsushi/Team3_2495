#include "Stage.h"
#include <cassert>
#include <sstream>
#include <fstream>
#include "Player.h"
#include "Block.h"
#include "csvReader.h"

const int WIDTH = 24;		//ステージ 幅
const int HEIGHT = 51;		//ステージ 高

int map[HEIGHT][WIDTH];

const int TOP_SPACE = -(CHIP_SIZE * (HEIGHT - 24));
const int SIDE_SPACE = CHIP_SIZE * 8;	//横余白
const char* STAGE_DATA_PATH = "data/Stage/Stage%02d.csv";	// ブロック配置情報のファイル名

Stage::Stage()
{
	//ランダムなCSVファイルを読み込んでステージ生成する！(堀越先生ありがとう！)
	int stageNo = 0;
	stageNo = GetRand(8) + 1; // 乱数 [01～05]のランダム

	char stageFile[100];
	sprintf_s(stageFile, STAGE_DATA_PATH, stageNo);


	CsvReader* csv = new CsvReader(stageFile);			    //Stage(01～05).CSVをランダム表示
	//CsvReader* csv = new CsvReader("data/stage/Test.csv"); //決まったCSVファイルを表示

	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			map[y][x] = csv->GetInt(y, x);
		}
	}
	delete csv;

	// 画像 ミノ画像
	MinoImage[2] = LoadGraph("data/image/Lmino_One.PNG");
	MinoImage[3] = LoadGraph("data/image/Jmino_One.PNG");
	MinoImage[4] = LoadGraph("data/image/Tmino_One.PNG");
	MinoImage[5] = LoadGraph("data/image/Omino_One.PNG");
	for (int i = 2; i < 6; i++)
	{
		assert(MinoImage[i] > 0);
	}

	groundImage = LoadGraph("data/image/Ground.JPG");	   // 画像 草ブロック
	assert(groundImage > 0);
	blockImage = LoadGraph("data/image/BlockA2.png");	   // 画像 既存ブロック
	assert(blockImage > 0);
	goalImage = LoadGraph("data/image/GoalLineShort.png"); // 画像 ゴールライン
	assert(goalImage > 0);
	wallImage = LoadGraph("data/image/pole.JPG");    // 画像 壁
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
	pm = FindGameObject<PlayMode>();
}

Stage::~Stage()
{
	DeleteGraph(groundImage);
	DeleteGraph(blockImage);
	DeleteGraph(goalImage);
	DeleteGraph(wallImage);

	DeleteGraph(MinoImage[2]);
	DeleteGraph(MinoImage[3]);
	DeleteGraph(MinoImage[4]);
	DeleteGraph(MinoImage[5]);
}

void Stage::Draw()
{
	//壁表示(仮)
	DrawGraph(30 * 7          , -1440 - scroll, wallImage, TRUE);
	DrawGraph(30 * 7 + 30 * 25, -1440 - scroll, wallImage, TRUE);

	//マップタイル表示
	for (int j = 0; j < HEIGHT; j++)	// 縦「j」
	{
		int y = j * CHIP_SIZE + TOP_SPACE;
		for (int i = 0; i < WIDTH; i++) // 幅「i」
		{
			int x = i * CHIP_SIZE + SIDE_SPACE;

			int chip = map[j][i];
			if (chip == 1)		     // 地面ブロック
			{
				DrawGraph(x, y - scroll, groundImage, TRUE);
			}
			if (chip == 6)		     // 既存ブロック
			{
				DrawGraph(x, y - scroll, blockImage, TRUE);
			}
			else if (chip >= 2 && chip < 6)
			{
				DrawGraph(x, y - scroll, MinoImage[chip], TRUE);
			}
			else if (chip == 8) // ゴールライン
			{
				DrawGraph(x, y - scroll, goalImage, TRUE);
			}
		}
	}
}

//ブロックの当たり判定
int Stage::IsWallRight(VECTOR2 pos) // posにはPlayer座標が入る
{
	int i = (pos.x - SIDE_SPACE) / CHIP_SIZE;
	int j = (pos.y - TOP_SPACE) / CHIP_SIZE;
	for (int x = 1; x < 7; x++) // [1～6]
	{
		if (map[j][i] == x)
		{
			//めり込んだ分押し返す
			//★(int)少数だけどintとして扱う
			int push = ((int)pos.x - SIDE_SPACE) % CHIP_SIZE + 1; //0なら1 1なら2
			return push;
		}
	}
	return 0;
}
int Stage::IsWallLeft(VECTOR2 pos)
{
	int i = (pos.x - SIDE_SPACE) / CHIP_SIZE;
	int j = (pos.y - TOP_SPACE) / CHIP_SIZE;
	for (int x = 1; x < 7; x++) // [1～6]
	{
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
	int i = (pos.x - SIDE_SPACE) / CHIP_SIZE;
	int j = (pos.y - TOP_SPACE) / CHIP_SIZE;
	for (int x = 1; x < 7; x++) // [1～6]
	{
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
	int i = (pos.x - SIDE_SPACE) / CHIP_SIZE;
	int j = (pos.y - TOP_SPACE) / CHIP_SIZE;
	for (int x = 1; x < 7; x++) // [1～6]
	{
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
	int j = (pos.y - TOP_SPACE) / CHIP_SIZE;
	if (map[j][i] == 8)
	{
		return true;
	}
	return false;
}

void Stage::PutBlock(int x, int y, int id)
{
	y = y - (TOP_SPACE - scroll) / CHIP_SIZE;
	x = x - (SIDE_SPACE / CHIP_SIZE);
	map[y][x] = id;

}

bool Stage::CheckBlock(int x, int y)//そこにマップチップがあるか
{
	//「マップチップ→座標」の逆、「座標→マップチップ」
	y = y - (TOP_SPACE - scroll) / CHIP_SIZE;
	if (y < 0) {
		return false;
	}
	x = x - (SIDE_SPACE / CHIP_SIZE);
	int id = map[y][x];
	if (map[y][x] >= 1 && map[y][x] < 7) // [1以上 かつ 7未満]
	{
		return true;

	}
	else { return false; }
}

bool Stage::CheckOnGoal(int x, int y)
{
	y = y - (TOP_SPACE - scroll) / CHIP_SIZE;
	x = x - (SIDE_SPACE / CHIP_SIZE);
	int id = map[y][x];
	if (map[y][x] ==8) // [8=ゴールの時]
	{
		return true;

	}
	else { return false; }
}

// 区切り文字を指定して文字列を分割する
std::vector<std::string> Stage::split(const std::string& text, char delim)
{
	std::vector<std::string>elements;
	std::stringstream ss(text);
	std::string item;
	while (getline(ss, item, delim))
	{
		if (!item.empty())
		{
			elements.push_back(item);
		}
	}
	return elements;
}

