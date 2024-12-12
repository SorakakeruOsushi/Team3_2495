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

	int coinImage;
	VECTOR2 position;

	bool got;	 //魔理沙は大変なコインを盗んでいきました
	int counter; //コイン表示の寿命

	float v;	 //跳ねる動きの速度
};