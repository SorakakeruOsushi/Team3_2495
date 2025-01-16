#pragma once
#include "../Library/GameObject.h"
#include "Vector2.h"
#include "PlayMode.h"
#include "Stage.h"


class Block :
	public GameObject
{private:
	Stage* s;
public:
	Block();
	~Block();
	void Update() override;
	void Draw() override;


	int hImage[6]; // 画像は全て持っておく
	struct IVECTOR2 {
		int x;
		int y;
	};
	IVECTOR2 position; // 座標は、ブロックのマスで持っておく

	VECTOR2 nowPosition;

	void SetPosition(int x,int y);

	int blockSize; // ブロックサイズはintで

	enum ShapeType {
		SHAPE_L,
		SHAPE_J,
		SHAPE_T,
		SHAPE_O,
		SHAPE_MAX
	};
	struct BlockSet {
		ShapeType shape;  // ブロックの形
		int rotation; // ブロックの回転
	};
	BlockSet nextBlock; // nextのブロック
	BlockSet nowBlock;  // 今のブロック
	bool sameMino;//ブロックが違うか

	float timer; // timeという名前は使っているので、timerにしました
	float counter;
	float quickCount;//Sを押している時にcounterを増やす倍率
	float pressTimerL=20;
	float pressTimerR = 20;
	float pressTimerRT = 20;
	float pressTimerLT = 20;
	float TurnWaitTimer = 2;

	bool isMovedLeft;//右に移動したか
	bool isMovedRight;//左に移動したか
	bool isTurn;//回転したか
	bool putBlock;//Xで置く用　仮

	int TurnSound;
	int PutSound;

	PlayMode* pm;
	Player* p;

	XINPUT_STATE input; //PAD操作用変数
};

