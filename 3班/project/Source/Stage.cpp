#include "Stage.h"
#include <cassert>
#include "Player.h"

//�X�e�[�W
#include "stageXtest.h"
//#include "stage1.h"

const int TOP_SPACE = -(CHIP_SIZE * (HEIGHT - 24)); 
const int SIDE_SPACE = CHIP_SIZE * 8; //���]��

Stage::Stage()
{
	emptyImage = LoadGraph("data/image/EmptyA1.png");
		assert(emptyImage > 0);
	blockImage = LoadGraph("data/image/Block.png");
		assert(blockImage > 0);
	goalImage = LoadGraph("data/image/Xgoal.png");
		assert(goalImage > 0);
	wallImage = LoadGraph("data/image/SideWall.png");
		assert(wallImage > 0);
	// �w�i�摜
	stageBGImage = LoadGraph("data/image/X/XmodeBGtetra.png");
		assert(stageBGImage > 0);
	hBGImageI = LoadGraph("data/image/Back1.JPG");
		assert(hBGImageI > 0);
	hBGImageII = LoadGraph("data/image/Back2.JPG");
		assert(hBGImageII > 0);
	hBGImageIII = LoadGraph("data/image/Back3.JPG");
		assert(hBGImageIII > 0);


	//9��T���āAPlayer��u��
	for (int j = 0; j < HEIGHT; j++)    //�uj�v�c
	{
		for (int i = 0; i < WIDTH; i++) //�ui�v��
		{
			if (map[j][i] == 9)//�v���C���[����
			{
				p = Instantiate<Player>();
				p->position.x = CHIP_SIZE * i + SIDE_SPACE;
				p->position.y = CHIP_SIZE * j + TOP_SPACE;
			}
		}
	}
	scroll = 0;
	cellBG = true;
}

Stage::~Stage()
{
	DeleteGraph(emptyImage);
	DeleteGraph(blockImage);
	DeleteGraph(goalImage);
	DeleteGraph(wallImage);

	DeleteGraph(stageBGImage);
	DeleteGraph(hBGImageI);
	DeleteGraph(hBGImageII);
	DeleteGraph(hBGImageIII);
}

void Stage::Draw()
{
	//��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 60);
	DrawGraph(30*8, -(Screen::HEIGHT * 0), stageBGImage, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	/*
	// �w�i�摜�\��(�{���͘A��png��z��ł�肽��)
	DrawGraph(0, -(Screen::HEIGHT * 0) - scroll, hBGImageI, TRUE);   //������P�Ԗ�
	DrawGraph(0, -(Screen::HEIGHT * 1) - scroll, hBGImageII, TRUE);  //������Q�Ԗ�
	DrawGraph(0, -(Screen::HEIGHT * 2) - scroll, hBGImageIII, TRUE);   //������R�Ԗ�
	*/

	//�Ǖ\��(��)
	DrawGraph(30*7, 0,  wallImage, TRUE);
	DrawGraph(30*7 + 30*25, 0,wallImage, TRUE);

	//�}�b�v�^�C���\��
	for (int j = 0; j < HEIGHT; j++)// �c�uj�v
	{
		int y = j * CHIP_SIZE + TOP_SPACE;
		for (int i = 0; i < WIDTH; i++)// ���ui�v
		{
			int x = i * CHIP_SIZE + SIDE_SPACE;

			if (cellBG)
			{
				if (map[j][i] == 0)		// �}�X�ځuEmpty.png�v
				{
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 30);
					//�l�p��\��(����,�E���A�F(R,G,B)�A�h��Ԃ�)
					DrawGraph(x, y - scroll, emptyImage, TRUE);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //���߂��Ȃ�
				}
			}

			if (map[j][i] == 1)		// �O���[�u���b�N�uBlock.png�v
			{
				DrawGraph(x, y - scroll, blockImage, TRUE);
			}
			if (map[j][i] == 8)		// �S�[���uXgoal.png�v
			{
				DrawGraph(x, y - scroll, goalImage, TRUE);
			}
		}
	}
}

//�u���b�N�̓����蔻��
int Stage::IsWallRight(VECTOR2 pos)//pos�ɂ�player���W������
{
	//�u�}�b�v�`�b�v�����W�v�̋t�A�u���W���}�b�v�`�b�v�v
	int i = (pos.x - SIDE_SPACE) / CHIP_SIZE;
	int j = (pos.y - TOP_SPACE)  / CHIP_SIZE;
	if (map[j][i] == 1)
	{
		//�߂荞�񂾕������Ԃ�
		//��(int)����������int�Ƃ��Ĉ���
		int push = ((int)pos.x - SIDE_SPACE) % CHIP_SIZE + 1;//0�Ȃ�1 1�Ȃ�2
		return push;
	}
	return 0;
}
int Stage::IsWallLeft(VECTOR2 pos)
{
	//�u�}�b�v�`�b�v�����W�v�̋t�A�u���W���}�b�v�`�b�v�v
	int i = (pos.x - SIDE_SPACE) / CHIP_SIZE;
	int j = (pos.y - TOP_SPACE)  / CHIP_SIZE;
	if (map[j][i] == 1)
	{
		//�߂荞�񂾕������Ԃ�
		//��(int)����������int�Ƃ��Ĉ���
		int push = CHIP_SIZE - ((int)pos.x - SIDE_SPACE) % CHIP_SIZE;//29�Ȃ�1 28�Ȃ�2
		return push;
	}
	return 0;
}
int Stage::IsWallDown(VECTOR2 pos)
{
	//�u�}�b�v�`�b�v�����W�v�̋t�A�u���W���}�b�v�`�b�v�v
	int i = (pos.x - SIDE_SPACE) / CHIP_SIZE;
	int j = (pos.y - TOP_SPACE)  / CHIP_SIZE;
	if (map[j][i] == 1)
	{
		//�߂荞�񂾕������Ԃ�
		//��(int)����������int�Ƃ��Ĉ���
		int push = ((int)pos.y - TOP_SPACE) % CHIP_SIZE + 1;
		return push;
	}
	return 0;
}
int Stage::IsWallUp(VECTOR2 pos)
{
	//�u�}�b�v�`�b�v�����W�v�̋t�A�u���W���}�b�v�`�b�v�v
	int i = (pos.x - SIDE_SPACE) / CHIP_SIZE;
	int j = (pos.y - TOP_SPACE)  / CHIP_SIZE;
	if (map[j][i] == 1)
	{
		//�߂荞�񂾕������Ԃ�
		//��(int)����������int�Ƃ��Ĉ���
		int push = CHIP_SIZE - ((int)pos.y - TOP_SPACE) % CHIP_SIZE;//29�Ȃ�1 28�Ȃ�2
		return push;
	}
	return 0;
}

bool Stage::IsGoal(VECTOR2 pos)
{
	//�u�}�b�v�`�b�v�����W�v�̋t�A�u���W���}�b�v�`�b�v�v
	int i = (pos.x - SIDE_SPACE) / CHIP_SIZE;
	int j = (pos.y - TOP_SPACE)  / CHIP_SIZE;
	if (map[j][i] == 8)
	{
		return true;
	}
	return false;
}