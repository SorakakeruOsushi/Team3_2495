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

	float speed;		//���x
	float velocity;		//���x(��?)

	int score = 0;
	int highScore = 0;

	bool prevJumpKey;	//�O�̃W�����v�L�[
	bool onGround;		//�ڒn����

	bool finish;		//���񂾁I
	bool goal;			//�S�[��

	int playerHeight;   //����
};