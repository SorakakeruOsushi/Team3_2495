#pragma once
#include "../Library/gameObject.h"
#include "Vector2.h"
#include "time.h"
#include "Stage.h"

class Player : public GameObject {
public:
	Player();
	~Player();
	void Update() override;
	void Draw() override;

	int hImage;
	int jumpSE;    // �T�E���h�n���h��(Hit) 

	Stage* s;

	VECTOR2 position;

	float playerHeight;
	float prePlayerY;

	float speed;		//���x


	float velocity;		//�͂ƕ���
	bool prevJumpKey;	//�O�̃W�����v�L�[
	bool onGround;		//�ڒn����

	bool finished;		//���񂾁I
	bool goaled;		//�S�[��

	bool IsWalkLeft;
	bool IsWalkRight;
	int patternX;
	int patternY;
	float timer;

	XINPUT_STATE input; //PAD����p�ϐ�
};