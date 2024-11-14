#include "Stage.h"
#include "Player.h"
#include <cassert>

const int WIDTH = 24;		//�X�e�[�W ��
const int HEIGHT = 24;		//�X�e�[�W ��
const int CHIP_SIZE = 30;   //�`�b�v�T�C�Y
int map[HEIGHT][WIDTH];

Stage::Stage()
{
	emptyImage = LoadGraph("data/image/Empty.png");
		assert(emptyImage > 0);
	blockImage = LoadGraph("data/image/Block.png");
		assert(blockImage > 0);
}

Stage::~Stage()
{
	DeleteGraph(emptyImage);
	DeleteGraph(blockImage);
}

void Stage::Draw()
{
	//�}�b�v�^�C���\��
	for (int j = 0; j < HEIGHT; j++)// �c�uj�v
	{
		int y = j * CHIP_SIZE + (CHIP_SIZE*0);
		for (int i = 0; i < WIDTH; i++)// ���ui�v
		{
			int x = i * CHIP_SIZE + (CHIP_SIZE*0);

			// ��}�X�uEmpty.png�v��`��
			DrawGraph(x, y, emptyImage, TRUE);
		}
	}
}