#include "Stage.h"
#include <cassert>
#include <sstream>
#include <fstream>
#include "Player.h"
#include "Block.h"


//�J�n���ɃX�e�[�W�������_���Ń��[�h������
//#include "stageXtest.h"
//#include "stage1.h"
const int WIDTH = 24;		//�X�e�[�W ��
const int HEIGHT = 51;		//�X�e�[�W ��(�����ƍ����Ȃ�?)50�Ƃ�

const int TOP_SPACE = -(CHIP_SIZE * (HEIGHT - 24)); 
const int SIDE_SPACE = CHIP_SIZE * 8; //���]��
const char* STAGE_DATA_PATH = "data/Stage/Stage%02d.csv";	//	�u���b�N�z�u���̃t�@�C����

int map[HEIGHT][WIDTH];

Stage::Stage()
{
#if false
	for (int y = 0; y < HEIGHT; y++) 
	{
		for (int x = 0; x < WIDTH; x++) 
		{
			map[y][x] = orgmap[y][x];
		}
	}
#endif

	//�����_����CSV�t�@�C����ǂݍ���ŃX�e�[�W��������I(�x�z�搶���肪�Ƃ��I)
	int stageNo = 0;
	stageNo = GetRand(9) + 1;

	char stageFile[100];
	sprintf_s(stageFile, STAGE_DATA_PATH, stageNo);

	// std::ifstream ifs(stageFile);		  //Stage(01�`10).CSV
	std::ifstream ifs("data/stage/Test.csv"); //�e�X�g.CSV

	std::string text;
	int y = 0;
	while (std::getline(ifs, text))
	{
		//  [,]�ŕ�������
		std::vector<std::string> element = split(text, ',');

		for (int x = 0; x < element.size(); x++)
		{
			int id = std::stoi(element[x]);
			map[y][x] = id;
		}
		y++;
	}
	ifs.close();

	
	// �摜 �~�m�摜
	MinoImage[2] = LoadGraph("data/image/Lmino_One.png");
	MinoImage[3] = LoadGraph("data/image/Jmino_One.png");
	MinoImage[4] = LoadGraph("data/image/Tmino_One.png");
	MinoImage[5] = LoadGraph("data/image/Omino_One.png");
	for (int i = 2; i < 6; i++) {
 		assert(MinoImage[i] > 0);
	}

	emptyImage = LoadGraph("data/image/EmptyA1.png");	   // �摜 ����ۃ}�X
		assert(emptyImage > 0);
	blockImage = LoadGraph("data/image/Ground.JPG");	   // �摜 ���u���b�N
		assert(blockImage > 0);
	goalImage = LoadGraph("data/image/GoalLineShort.png"); // �摜 ���u���b�N
		assert(goalImage > 0);
	wallImage = LoadGraph("data/image/WallA1Long.png");    // �摜 ��
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

