
#pragma once
#include "../Library/gameObject.h"
#include "Vector2.h"
#include "Player.h"

class CoinSP : public GameObject
{
public:
	CoinSP();
	~CoinSP();
	void Update() override;
	void Draw() override;

	Stage* s;
	Player* p;

	int coinSPImage; // 画像 コイン
	int coinSPSound; // 音 コイン取得

	int patternX;
	float animTimer;

	VECTOR2 position;

	bool got;	   // コインが取られた

	bool CoinDraw;
	float destroyTimer;     //コイン表示タイマー
	float destroyTimeLimit; //コイン表示時間
	float v;//跳ねる動きの速度

	float destroyCountDown;
	void destroyCountDownTimer();
	bool nowPlaySE = false;
};