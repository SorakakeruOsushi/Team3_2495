#pragma once
#include "../Library/gameObject.h"
#include "Vector2.h"
#include "time.h"
//#include "Stage.h"
#include "PlayMode.h"
class Stage;

class Player : public GameObject {
public:
	Player();
	~Player();
	void Update() override;
	void Draw() override;

	int playerImage; // 画像 プレイヤー
	int jumpSound;   // 音 ジャンプ

	XINPUT_STATE input; //PAD操作用変数
	
	Stage* s;
	PlayMode* pm;

	VECTOR2 position;

	float playerHeight;
	float prePlayerY;

	float speed;		// 速度

	float velocity;		// 力と方向
	bool prevJumpKey;	// 前のジャンプキー
	bool onGround;		// 接地判定

	int gotCoin;		// コイン取得数

	bool finished;		// 死んだ！
	bool goaled;		// ゴール

	bool IsWalkLeft;
	bool IsWalkRight;
	int patternX;
	int patternY;
	float timer;
};