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

	float playerHeight;
	float prePlayerY;

	float speed;		//速度
	float velocity;		//速度(力?)

	bool prevJumpKey;	//前のジャンプキー
	bool onGround;		//接地判定

	bool finished;		//死んだ！
	bool goaled;		//ゴール
};