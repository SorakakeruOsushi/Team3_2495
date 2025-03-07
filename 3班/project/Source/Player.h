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

	int jumpCount;
	int maxJump;

	int gotCoin;		// コイン取得数
	int gotCoinSP;		// コインSP取得数

	bool finished;		// 死んだ！
	bool goaled;		// ゴール

	bool IsWalkLeft = false;
	bool IsWalkRight = false;
	int patternX;
	int patternY;
	float timer;
	int collisionDown; // プレイヤーの当たり判定の位置を足元に合わせる
	int outOfScreen;   // プレイヤーがどの程度画面の外に出たらゲームオーバーになるか
};