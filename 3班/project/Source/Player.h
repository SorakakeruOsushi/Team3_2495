#pragma once
#include "../Library/gameObject.h"
#include "Vector2.h"
#include "time.h"

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

	float speed;		//���x

	int jumpSE;    // �T�E���h�n���h��(Hit) 


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
};