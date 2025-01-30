#include "Block.h"
#include "Stage.h"
#include "player.h"
#include <cassert>
#include <time.h>



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
		{3,0,0},
		{3,3,3},
	}}, {{
		{3,3,0},
		{3,0,0},
		{3,0,0},
	}}, {{
		{3,3,3},
		{0,0,3},
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
	sameMino = true;
	s = FindGameObject<Stage>();
	assert(s != nullptr);
	p = FindGameObject<Player>();
	assert(p != nullptr);

	TurnSound=LoadSoundMem("data/sound/GameSE/ブロック回転１.mp3");//回転音
	assert(TurnSound > 0);
	PutSound= LoadSoundMem("data/sound/GameSE/ブロック設置４.mp3");//設置音
	assert(PutSound > 0);


	isMovedLeft = false;
	isMovedRight = false;
	isTurn = false;

	putBlock = false;

	position.x =WIDTH-5;
	position.y =0;

	blockSize = 30;

	timer = 1.3f;
	counter = 0.0f;
	quickCount = 17.0f;

	srand(time(NULL)); // こうすると、起動するたびに乱数が変わるようになる

	nowBlock.shape = (ShapeType)(rand() % ShapeType::SHAPE_MAX);
	nowBlock.rotation = 0;
	while (sameMino) {
		nextBlock.shape = (ShapeType)(rand() % ShapeType::SHAPE_MAX);
		if (nextBlock.shape == nowBlock.shape) {//nowBlockとnextBlockの形が同じとき
			sameMino = true;//繰り返す
		}
		else {
			sameMino = false;
		}
	}
	sameMino = true;
	nextBlock.rotation = 0;
	for (int i = 2; i < 6; i++) {
		hImage[i] = -1;
	}
	for (int i = 2; i < 6; i++) {
		NextImage[i] = -1;
	}
	hImage[2] = LoadGraph("data/image/Lmino.PNG");
	hImage[3] = LoadGraph("data/image/Jmino.PNG");
	hImage[4] = LoadGraph("data/image/Tmino.PNG");
	hImage[5] = LoadGraph("data/image/Omino.PNG");

	NextImage[2] = LoadGraph("data/image/Lmino_One.PNG");
	NextImage[3] = LoadGraph("data/image/Jmino_One.PNG");
	NextImage[4] = LoadGraph("data/image/Tmino_One.PNG");
	NextImage[5] = LoadGraph("data/image/Omino_One.PNG");

	pm = FindGameObject<PlayMode>();
	assert(pm != nullptr);
}

Block::~Block()
{
	for (int i = 2; i < 6; i++) {
		if (hImage[i] > 0) {
			DeleteGraph(hImage[i]);
		}
		if (NextImage[i] > 0) {
			DeleteGraph(NextImage[i]);
		}
	}
}


void Block::Update()
{
	if (!pm->IsGameStart)		 // ゲーム開始前
	{
		return;
	}
	if (p->finished || p->goaled)// ゲーム終了
	{
		return;
	}
	else if (pm->playMode == 0)	 // テトラモード
	{
		return;
	}

	//パッド用関数(毎フレーム呼び出す)
	GetJoypadXInputState(DX_INPUT_PAD1, &input);

	//ブロックを落とす
	if (CheckHitKey(KEY_INPUT_S)||CheckHitKey(KEY_INPUT_DOWN)
		|| (input.Buttons[XINPUT_BUTTON_DPAD_LEFT])) {
		counter += Time::DeltaTime() * quickCount;
		//Sが押されていたらquickCount倍早くcountが進む＝早く落ちる
	}
	else {
		counter += Time::DeltaTime();//押されていなければそのまま
	}
	if (counter >= timer) {//地面についたら置く
		BlockPos block = GetBlockPos(nowBlock.shape, nowBlock.rotation);
		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {
				int id = block.blockPos[y][x];
				if (id > 0) {
					if (s->CheckBlock(position.x + x, (position.y + y) + 1)) { // ミノの下に障害物があれば
						BlockPos block = GetBlockPos(nowBlock.shape, nowBlock.rotation);
						for (int y = 0; y < 3; y++) {
							for (int x = 0; x < 3; x++) {
								int id = block.blockPos[y][x];
								if (s->CheckOnGoal(position.x + x, position.y + y)) {//ゴールとミノがかぶっていたら消滅
									nowBlock = nextBlock;
									position.x = WIDTH - 5;
									position.y = 0;
									while (sameMino) {
										nextBlock.shape = (ShapeType)(rand() % ShapeType::SHAPE_MAX);
										if (nextBlock.shape == nowBlock.shape) {//nowBlockとnextBlockの形が同じとき
											sameMino = true;//繰り返す
										}
										else {
											sameMino = false;
										}
									}
									sameMino = true;
									nextBlock.rotation = 0;
									return;
								}
								else if(position.y+y < 4){//上から四列に設置したミノを消去
									nowBlock = nextBlock;
									position.x = WIDTH - 5;
									position.y = 0;
									while (sameMino) {
										nextBlock.shape = (ShapeType)(rand() % ShapeType::SHAPE_MAX);
										if (nextBlock.shape == nowBlock.shape) {//nowBlockとnextBlockの形が同じとき
											sameMino = true;//繰り返す
										}
										else {
											sameMino = false;
										}
									}
									sameMino = true;
									nextBlock.rotation = 0;
									return;
								}
								else{
									if (id > 0) {
										s->PutBlock(position.x + x, position.y + y, id);//ミノを配置する
										PlaySoundMem(PutSound, DX_PLAYTYPE_BACK); // 設置音の再生
									}
								}
							}
						}
						nowBlock = nextBlock;
						position.x = WIDTH - 5;
						position.y = 0;
						while (sameMino) {
							nextBlock.shape = (ShapeType)(rand() % ShapeType::SHAPE_MAX);
							if (nextBlock.shape == nowBlock.shape) {//nowBlockとnextBlockの形が同じとき
								sameMino = true;//繰り返す
							}
							else {
								sameMino = false;
							}
						}
						sameMino = true;
							nextBlock.rotation = 0;
						return;
					}
				}
			}
		}
		if (position.y > 24) {//画面外に3ブロック分出たら現在のブロックを消去
			nowBlock = nextBlock;
			position.x = WIDTH - 5;
			position.y = 0;
			while (sameMino) {
				nextBlock.shape = (ShapeType)(rand() % ShapeType::SHAPE_MAX);
				if (nextBlock.shape == nowBlock.shape) {//nowBlockとnextBlockの形が同じとき
					sameMino = true;//繰り返す
				}
				else {
					sameMino = false;
				}
			}
			sameMino = true;
			nextBlock.rotation = 0;
			return;
		}
		
			position.y++;
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
		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {
				BlockPos block = GetBlockPos(nowBlock.shape, nowBlock.rotation);
				int id = block.blockPos[y][x];
				if (id > 0) {
					if (s->CheckBlock(position.x + x, position.y + y)) { 
						BlockPos block = GetBlockPos(nowBlock.shape, nowBlock.rotation);
						position.x += 1;
					}
				}
			}
		}
		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {
				BlockPos block = GetBlockPos(nowBlock.shape, nowBlock.rotation);
				int id = block.blockPos[y][x];
				if (id > 0) {
					if (position.x+x-1 <= WIDTH - 5 - 13) { // 左の壁にかぶったら
						position.x +=1;
					}
				}
			}
		}
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
		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {
				BlockPos block = GetBlockPos(nowBlock.shape, nowBlock.rotation);
				int id = block.blockPos[y][x];
				if (id > 0) {
					if (s->CheckBlock(position.x + x, position.y+y)) {
						BlockPos block = GetBlockPos(nowBlock.shape, nowBlock.rotation);
						position.x -= 1;
					}
				}
			}
		}
		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {
				BlockPos block = GetBlockPos(nowBlock.shape, nowBlock.rotation);
				int id = block.blockPos[y][x];
				if (id > 0) {
					if (position.x+x+1 >= WIDTH - 5 + 14) { // 右の壁にかぶったら
						BlockPos block = GetBlockPos(nowBlock.shape, nowBlock.rotation);
						position.x -=1;
					}
				}
			}
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
			PlaySoundMem(TurnSound, DX_PLAYTYPE_BACK); // 回転音の再生
			isTurn = true;
			
		}
		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {
				BlockPos block = GetBlockPos(nowBlock.shape, nowBlock.rotation);
				int id = block.blockPos[y][x];
				if (id > 0) {
					if (s->CheckBlock(position.x + x, position.y + y)) { 
						BlockPos block = GetBlockPos(nowBlock.shape, nowBlock.rotation);
						position.y -= 1;
					}
				}
			}
		}
		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {
				BlockPos block = GetBlockPos(nowBlock.shape, nowBlock.rotation);
				int id = block.blockPos[y][x];
				if (id > 0) {
					if (id > 0) {
						if (position.x + x - 1 <= WIDTH - 5 - 13) { // 左の壁にかぶったら
							position.x += 1;
						}
					}
				}
			}
		}
		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {
				BlockPos block = GetBlockPos(nowBlock.shape, nowBlock.rotation);
				int id = block.blockPos[y][x];
				if (id > 0) {
					if (position.x + x + 1 >= WIDTH - 5 + 14) { // 右の壁にかぶったら
						BlockPos block = GetBlockPos(nowBlock.shape, nowBlock.rotation);
						position.x -= 1;
					}
				}
			}
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
			PlaySoundMem(TurnSound, DX_PLAYTYPE_BACK); // ジャンプ音の再生
			isTurn = true;
		}
		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {
				BlockPos block = GetBlockPos(nowBlock.shape, nowBlock.rotation);
				int id = block.blockPos[y][x];
				if (id > 0) {
					if (s->CheckBlock(position.x + x, position.y + y)) { // ミノの下に障害物があれば
						BlockPos block = GetBlockPos(nowBlock.shape, nowBlock.rotation);
						position.y -= 1;
					}
				}
			}
		}
		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {
				BlockPos block = GetBlockPos(nowBlock.shape, nowBlock.rotation);
				int id = block.blockPos[y][x];
				if (id > 0) {
					if (position.x + x - 1 <= WIDTH - 5 - 13) { // 左の壁にかぶったら
						position.x += 1;
					}
				}
			}
		}
		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {
				BlockPos block = GetBlockPos(nowBlock.shape, nowBlock.rotation);
				int id = block.blockPos[y][x];
				if (id > 0) {
					if (position.x + x + 1 >= WIDTH - 5 + 14) { // 右の壁にかぶったら
						BlockPos block = GetBlockPos(nowBlock.shape, nowBlock.rotation);
						position.x -= 1;
					}
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
	int Xmax = -9999999;
	int Xmin = 9999999;

	if (pm->playMode == 1)	 // ブロック消去範囲の表示
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
		DrawBox(240, 0, 960, 120, GetColor(255, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 256);
	}

	BlockPos block = GetBlockPos(nowBlock.shape, nowBlock.rotation);
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			int id = block.blockPos[y][x];
			if (id > 0) {
				if (position.x + x > Xmax) {//ミノの右側の座標を得る
					Xmax = position.x + x;
				}
				if (position.x + x < Xmin) {//左側の座標を得る
					Xmin = position.x + x;
				}
			}
		}
	}
	if (pm->playMode == 1) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
		DrawBox(Xmin * blockSize, 0, (Xmax + 1) * blockSize, 690, GetColor(255, 255, 255), TRUE);//ブロックを囲む枠組みを作る
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 256);
	}
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			int id = block.blockPos[y][x];
			if (id > 0) {
				if (pm->playMode == 1) {
					DrawGraph((position.x + x) * blockSize, (position.y + y) * blockSize, hImage[id], TRUE);
				}
				else {
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
					DrawGraph((position.x + x) * blockSize, (position.y + y) * blockSize, hImage[id], TRUE);
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 256);
				}
			}
		}
	}



	block = GetBlockPos(nextBlock.shape, nextBlock.rotation);
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			int id = block.blockPos[y][x];
			if (id == 2 || id == 5) {
				DrawGraph(1115 + x * blockSize, 110 + y * blockSize, NextImage[id], TRUE);
			}
			else if (id == 4) {
				DrawGraph(1105 + x * blockSize, 95 + y * blockSize, NextImage[id], TRUE);
			}
			else if (id == 3) {
				DrawGraph(1090 + x * blockSize, 110 + y * blockSize, NextImage[id], TRUE);
			}
		}
	}
}

void Block::SetPosition(int x,int y)
{
			nowPosition.x =x;
			nowPosition.y =y;
}

