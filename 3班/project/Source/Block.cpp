#include "Block.h"
#include "Stage.h"
#include "player.h"
#include <cassert>


//��鎖
//���ړ��i�������Ƃ������j����]�������蔻�聨�����_�������iNEXT���݁j

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
	isMovedLeft = false;
	isMovedRight = false;
	
	position.x = 0;
	position.y = 0;

	blockSize = 30;

	time = 1.3f;
	counter = 0.0f;
	quickCount = 17.0f;

	for (int i = 0; i < 10; i++) {
		rand();//�����\�̏����l10���̂Ă�(��胉���_���ɂ��邽��)
	}

	// �����_���ȃ~�m���I�΂��
	switch (rand() % 4) {
	case 0:
		hImage = LoadGraph("data/image/Tmino_30.png");
		assert(hImage > 0);
		break;
	case 1:
		hImage = LoadGraph("data/image/Jmino_30.png");
		assert(hImage > 0);
		break;
	case 2:
		hImage = LoadGraph("data/image/Lmino_30.png");
		assert(hImage > 0);
		break;
	case 3:
		hImage = LoadGraph("data/image/Omino_30.png");
		assert(hImage > 0);
		break;
	} 
}

Block::~Block()
{
	DeleteGraph(hImage);
}



void Block::Update()
{
	//�u���b�N�𗎂Ƃ�
	if (CheckHitKey(KEY_INPUT_S)) {
		 counter += Time::DeltaTime()*quickCount;
		//S��������Ă�����quickCount�{����count���i�ށ�����������
	}
	else {
		counter += Time::DeltaTime();//������Ă��Ȃ���΂��̂܂�
	}
	if (counter >= time) {
		position.y += blockSize;
		counter = 0.0f;
	}
	//���Ɉړ�
	if (CheckHitKey(KEY_INPUT_A)) {
		if (isMovedLeft == false) {
			position.x -= blockSize;
			isMovedLeft = true;
		}
	}
	else {
		isMovedLeft = false;
	}
	//�E�Ɉړ�
	if (CheckHitKey(KEY_INPUT_D)) {
		if (isMovedRight == false) {
			position.x += blockSize;
			isMovedRight = true;
		}
	}
	else {
		isMovedRight = false;
	}

}

void Block::Draw()
{
	DrawGraph(position.x, position.y, hImage, TRUE);
}
