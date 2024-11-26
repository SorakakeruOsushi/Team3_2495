#pragma once
#include "../Library/gameObject.h"
#include "Vector2.h"
#include "Player.h"

class Stage : public GameObject
{
public:
	Stage();
	~Stage();
	void Draw() override;

	int IsWallRight(VECTOR2 pos);
	int IsWallLeft(VECTOR2 pos);
	int IsWallDown(VECTOR2 pos);
	int IsWallUp(VECTOR2 pos);

	bool IsGoal(VECTOR2 pos);

	Player* p;

	int emptyImage;  // �摜 �}�X��
	int blockImage;  // �摜 �D�u���b�N
	int goalImage;	 // �摜 �S�[��(��)

	int scroll;		//��ʂ̃X�N���[��
};
