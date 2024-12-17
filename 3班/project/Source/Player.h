#pragma once
#include "../Library/gameObject.h"
#include "Vector2.h"
#include "time.h"
//#include "Stage.h"
#include "PlayMode.h"
class Stage;

class Player : public GameObject {
public:
	Player();
	~Player();
	void Update() override;
	void Draw() override;

	int hImage; // �摜 �v���C���[
	int jumpSE; // SE �W�����v��

	XINPUT_STATE input; //PAD����p�ϐ�
	
	Stage* s;
	PlayMode* pm;

	VECTOR2 position;

	float playerHeight;
	float prePlayerY;

	float speed;		//���x


	float velocity;		//�͂ƕ���
	bool prevJumpKey;	//�O�̃W�����v�L�[
	bool onGround;		//�ڒn����

	int gotCoin;		//�R�C���擾��

	bool finished;		//���񂾁I
	bool goaled;		//�S�[��

	bool IsWalkLeft;
	bool IsWalkRight;
	int patternX;
	int patternY;
	float timer;
};