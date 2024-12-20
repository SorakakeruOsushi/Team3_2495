#include "Stage.h"
#include <cassert>
#include <sstream>
#include <fstream>
#include "Player.h"
#include "Block.h"


//開始時にステージをランダムでロードしたい
//#include "stageXtest.h"
//#include "stage1.h"
const int WIDTH = 24;		//ステージ 幅
const int HEIGHT = 51;		//ステージ 高(もっと高くなる?)50とか

int map[HEIGHT][WIDTH];


const int TOP_SPACE = -(CHIP_SIZE * (HEIGHT - 24)); 
const int SIDE_SPACE = CHIP_SIZE * 8; //横余白
const char* STAGE_DATA_PATH = "data/Stage/Stage%02d.csv";	//	ブロック配置情報のファイル名



Stage::Stage()
{
#if false
	for (int y = 0; y < HEIGHT; y++) 
	{
		for (int x = 0; x < WIDTH; x++) 
		{
			map[y][x] = orgmap[y][x];
		}
	}
#endif

	//ランダムなCSVファイルを読み込んでステージ生成する！(堀越先生ありがとう！)
	int stageNo = 0;
	stageNo = GetRand(9) + 1;

	char stageFile[100];
	sprintf_s(stageFile, STAGE_DATA_PATH, stageNo);

	// std::ifstream ifs(stageFile);		  //Stage(01～10).CSV
	std::ifstream ifs("data/Stage/test.csv"); //テスト.CSV

	std::string text;
	int y = 0;
	while (std::getline(ifs, text))
	{
		//  [,]で分割する
		std::vector<std::string> element = split(text, ',');

		for (int x = 0; x < element.size(); x++)
		{
			int id = std::stoi(element[x]);
			map[y][x] = id;
		}
		y++;
	}
	ifs.close();

	
	// 画像 ミノ画像
	MinoImage[2] = LoadGraph("data/image/Lmino.PNG");
	MinoImage[3] = LoadGraph("data/image/Jmino.PNG");
	MinoImage[4] = LoadGraph("data/image/Tmino.PNG");
	MinoImage[5] = LoadGraph("data/image/Omino.PNG");
	for (int i = 2; i < 6; i++) {
 		assert(MinoImage[i] > 0);
	}

	emptyImage = LoadGraph("data/image/EmptyA1.png");	   // 画像 空っぽマス
		assert(emptyImage > 0);
	blockImage = LoadGraph("data/image/Ground.JPG");	   // 画像 草ブロック
		assert(blockImage > 0);
	goalImage = LoadGraph("data/image/GoalLineShort.png"); // 画像 草ブロック
		assert(goalImage > 0);
	wallImage = LoadGraph("data/image/WallA1Long.png");    // 画像 壁
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
	x = x - (SIDE_SPACE / CHIP_SIZE);
	int id = map[y][x];
	if (map[y][x]>=1&&map[y][x]<6)
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

