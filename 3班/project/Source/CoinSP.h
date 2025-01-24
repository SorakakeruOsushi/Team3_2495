
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

	int coinSPImage; // �摜 �R�C��
	int coinSPSound; // �� �R�C���擾

	int patternX;
	float animTimer;

	VECTOR2 position;

	bool got;	   // �R�C�������ꂽ

	bool CoinDraw;
	float destroyTimer;     //�R�C���\���^�C�}�[
	float destroyTimeLimit; //�R�C���\������
	float v;//���˂铮���̑��x

	float destroyCountDown;
	void destroyCountDownTimer();
	bool nowPlaySE = false;
};