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

	float speed;		//���x
	float velocity;		//���x(��?)

	bool prevJumpKey;	//�O�̃W�����v�L�[
	bool onGround;		//�ڒn����

	bool finished;		//���񂾁I
	bool goaled;		//�S�[��
};