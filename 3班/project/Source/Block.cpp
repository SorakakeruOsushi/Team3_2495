#include "Block.h"
#include "Stage.h"
#include "player.h"
#include <cassert>
#include <time.h>



//やる事
//横移動（押したときだけ）→回転→当たり判定→ランダム生成（NEXT込み）

//テトリス作ろうと思ったけど行き詰った跡(一応残して置いておきますが、気にせずどうぞ)
// 参考動画「テトリスを小一時間で作ってみた�U【C言語ゲームプログラミング実況】Programming Tetris」
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


// ここは、StageXtest.hから持ってきた
const int WIDTH = 24;		//ステージ 幅
const int HEIGHT = 51;		//ステージ 高(もっと高くなる?)50とか

struct BlockPos { // ブロックのある場所を定義
	int blockPos[3][3];
};

const BlockPos shapeL[] = {
	{{
		{2,0,0},
		{2,0,0},
		{2,2,0},
	}}, {{
		{2,2,2},
		{2,0,0},
		{0,0,0},
	}},{{
		{0,2,2},
		{0,0,2},
		{0,0,2},
	}}, {{
		{0,0,0},
		{0,0,2},
		{2,2,2},
	}}
};

const BlockPos shapeJ[] = {
	{{
		{0,0,3},
		{0,0,3},
		{0,3,3},
	}}, {{
		{0,0,0},
		{0,0,3},
		{3,3,3},
	}}, {{
		{3,0,0},
		{3,0,0},
		{3,3,0},
	}}, {{
		{3,3,3},
		{3,0,0},
		{0,0,0},
	}}
};

BlockPos shapeT[] = {
	{{
		{0,0,0},
		{0,4,0},
		{4,4,4},
	}}, {{
		{4,0,0},
		{4,4,0},
		{4,0,0},
	}}, {{
		{4,4,4},
		{0,4,0},
		{0,0,0},
	}}, {{
		{0,0,4},
		{0,4,4},
		{0,0,4},
	}}
};

BlockPos shapeO[] = {
	{{
		{5,5,0},
		{5,5,0},
		{0,0,0},
	}}, {{
		{5,5,0},
		{5,5,0},
		{0,0,0},
	}}, {{
		{5,5,0},
		{5,5,0},
		{0,0,0},
	}}, {{
		{5,5,0},
		{5,5,0},
		{0,0,0},
	}}
};

BlockPos GetBlockPos(Block::ShapeType type, int rot) {
	switch (type) {
	case Block::SHAPE_L:
		return shapeL[rot];
	case Block::SHAPE_J:
		return shapeJ[rot];
	case Block::SHAPE_T:
		return shapeT[rot];
	case Block::SHAPE_O:
		return shapeO[rot];
	}
}


Block::Block()
{

	s = FindGameObject<Stage>();
	assert(s != nullptr);
	p = FindGameObject<Player>();
	assert(p != nullptr);

	isMovedLeft = false;
	isMovedRight = false;
	isTurn = false;

	position.x =WIDTH-5;
	position.y =0;

	blockSize = 30;

	timer = 1.3f;
	counter = 0.0f;
	quickCount = 17.0f;

	srand(time(NULL)); // こうすると、起動するたびに乱数が変わるようになる

	nowBlock.shape = (ShapeType)(rand() % ShapeType::SHAPE_MAX);
	nowBlock.rotation = 0;
	nextBlock.shape = (ShapeType)(rand() % ShapeType::SHAPE_MAX);
	nextBlock.rotation = 0;
	for (int i = 2; i < 6; i++) {
		hImage[i] = -1;
	}
	hImage[2] = LoadGraph("data/image/Lmino_One.png");
	hImage[3] = LoadGraph("data/image/Jmino_One.png");
	hImage[4] = LoadGraph("data/image/Tmino_One.png");
	hImage[5] = LoadGraph("data/image/Omino_One.png");

	pm = FindGameObject<PlayMode>();
	assert(pm != nullptr);
}

Block::~Block()
{
	for (int i = 2; i < 6; i++) {
		if (hImage[i] > 0) {
			DeleteGraph(hImage[i]);
		}
	}
}


