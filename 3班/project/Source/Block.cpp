#include "Block.h"
#include "Stage.h"
#include "player.h"
#include <cassert>

//�e�g���X��낤�Ǝv�������Ǎs���l������(�ꉞ�c���Ēu���Ă����܂����A�C�ɂ����ǂ���)
// �Q�l����u�e�g���X�����ꎞ�Ԃō���Ă݂��U�yC����Q�[���v���O���~���O�����zProgramming Tetris�v
// h ttps://youtu.be/BJs29RicyPw?si=-gs57ir-W4lnC66g
/*
//�uShape:�`�v

//�f�[�^�̑傫��
#define SHAPE_WIDTH_MAX (4)
#define SHAPE_HEIGHT_MAX (4)

//�񋓌^enum
enum {
	SHAPE_I,
	SHAPE_O,
	SHAPE_S,
	SHAPE_Z,
	SHAPE_J,
	SHAPE_L,
	SHAPE_T,
	SHAPE_MAX
};

//SHAPE�\���̐錾
//�`��̍\����
typedef struct 
{
	int width, height;							    //���ƍ���
	int pattern[SHAPE_WIDTH_MAX][SHAPE_HEIGHT_MAX]; //�p�^�[���̐�
}SHAPE; // SHAPE�^�Ƃ���(?)

//�e�g���~�m�̍\����
typedef struct
{
	int  x, y;   // ���W�f�[�^
	SHAPE shape; // �`��f�[�^
}MINO; // MINO�^�Ƃ���(?)


//SHAPE�̎���
//�\���̂̒��g��ݒ�
SHAPE shapes[SHAPE_MAX] = {
	// SHAPE_I
	{
		//int width, height; //���ƍ���
		4,4,
		{
		//int pattern[SHAPE_WIDTH_MAX][SHAPE_HEIGHT_MAX]; //�p�^�[���̐�
			{0,0,0,0},
			{1,1,1,1},
			{0,0,0,0},
			{0,0,0,0}
		}
	},
	// SHAPE_O
	{
		//int width, height; //���ƍ���
		2,2,
		{
		//int pattern[SHAPE_WIDTH_MAX][SHAPE_HEIGHT_MAX]; //�p�^�[���̐�
			{1,1},
			{1,1}
		}
	},
	// SHAPE_S
	{
		//int width, height; //���ƍ���
		3,3,
		{
		//int pattern[SHAPE_WIDTH_MAX][SHAPE_HEIGHT_MAX]; //�p�^�[���̐�
			{0,1,1},
			{1,1,0},
			{0,0,0}
		}
	},
	// SHAPE_Z
	{
		//int width, height; //���ƍ���
		3,3,
		{
		//int pattern[SHAPE_WIDTH_MAX][SHAPE_HEIGHT_MAX]; //�p�^�[���̐�
			{1,1,0},
			{0,1,1},
			{0,0,0}
		}
	},
	// SHAPE_J
	{
		//int width, height; //���ƍ���
		3,3,
		{
		//int pattern[SHAPE_WIDTH_MAX][SHAPE_HEIGHT_MAX]; //�p�^�[���̐�
			{1,0,0},
			{1,1,1},
			{0,0,0}
		}
	},
	// SHAPE_L
	{
		//int width, height; //���ƍ���
		3,3,
		{
		//int pattern[SHAPE_WIDTH_MAX][SHAPE_HEIGHT_MAX]; //�p�^�[���̐�
			{0,0,1},
			{1,1,1},
			{0,0,0}
		}
	},
	// SHAPE_T
	{
		//int width, height; //���ƍ���
		3,3,
		{
		//int pattern[SHAPE_WIDTH_MAX][SHAPE_HEIGHT_MAX]; //�p�^�[���̐�
			{0,1,0},
			{1,1,1},
			{0,0,0}
		}
	},
};

//Stage�̓��e?
//int map[WIDTH][HEIGHT];
//int screen[WIDTH][HEIGHT];//����Ƀ}�b�v�ƃ~�m����������
//MINO mino;
////////////////////////////////////////////////////*/


Block::Block()
{
	hImage = LoadGraph("data/image/Tmino_30.png");
	assert(hImage > 0);

	position.x = 0;
	position.y = 0;

	blockSize = 30;

	time = 1.5f;
	counter = 0.0f;

	//mino.shape = shapes[rand() % SHAPE_MAX]; // �����_���ȃ~�m���I�΂��
}

Block::~Block()
{
	DeleteGraph(hImage);
}



void Block::Update()
{
	//�u���b�N�𗎂Ƃ�
	counter += Time::DeltaTime();
	if (counter >= time) {
		position.y += blockSize;
		counter = 0.0f;
	}

}

void Block::Draw()
{
	DrawGraph(position.x, position.y, hImage, TRUE);
}
