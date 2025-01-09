#pragma once
#include "../Library/gameObject.h"
#include "Vector2.h"
#include "Player.h"

class Coin : public GameObject
{
public:
	Coin();
	~Coin();
	void Update() override;
	void Draw() override;

	Stage* s;
	Player* p;

	int coinImage; // 画像 コイン
	int coinSound; // 音 コイン取得

	VECTOR2 position;

	bool got;	   // コインが取られた

	bool CoinDraw;
	float destroyTimer;     //コイン表示タイマー
	float destroyTimeLimit; //コイン表示時間
	float v;//跳ねる動きの速度
};