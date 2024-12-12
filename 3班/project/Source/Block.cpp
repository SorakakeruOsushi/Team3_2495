#include "Block.h"
#include "Stage.h"
#include "player.h"
#include <cassert>
#include <time.h>



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


// �����́AStageXtest.h���玝���Ă���
const int WIDTH = 24;		//�X�e�[�W ��
const int HEIGHT = 51;		//�X�e�[�W ��(�����ƍ����Ȃ�?)50�Ƃ�

struct BlockPos { // �u���b�N�̂���ꏊ���`
	int blockPos[3][3];
};

const BlockPos shapeL[] = {
	{{
		{2,0,0},
		{2,0,0},
		{2,2,0},
	}}, {{
		{2,2,2},
		{2,0,0},
		{0,0,0},
	}},{{
		{0,2,2},
		{0,0,2},
		{0,0,2},
	}}, {{
		{0,0,0},
		{0,0,2},
		{2,2,2},
	}}
};

const BlockPos shapeJ[] = {
	{{
		{0,0,3},
		{0,0,3},
		{0,3,3},
	}}, {{
		{0,0,0},
		{0,0,3},
		{3,3,3},
	}}, {{
		{3,0,0},
		{3,0,0},
		{3,3,0},
	}}, {{
		{3,3,3},
		{3,0,0},
		{0,0,0},
	}}
};

BlockPos shapeT[] = {
	{{
		{0,0,0},
		{0,4,0},
		{4,4,4},
	}}, {{
		{4,0,0},
		{4,4,0},
		{4,0,0},
	}}, {{
		{4,4,4},
		{0,4,0},
		{0,0,0},
	}}, {{
		{0,0,4},
		{0,4,4},
		{0,0,4},
	}}
};

BlockPos shapeO[] = {
	{{
		{5,5,0},
		{5,5,0},
		{0,0,0},
	}}, {{
		{5,5,0},
		{5,5,0},
		{0,0,0},
	}}, {{
		{5,5,0},
		{5,5,0},
		{0,0,0},
	}}, {{
		{5,5,0},
		{5,5,0},
		{0,0,0},
	}}
};

BlockPos GetBlockPos(Block::ShapeType type, int rot) {
	switch (type) {
	case Block::SHAPE_L:
		return shapeL[rot];
	case Block::SHAPE_J:
		return shapeJ[rot];
	case Block::SHAPE_T:
		return shapeT[rot];
	case Block::SHAPE_O:
		return shapeO[rot];
	}
}


Block::Block()
{

	s = FindGameObject<Stage>();

	isMovedLeft = false;
	isMovedRight = false;
	isTurn = false;

	position.x =WIDTH-5;
	position.y =0;

	blockSize = 30;

	timer = 1.3f;
	counter = 0.0f;
	quickCount = 17.0f;

	srand(time(NULL)); // ��������ƁA�N�����邽�тɗ������ς��悤�ɂȂ�

	nowBlock.shape = (ShapeType)(rand() % ShapeType::SHAPE_MAX);
	nowBlock.rotation = 0;
	nextBlock.shape = (ShapeType)(rand() % ShapeType::SHAPE_MAX);
	nextBlock.rotation = 0;
	for (int i = 0; i < ShapeType::SHAPE_MAX; i++) {
		hImage[i] = -1;
	}
	hImage[2] = LoadGraph("data/image/Lmino_One.png");
	hImage[3] = LoadGraph("data/image/Jmino_One.png");
	hImage[4] = LoadGraph("data/image/Tmino_One.png");
	hImage[5] = LoadGraph("data/image/Omino_One.png");

	pm = FindGameObject<PlayMode>();
	assert(pm != nullptr);

}

Block::~Block()
{
	for (int i = 0; i < ShapeType::SHAPE_MAX; i++) {
		if (hImage[i] > 0) {
			DeleteGraph(hImage[i]);
		}
	}
}



void Block::Update()
{
	/*if (finished || goaled)
	{
		return;
	}
	else*/ if (pm->playMode == 0)
	{
		return;
	}

	//�u���b�N�𗎂Ƃ�
	if (CheckHitKey(KEY_INPUT_S)) {
		counter += Time::DeltaTime() * quickCount;
		//S��������Ă�����quickCount�{����count���i�ށ�����������
	}
	else {
		counter += Time::DeltaTime();//������Ă��Ȃ���΂��̂܂�
	}
	if (counter >= timer) {
		if (position.y >= 20) { // �{���́A���ɂ���u���b�N�̏�ɏ������
			nowBlock = nextBlock;
			position.x = WIDTH-5;
			position.y = 0;
			nextBlock.shape = (ShapeType)(rand() % ShapeType::SHAPE_MAX);
			nextBlock.rotation = 0;
		}
		else {
			position.y++;
		}
		counter = 0.0f;
	}
	//���Ɉړ�
	if (CheckHitKey(KEY_INPUT_A)) {
		if (isMovedLeft == false) {
			position.x--;
			isMovedLeft = true;
		}
	}
	else {
		isMovedLeft = false;
	}
	//�E�Ɉړ�
	if (CheckHitKey(KEY_INPUT_D)) {
		if (isMovedRight == false) {
			position.x++;
			isMovedRight = true;
		}
	}
	else {
		isMovedRight = false;
	}
	// ��]
	if (CheckHitKey(KEY_INPUT_SPACE)) {
		if (not isTurn) {
			nowBlock.rotation = (nowBlock.rotation + 1) % 4; // �S��]�ň��
			isTurn = true; 
		}
	}
	else {
		isTurn = false;
	}
	

}

void Block::Draw()
{
	BlockPos block = GetBlockPos(nowBlock.shape, nowBlock.rotation);
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			int id = block.blockPos[y][x];
			if (id > 0) {
				DrawGraph((position.x + x) * blockSize, (position.y + y) * blockSize, hImage[id], TRUE);
			}
		}
	}

	block = GetBlockPos(nextBlock.shape, nextBlock.rotation);
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			int id = block.blockPos[y][x];
			if (id > 0) {
				DrawGraph(1065 + x * blockSize, 120 + y * blockSize, hImage[id], TRUE);
			}
		}
	}
}
