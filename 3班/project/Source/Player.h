#pragma once
#include "../Library/gameObject.h"
#include "Vector2.h"

class Player : public GameObject {
public:
	Player();
	~Player();
	void Update() override;
	void Draw() override;

	int hImage;
	VECTOR2 position;

	float speed;		//速度
	float velocity;		//速度(力?)

	int score = 0;
	int highScore = 0;

	bool prevJumpKey;	//前のジャンプキー
	bool onGround;		//接地判定

	bool finish;		//死んだ！
	bool goal;			//ゴール

	int playerHeight;   //高さ
};