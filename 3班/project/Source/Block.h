#pragma once
#include "../Library/GameObject.h"
#include "Vector2.h"
#include "PlayMode.h"


class Block :
	public GameObject
{
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

	float timer; // timeという名前は使っているので、timerにしました
	float counter;
	float quickCount;//Sを押している時にcounterを増やす倍率
	float pressTimerLeft;//左長押しの時間
	float pressTimerRight;//右長押しの時間

	bool isMovedLeft;//右に移動したか
	bool isMovedRight;//左に移動したか
	bool isTurn;//回転したか

	//bool isLongPressLeft;//左の長押し
	//bool isLongPressRight;//右の長押し

	PlayMode* pm;
};

