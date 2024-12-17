#include "Stage.h"
#include <cassert>
#include "Player.h"
#include "Block.h"


//�J�n���ɃX�e�[�W�������_���Ń��[�h������
#include "stageXtest.h"
//#include "stage1.h"

const int TOP_SPACE = -(CHIP_SIZE * (HEIGHT - 24)); 
const int SIDE_SPACE = CHIP_SIZE * 8; //���]��

int map[HEIGHT][WIDTH];

Stage::Stage()
{
	for (int y = 0; y < HEIGHT; y++) 
	{
		for (int x = 0; x < WIDTH; x++) 
		{
			map[y][x] = orgmap[y][x];
		}
	}
	
	// �摜 �~�m�摜
	MinoImage[2] = LoadGraph("data/image/Lmino_One.png");
	MinoImage[3] = LoadGraph("data/image/Jmino_One.png");
	MinoImage[4] = LoadGraph("data/image/Tmino_One.png");
	MinoImage[5] = LoadGraph("data/image/Omino_One.png");
	for (int i = 2; i < 6; i++) {
 		assert(MinoImage[i] > 0);
	}

	emptyImage = LoadGraph("data/image/EmptyA1.png");
		assert(emptyImage > 0);
	blockImage = LoadGraph("data/image/BlockA2.png");
		assert(blockImage > 0);
	goalImage = LoadGraph("data/image/GoalLineShort.png");
		assert(goalImage > 0);
	wallImage = LoadGraph("data/image/WallA1Long.png");
		assert(wallImage > 0);

	//9��T���āAPlayer��u��
	for (int j = 0; j < HEIGHT; j++)    //�uj�v�c
	{
		for (int i = 0; i < WIDTH; i++) //�ui�v��
		{
			if (map[j][i] == 9) //�v���C���[����
			{
				p = Instantiate<Player>();
				p->position.x = CHIP_SIZE * i + SIDE_SPACE;
				p->position.y = CHIP_SIZE * j + TOP_SPACE;
			}
			if (map[j][i] == 7) //�R�C������
			{
				c = Instantiate<Coin>();
				c->position.x = CHIP_SIZE * i + SIDE_SPACE;
				c->position.y = CHIP_SIZE * j + TOP_SPACE;
			}
		}
	}
	scroll = 0;
	cellBG = true;

	
	b = FindGameObject<Block>();
}

Stage::~Stage()
{
	DeleteGraph(emptyImage);
	DeleteGraph(blockImage);
	DeleteGraph(goalImage);
	DeleteGraph(wallImage);
}

void Stage::Draw()
{
	//�Ǖ\��(��)
	DrawGraph(30*7, 0,  wallImage, TRUE);
	DrawGraph(30*7 + 30*25, 0,wallImage, TRUE);

	//�}�b�v�^�C���\��
	for (int j = 0; j < HEIGHT; j++)	// �c�uj�v
	{
		int y = j * CHIP_SIZE + TOP_SPACE;
		for (int i = 0; i < WIDTH; i++) // ���ui�v
		{
			int x = i * CHIP_SIZE + SIDE_SPACE;

			if (cellBG)
			{
				if (map[j][i] == 0)	// �}�X�ځuEmptyA1.png�v
				{
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 30);
					//�l�p��\��(����,�E���A�F(R,G,B)�A�h��Ԃ�)
					DrawGraph(x, y - scroll, emptyImage, TRUE);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //���߂��Ȃ�
				}
			}

			/*
			if (map[j][i] == 1)		
			{
				DrawGraph(x, y - scroll, blockImage, TRUE);
			}
			if (map[j][i] == 8)	
			*/

			int chip = map[j][i];
			if (chip == 1)		     // �O���[�u���b�N�uBlockA3.png�v
			{
				DrawGraph(x, y - scroll, blockImage, TRUE);
			}
			else if (chip >= 2 && chip < 6) {
				DrawGraph(x, y - scroll, MinoImage[chip], TRUE);
			}
			else if (map[j][i] == 8) // �S�[���uGoalLineShort.png�v

			{
				DrawGraph(x, y - scroll, goalImage, TRUE);
			}
		}
	}
}

//########################################################
// �g����������Ȃ�
//if (map[j][i] == 1)
//if ( (map[j][i] == 1)|| (map[j][i] == 2) || (map[j][i] == 3) || (map[j][i] == 4) || (map[j][i] == 5) )

//�u���b�N�̓����蔻��
int Stage::IsWallRight(VECTOR2 pos)//pos�ɂ�player���W������
{
	//�u�}�b�v�`�b�v�����W�v�̋t�A�u���W���}�b�v�`�b�v�v
	int i = (pos.x - SIDE_SPACE) / CHIP_SIZE;
	int j = (pos.y - TOP_SPACE)  / CHIP_SIZE;
	for (int x = 1; x < 6; x++) {
		if (map[j][i] == x)
		{
			//�߂荞�񂾕������Ԃ�
			//��(int)����������int�Ƃ��Ĉ���
			int push = ((int)pos.x - SIDE_SPACE) % CHIP_SIZE + 1;//0�Ȃ�1 1�Ȃ�2
			return push;
		}
	}
	return 0;
}
int Stage::IsWallLeft(VECTOR2 pos)
{
	//�u�}�b�v�`�b�v�����W�v�̋t�A�u���W���}�b�v�`�b�v�v
	int i = (pos.x - SIDE_SPACE) / CHIP_SIZE;
	int j = (pos.y - TOP_SPACE)  / CHIP_SIZE;
	for (int x = 1; x < 6; x++) {
		if (map[j][i] == x)
		{
			//�߂荞�񂾕������Ԃ�
			//��(int)����������int�Ƃ��Ĉ���
			int push = CHIP_SIZE - ((int)pos.x - SIDE_SPACE) % CHIP_SIZE;//29�Ȃ�1 28�Ȃ�2
			return push;
		}
	}
	return 0;
}
int Stage::IsWallDown(VECTOR2 pos)
{
	//�u�}�b�v�`�b�v�����W�v�̋t�A�u���W���}�b�v�`�b�v�v
	int i = (pos.x - SIDE_SPACE) / CHIP_SIZE;
	int j = (pos.y - TOP_SPACE)  / CHIP_SIZE;
	for (int x = 1; x < 6; x++) {
		if (map[j][i] == x)
		{
			//�߂荞�񂾕������Ԃ�
			//��(int)����������int�Ƃ��Ĉ���
			int push = ((int)pos.y - TOP_SPACE) % CHIP_SIZE + 1;
			return push;
		}
	}
	return 0;
}
int Stage::IsWallUp(VECTOR2 pos)
{
	//�u�}�b�v�`�b�v�����W�v�̋t�A�u���W���}�b�v�`�b�v�v
	int i = (pos.x - SIDE_SPACE) / CHIP_SIZE;
	int j = (pos.y - TOP_SPACE)  / CHIP_SIZE;
	for (int x = 1; x < 6; x++) {
		if (map[j][i] == x)
		{
			//�߂荞�񂾕������Ԃ�
			//��(int)����������int�Ƃ��Ĉ���
			int push = CHIP_SIZE - ((int)pos.y - TOP_SPACE) % CHIP_SIZE;//29�Ȃ�1 28�Ȃ�2
			return push;
		}
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