#include "Stage.h"
#include "Player.h"
#include <cassert>


const int CHIP_SIZE = 30;   //�`�b�v�T�C�Y
//�X�e�[�W
#include "stage1.h"


Stage::Stage()
{
	emptyImage = LoadGraph("data/image/EmptyA1.png");
		assert(emptyImage > 0);
	blockImage = LoadGraph("data/image/Block.png");
		assert(blockImage > 0);

	//9��T���āAPlayer��u��
	for (int j = 0; j < HEIGHT; j++)    //�uj�v�c
	{
		for (int i = 0; i < WIDTH; i++) //�ui�v��
		{
			if (map[j][i] == 9)//�v���C���[����
			{
				Player* p = Instantiate<Player>();
				p->position.x = CHIP_SIZE * i + CHIP_SIZE * 0;
				p->position.y = CHIP_SIZE * j + CHIP_SIZE * 0;
			}
		}
	}
	scroll = 0;
}

Stage::~Stage()
{
	DeleteGraph(emptyImage);
	DeleteGraph(blockImage);
}

void Stage::Draw()
{
	//�}�b�v�Z��(�}�X��)�Œ�\��
	//DrawGraph(CHIP_SIZE * 0, CHIP_SIZE * 0, cellBGImage, TRUE);

	//�}�b�v�^�C���\��
	for (int j = 0; j < HEIGHT; j++)// �c�uj�v
	{
		int y = j * CHIP_SIZE + (CHIP_SIZE * 0);
		for (int i = 0; i < WIDTH; i++)// ���ui�v
		{
			int x = i * CHIP_SIZE + (CHIP_SIZE * 0);

			if (map[j][i] == 0)		// ��b�^�C���uEmpty.png�v
			{
				DrawGraph(x, y - scroll, emptyImage, TRUE);
			}

			if (map[j][i] == 1)		// ��b�^�C���uBlock.png�v
			{
				DrawGraph(x, y - scroll, blockImage, TRUE);
			}
		}
	}
}

//�u���b�N�̓����蔻��
int Stage::IsWallRight(VECTOR2 pos)//pos�ɂ�player���W������
{
	//�u�}�b�v�`�b�v�����W�v�̋t�A�u���W���}�b�v�`�b�v�v
	int i = (pos.x - CHIP_SIZE * 0) / 30;
	int j = (pos.y - CHIP_SIZE * 0) / 30;
	if (map[j][i] == 1)
	{
		//�߂荞�񂾕������Ԃ�
		//��(int)����������int�Ƃ��Ĉ���
		int push = ((int)pos.x - CHIP_SIZE * 0) % 30 + 1;//0�Ȃ�1 1�Ȃ�2
		return push;
	}
	return 0;
}
int Stage::IsWallLeft(VECTOR2 pos)
{
	//�u�}�b�v�`�b�v�����W�v�̋t�A�u���W���}�b�v�`�b�v�v
	int i = (pos.x - CHIP_SIZE * 0) / 30;
	int j = (pos.y - CHIP_SIZE * 0) / 30;
	if (map[j][i] == 1)
	{
		//�߂荞�񂾕������Ԃ�
		//��(int)����������int�Ƃ��Ĉ���
		int push = 30 - ((int)pos.x - CHIP_SIZE * 0) % 30;//29�Ȃ�1 28�Ȃ�2
		return push;
	}
	return 0;
}
int Stage::IsWallDown(VECTOR2 pos)
{
	//�u�}�b�v�`�b�v�����W�v�̋t�A�u���W���}�b�v�`�b�v�v
	int i = (pos.x - CHIP_SIZE * 0) / 30;
	int j = (pos.y - CHIP_SIZE * 0) / 30;
	if (map[j][i] == 1)
	{
		//�߂荞�񂾕������Ԃ�
		//��(int)����������int�Ƃ��Ĉ���
		int push = ((int)pos.y - CHIP_SIZE * 0) % 30 + 1;
		return push;
	}
	return 0;
}
int Stage::IsWallUp(VECTOR2 pos)
{
	//�u�}�b�v�`�b�v�����W�v�̋t�A�u���W���}�b�v�`�b�v�v
	int i = (pos.x - CHIP_SIZE * 0) / 30;
	int j = (pos.y - CHIP_SIZE * 0) / 30;
	if (map[j][i] == 1)
	{
		//�߂荞�񂾕������Ԃ�
		//��(int)����������int�Ƃ��Ĉ���
		int push = 30 - ((int)pos.y - CHIP_SIZE * 0) % 30;//29�Ȃ�1 28�Ȃ�2
		return push;
	}
	return 0;
}
