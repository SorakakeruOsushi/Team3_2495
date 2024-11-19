#include "Block.h"
#include "Stage.h"
#include "player.h"
#include <cassert>

//テトリス作ろうと思ったけど行き詰った跡(一応残して置いておきますが、気にせずどうぞ)
// 参考動画「テトリスを小一時間で作ってみたⅡ【C言語ゲームプログラミング実況】Programming Tetris」
// h ttps://youtu.be/BJs29RicyPw?si=-gs57ir-W4lnC66g
/*
//「Shape:形」

//データの大きさ
#define SHAPE_WIDTH_MAX (4)
#define SHAPE_HEIGHT_MAX (4)

//列挙型enum
enum {
	SHAPE_I,
	SHAPE_O,
	SHAPE_S,
	SHAPE_Z,
	SHAPE_J,
	SHAPE_L,
	SHAPE_T,
	SHAPE_MAX
};

//SHAPE構造体宣言
//形状の構造体
typedef struct 
{
	int width, height;							    //幅と高さ
	int pattern[SHAPE_WIDTH_MAX][SHAPE_HEIGHT_MAX]; //パターンの数
}SHAPE; // SHAPE型とする(?)

//テトリミノの構造体
typedef struct
{
	int  x, y;   // 座標データ
	SHAPE shape; // 形状データ
}MINO; // MINO型とする(?)


//SHAPEの実体
//構造体の中身を設定
SHAPE shapes[SHAPE_MAX] = {
	// SHAPE_I
	{
		//int width, height; //幅と高さ
		4,4,
		{
		//int pattern[SHAPE_WIDTH_MAX][SHAPE_HEIGHT_MAX]; //パターンの数
			{0,0,0,0},
			{1,1,1,1},
			{0,0,0,0},
			{0,0,0,0}
		}
	},
	// SHAPE_O
	{
		//int width, height; //幅と高さ
		2,2,
		{
		//int pattern[SHAPE_WIDTH_MAX][SHAPE_HEIGHT_MAX]; //パターンの数
			{1,1},
			{1,1}
		}
	},
	// SHAPE_S
	{
		//int width, height; //幅と高さ
		3,3,
		{
		//int pattern[SHAPE_WIDTH_MAX][SHAPE_HEIGHT_MAX]; //パターンの数
			{0,1,1},
			{1,1,0},
			{0,0,0}
		}
	},
	// SHAPE_Z
	{
		//int width, height; //幅と高さ
		3,3,
		{
		//int pattern[SHAPE_WIDTH_MAX][SHAPE_HEIGHT_MAX]; //パターンの数
			{1,1,0},
			{0,1,1},
			{0,0,0}
		}
	},
	// SHAPE_J
	{
		//int width, height; //幅と高さ
		3,3,
		{
		//int pattern[SHAPE_WIDTH_MAX][SHAPE_HEIGHT_MAX]; //パターンの数
			{1,0,0},
			{1,1,1},
			{0,0,0}
		}
	},
	// SHAPE_L
	{
		//int width, height; //幅と高さ
		3,3,
		{
		//int pattern[SHAPE_WIDTH_MAX][SHAPE_HEIGHT_MAX]; //パターンの数
			{0,0,1},
			{1,1,1},
			{0,0,0}
		}
	},
	// SHAPE_T
	{
		//int width, height; //幅と高さ
		3,3,
		{
		//int pattern[SHAPE_WIDTH_MAX][SHAPE_HEIGHT_MAX]; //パターンの数
			{0,1,0},
			{1,1,1},
			{0,0,0}
		}
	},
};

//Stageの内容?
//int map[WIDTH][HEIGHT];
//int screen[WIDTH][HEIGHT];//これにマップとミノを書き込む
//MINO mino;
////////////////////////////////////////////////////*/


Block::Block()
{
	hImage = LoadGraph("data/image/Tmino_30.png");
	assert(hImage > 0);

	position.x = 0;
	position.y = 0;

	blockSize = 30;

	time = 1.5f;
	counter = 0.0f;

	//mino.shape = shapes[rand() % SHAPE_MAX]; // ランダムなミノが選ばれる
}

Block::~Block()
{
	DeleteGraph(hImage);
}



void Block::Update()
{
	//ブロックを落とす
	counter += Time::DeltaTime();
	if (counter >= time) {
		position.y += blockSize;
		counter = 0.0f;
	}

}

void Block::Draw()
{
	DrawGraph(position.x, position.y, hImage, TRUE);
}
