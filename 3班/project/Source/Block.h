#pragma once
#include "../Library/GameObject.h"
#include "Vector2.h"
#include "PlayMode.h"


class Block :
	public GameObject
{
public:
	Block();
	~Block();
	void Update() override;
	void Draw() override;


	int hImage[6]; // �摜�͑S�Ď����Ă���
	struct IVECTOR2 {
		int x;
		int y;
	};
	IVECTOR2 position; // ���W�́A�u���b�N�̃}�X�Ŏ����Ă���

	int blockSize; // �u���b�N�T�C�Y��int��

	enum ShapeType {
		SHAPE_L,
		SHAPE_J,
		SHAPE_T,
		SHAPE_O,
		SHAPE_MAX
	};
	struct BlockSet {
		ShapeType shape;  // �u���b�N�̌`
		int rotation; // �u���b�N�̉�]
	};
	BlockSet nextBlock; // next�̃u���b�N
	BlockSet nowBlock;  // ���̃u���b�N

	float timer; // time�Ƃ������O�͎g���Ă���̂ŁAtimer�ɂ��܂���
	float counter;
	float quickCount;//S�������Ă��鎞��counter�𑝂₷�{��
	float pressTimerLeft;//���������̎���
	float pressTimerRight;//�E�������̎���

	bool isMovedLeft;//�E�Ɉړ�������
	bool isMovedRight;//���Ɉړ�������
	bool isTurn;//��]������

	//bool isLongPressLeft;//���̒�����
	//bool isLongPressRight;//�E�̒�����

	PlayMode* pm;
};

