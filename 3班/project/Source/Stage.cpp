#include "Stage.h"
#include <cassert>
#include <sstream>
#include <fstream>
#include "Player.h"
#include "Block.h"
#include "csvReader.h"

const int WIDTH = 24;		//�X�e�[�W ��
const int HEIGHT = 51;		//�X�e�[�W ��

int map[HEIGHT][WIDTH];

const int TOP_SPACE = -(CHIP_SIZE * (HEIGHT - 24));
const int SIDE_SPACE = CHIP_SIZE * 8;	//���]��
const char* STAGE_DATA_PATH = "data/Stage/Stage%02d.csv";	// �u���b�N�z�u���̃t�@�C����

Stage::Stage()
{
	//�����_����CSV�t�@�C����ǂݍ���ŃX�e�[�W��������I(�x�z�搶���肪�Ƃ��I)
	int stageNo = 0;
	stageNo = GetRand(8) + 1; // ���� [01�`05]�̃����_��

	char stageFile[100];
	sprintf_s(stageFile, STAGE_DATA_PATH, stageNo);


	CsvReader* csv = new CsvReader(stageFile);			    //Stage(01�`05).CSV�������_���\��
	//CsvReader* csv = new CsvReader("data/stage/Test.csv"); //���܂���CSV�t�@�C����\��

	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			map[y][x] = csv->GetInt(y, x);
		}
	}
	delete csv;

	// �摜 �~�m�摜
	MinoImage[2] = LoadGraph("data/image/Lmino_One.PNG");
	MinoImage[3] = LoadGraph("data/image/Jmino_One.PNG");
	MinoImage[4] = LoadGraph("data/image/Tmino_One.PNG");
	MinoImage[5] = LoadGraph("data/image/Omino_One.PNG");
	for (int i = 2; i < 6; i++)
	{
		assert(MinoImage[i] > 0);
	}

	groundImage = LoadGraph("data/image/Ground.JPG");	   // �摜 ���u���b�N
	assert(groundImage > 0);
	blockImage = LoadGraph("data/image/BlockA2.png");	   // �摜 �����u���b�N
	assert(blockImage > 0);
	goalImage = LoadGraph("data/image/GoalLineShort.png"); // �摜 �S�[�����C��
	assert(goalImage > 0);
	wallImage = LoadGraph("data/image/pole.JPG");    // �摜 ��
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
	pm = FindGameObject<PlayMode>();
}

Stage::~Stage()
{
	DeleteGraph(groundImage);
	DeleteGraph(blockImage);
	DeleteGraph(goalImage);
	DeleteGraph(wallImage);

	DeleteGraph(MinoImage[2]);
	DeleteGraph(MinoImage[3]);
	DeleteGraph(MinoImage[4]);
	DeleteGraph(MinoImage[5]);
}

void Stage::Draw()
{
	//�Ǖ\��(��)
	DrawGraph(30 * 7          , -1440 - scroll, wallImage, TRUE);
	DrawGraph(30 * 7 + 30 * 25, -1440 - scroll, wallImage, TRUE);

	//�}�b�v�^�C���\��
	for (int j = 0; j < HEIGHT; j++)	// �c�uj�v
	{
		int y = j * CHIP_SIZE + TOP_SPACE;
		for (int i = 0; i < WIDTH; i++) // ���ui�v
		{
			int x = i * CHIP_SIZE + SIDE_SPACE;

			int chip = map[j][i];
			if (chip == 1)		     // �n�ʃu���b�N
			{
				DrawGraph(x, y - scroll, groundImage, TRUE);
			}
			if (chip == 6)		     // �����u���b�N
			{
				DrawGraph(x, y - scroll, blockImage, TRUE);
			}
			else if (chip >= 2 && chip < 6)
			{
				DrawGraph(x, y - scroll, MinoImage[chip], TRUE);
			}
			else if (chip == 8) // �S�[�����C��
			{
				DrawGraph(x, y - scroll, goalImage, TRUE);
			}
		}
	}
}

//�u���b�N�̓����蔻��
int Stage::IsWallRight(VECTOR2 pos) // pos�ɂ�Player���W������
{
	int i = (pos.x - SIDE_SPACE) / CHIP_SIZE;
	int j = (pos.y - TOP_SPACE) / CHIP_SIZE;
	for (int x = 1; x < 7; x++) // [1�`6]
	{
		if (map[j][i] == x)
		{
			//�߂荞�񂾕������Ԃ�
			//��(int)����������int�Ƃ��Ĉ���
			int push = ((int)pos.x - SIDE_SPACE) % CHIP_SIZE + 1; //0�Ȃ�1 1�Ȃ�2
			return push;
		}
	}
	return 0;
}
int Stage::IsWallLeft(VECTOR2 pos)
{
	int i = (pos.x - SIDE_SPACE) / CHIP_SIZE;
	int j = (pos.y - TOP_SPACE) / CHIP_SIZE;
	for (int x = 1; x < 7; x++) // [1�`6]
	{
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
	int i = (pos.x - SIDE_SPACE) / CHIP_SIZE;
	int j = (pos.y - TOP_SPACE) / CHIP_SIZE;
	for (int x = 1; x < 7; x++) // [1�`6]
	{
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
	int i = (pos.x - SIDE_SPACE) / CHIP_SIZE;
	int j = (pos.y - TOP_SPACE) / CHIP_SIZE;
	for (int x = 1; x < 7; x++) // [1�`6]
	{
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
	int j = (pos.y - TOP_SPACE) / CHIP_SIZE;
	if (map[j][i] == 8)
	{
		return true;
	}
	return false;
}

void Stage::PutBlock(int x, int y, int id)
{
	y = y - (TOP_SPACE - scroll) / CHIP_SIZE;
	x = x - (SIDE_SPACE / CHIP_SIZE);
	map[y][x] = id;

}

bool Stage::CheckBlock(int x, int y)//�����Ƀ}�b�v�`�b�v�����邩
{
	//�u�}�b�v�`�b�v�����W�v�̋t�A�u���W���}�b�v�`�b�v�v
	y = y - (TOP_SPACE - scroll) / CHIP_SIZE;
	if (y < 0) {
		return false;
	}
	x = x - (SIDE_SPACE / CHIP_SIZE);
	int id = map[y][x];
	if (map[y][x] >= 1 && map[y][x] < 7) // [1�ȏ� ���� 7����]
	{
		return true;

	}
	else { return false; }
}

bool Stage::CheckOnGoal(int x, int y)
{
	y = y - (TOP_SPACE - scroll) / CHIP_SIZE;
	x = x - (SIDE_SPACE / CHIP_SIZE);
	int id = map[y][x];
	if (map[y][x] ==8) // [8=�S�[���̎�]
	{
		return true;

	}
	else { return false; }
}

// ��؂蕶�����w�肵�ĕ�����𕪊�����
std::vector<std::string> Stage::split(const std::string& text, char delim)
{
	std::vector<std::string>elements;
	std::stringstream ss(text);
	std::string item;
	while (getline(ss, item, delim))
	{
		if (!item.empty())
		{
			elements.push_back(item);
		}
	}
	return elements;
}