void Block::Update()
{
	if (p->finished || p->goaled)
	{
		return;
	}
	else if (pm->playMode == 0)
	{
		return;
	}

	//パッド用関数(毎フレーム呼び出す)
	GetJoypadXInputState(DX_INPUT_PAD1, &input);

	//ブロックを落とす
	if (CheckHitKey(KEY_INPUT_S)) {
		counter += Time::DeltaTime() * quickCount;
		//Sが押されていたらquickCount倍早くcountが進む＝早く落ちる
	}
	else {
		counter += Time::DeltaTime();//押されていなければそのまま
	}
	if (counter >= timer) {
		if (position.y >= 20) { // 本当は、既にあるブロックの上に乗ったら
			nowBlock = nextBlock;
			position.x = WIDTH - 5;
			position.y = 0;
			nextBlock.shape = (ShapeType)(rand() % ShapeType::SHAPE_MAX);
			nextBlock.rotation = 0;
		}
		else {
			position.y++;
		}
		counter = 0.0f;
	}
	//左に移動(A・←・PAD←)
	if (CheckHitKey(KEY_INPUT_A) || (CheckHitKey(KEY_INPUT_LEFT))
		|| (input.Buttons[XINPUT_BUTTON_DPAD_LEFT])) {
		if (isMovedLeft == false) {
			position.x--;
			isMovedLeft = true;
			pressTimerL = 20;//pressTimerを20Fに設定
		}
		pressTimerL--;
		if (pressTimerL <= 0 && isMovedLeft == true) {//pressTimerが0以下かつ長押し中
			position.x--;
			pressTimerL = 3;//pressTimerを3Fに設定(3F毎に繰り返す)
		}
		SetPosition();
		//左に壁があるか調べる
		/*int push = s->IsWallLeft(nowPosition + VECTOR2(0, 0));
		position.x += push;
		push = s->IsWallLeft(nowPosition + VECTOR2(0, 34));
		position.x += push;
		push = s->IsWallLeft(nowPosition + VECTOR2(0, 35));
		position.x += push;
		push = s->IsWallLeft(nowPosition + VECTOR2(0, 69));
		position.x += push;*/
	}
	else {
		isMovedLeft = false;
	}
	//右に移動(D・→・PAD→)
	if (CheckHitKey(KEY_INPUT_D) || (CheckHitKey(KEY_INPUT_RIGHT))
		|| (input.Buttons[XINPUT_BUTTON_DPAD_RIGHT])) {
		if (isMovedRight == false) {
			position.x++;
			isMovedRight = true;
			pressTimerR = 20;//pressTimerを20Fに設定
		}
		pressTimerR--;
		if (pressTimerR <= 0 && isMovedRight) {//pressTimerが0以下かつ長押し中
			position.x++;
			pressTimerR = 3;//pressTimerを3Fに設定(3F毎に繰り返す)
		}

	}
	else {
		isMovedRight = false;
	}
	// 回転(スペース、RBボタン)
	if (CheckHitKey(KEY_INPUT_SPACE) ||
		input.Buttons[XINPUT_BUTTON_RIGHT_SHOULDER]) {
		if (not isTurn) {
			nowBlock.rotation = (nowBlock.rotation + 1) % 4; // ４回転で一周
			isTurn = true;
			pressTimerRT = 20;//pressTimerを20Fに設定
		}
		pressTimerRT--;
		if (pressTimerRT <= 0 && isTurn) {
			nowBlock.rotation = (nowBlock.rotation + 1) % 4;
			pressTimerRT = 3;//pressTimerを3Fに設定(3F毎に繰り返す)
		}
	}
	//左回転(左右のShift、LBボタン)
	else if (CheckHitKey(KEY_INPUT_RSHIFT) || CheckHitKey(KEY_INPUT_LSHIFT)
		|| input.Buttons[XINPUT_BUTTON_LEFT_SHOULDER]) {
		if (not isTurn) {
			nowBlock.rotation -= 1;
			if (nowBlock.rotation <= -1) {
				nowBlock.rotation = 3;
			}
			isTurn = true;
			pressTimerLT = 20;//pressTimerを20Fに設定
		}
		pressTimerLT--;
		if (pressTimerLT <= 0 && isTurn) {//pressTimerが0以下かつ長押し中
			TurnWaitTimer--;
			if (TurnWaitTimer < 0) {
				TurnWaitTimer = 2;//回転の書き方のせいでここだけ早いので遅延
				nowBlock.rotation -= 1;
				if (nowBlock.rotation <= -1) {
					nowBlock.rotation = 3;
					pressTimerLT = 3;//pressTimerを3Fに設定(3F毎に繰り返す)
				}
			}
		}
	}
	else {
		isTurn = false;
	}
}

void Block::Draw()
{
	BlockPos block = GetBlockPos(nowBlock.shape, nowBlock.rotation);
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			int id = block.blockPos[y][x];
			if (id > 0) {
				DrawGraph((position.x + x) * blockSize, (position.y + y) * blockSize, hImage[id], TRUE);
			}
		}
	}

	block = GetBlockPos(nextBlock.shape, nextBlock.rotation);
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			int id = block.blockPos[y][x];
			if (id > 0) {
				DrawGraph(1065 + x * blockSize, 120 + y * blockSize, hImage[id], TRUE);
			}
		}
	}
}
