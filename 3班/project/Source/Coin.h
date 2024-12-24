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

	int coinImage; // �摜 �R�C���摜
	int coinSE;    // SE �R�C���擾��

	VECTOR2 position;

	bool got;	   // �R�C�������ꂽ

	bool CoinDraw;
	float destroyTimer;     //�R�C���\���^�C�}�[
	float destroyTimeLimit; //�R�C���\������
	float v;//���˂铮���̑��x
};