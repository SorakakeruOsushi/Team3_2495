#pragma once
#include "../Library/gameObject.h"
#include "Vector2.h"
#include "time.h"
#include "Stage.h"

class Player : public GameObject {
public:
	Player();
	~Player();
	void Update() override;
	void Draw() override;

	int hImage;
	int jumpSE;    // サウンドハンドル(Hit) 

	Stage* s;

	VECTOR2 position;

	float playerHeight;
	float prePlayerY;

	float speed;		//速度


	float velocity;		//力と方向
	bool prevJumpKey;	//前のジャンプキー
	bool onGround;		//接地判定

	bool finished;		//死んだ！
	bool goaled;		//ゴール

	bool IsWalkLeft;
	bool IsWalkRight;
	int patternX;
	int patternY;
	float timer;

	XINPUT_STATE input; //PAD操作用変数
};