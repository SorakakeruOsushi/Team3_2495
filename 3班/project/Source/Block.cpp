#include "Block.h"
#include "Stage.h"
#include "player.h"
#include <cassert>


//やる事
//横移動（押したときだけ）→回転→当たり判定→ランダム生成（NEXT込み）

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
	isMovedLeft = false;
	isMovedRight = false;
	
	position.x = 0;
	position.y = 0;

	blockSize = 30;

	time = 1.3f;
	counter = 0.0f;
	quickCount = 17.0f;

	for (int i = 0; i < 10; i++) {
		rand();//乱数表の初期値10個を捨てる(よりランダムにするため)
	}

	// ランダムなミノが選ばれる
	switch (rand() % 4) {
	case 0:
		hImage = LoadGraph("data/image/Tmino_30.png");
		assert(hImage > 0);
		break;
	case 1:
		hImage = LoadGraph("data/image/Jmino_30.png");
		assert(hImage > 0);
		break;
	case 2:
		hImage = LoadGraph("data/image/Lmino_30.png");
		assert(hImage > 0);
		break;
	case 3:
		hImage = LoadGraph("data/image/Omino_30.png");
		assert(hImage > 0);
		break;
	} 
}

Block::~Block()
{
	DeleteGraph(hImage);
}



void Block::Update()
{
	//ブロックを落とす
	if (CheckHitKey(KEY_INPUT_S)) {
		 counter += Time::DeltaTime()*quickCount;
		//Sが押されていたらquickCount倍早くcountが進む＝早く落ちる
	}
	else {
		counter += Time::DeltaTime();//押されていなければそのまま
	}
	if (counter >= time) {
		position.y += blockSize;
		counter = 0.0f;
	}
	//左に移動
	if (CheckHitKey(KEY_INPUT_A)) {
		if (isMovedLeft == false) {
			position.x -= blockSize;
			isMovedLeft = true;
		}
	}
	else {
		isMovedLeft = false;
	}
	//右に移動
	if (CheckHitKey(KEY_INPUT_D)) {
		if (isMovedRight == false) {
			position.x += blockSize;
			isMovedRight = true;
		}
	}
	else {
		isMovedRight = false;
	}

}

void Block::Draw()
{
	DrawGraph(position.x, position.y, hImage, TRUE);
}
