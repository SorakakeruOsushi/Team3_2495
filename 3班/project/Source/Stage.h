#pragma once
#include "../Library/gameObject.h"
#include "Vector2.h"
#include "Screen.h"
//#include "Player.h"
class Player;
const int CHIP_SIZE = 30;   //�`�b�v�T�C�Y
class Stage : public GameObject
{
public:
	Stage();
	~Stage();
	void Draw() override;

	int emptyImage;  // �摜 �}�X��
	int blockImage;  // �摜 �D�u���b�N
	int goalImage;	 // �摜 �S�[��(��)
	int wallImage;   // �摜 ���̕�
	int hBGImageI;    // �摜 �w�i1
	int hBGImageII;    // �摜 �w�i2
	int hBGImageIII;    // �摜 �w�i3

	int IsWallRight(VECTOR2 pos);
	int IsWallLeft(VECTOR2 pos);
	int IsWallDown(VECTOR2 pos);
	int IsWallUp(VECTOR2 pos);
	bool IsGoal(VECTOR2 pos);	//�S�[������

	Player* p;

	int scroll;		//��ʂ̃X�N���[��
	bool cellBG;	//�w�i�̃}�X�ڂ̕\��
};
