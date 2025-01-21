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
	int playerIdolImage; // 画像 IDOLプレイヤー
	int playerAnimImage; // 画像 ANIMプレイヤー

	int jumpSound;   // 音 ジャンプ
	int fallSound;	 // 音 画面外へ

	XINPUT_STATE input; //PAD操作用変数
	
	Stage* s;
	PlayMode* pm;

	VECTOR2 position;

	int alpha;

	float playerHeight;
	float prePlayerY;
	float playerBestHeight;

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
	int outOfScreen;   // プレイヤーがどの程度画面の外に出たらゲームオーバーになるか
};