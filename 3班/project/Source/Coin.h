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

	bool got;	 //�������͑�ςȃR�C���𓐂�ł����܂���
	int counter; //�R�C���\���̎���

	float v;	 //���˂铮���̑��x
};