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
		{3,0,0},
		{3,3,3},
	}}, {{
		{3,3,0},
		{3,0,0},
		{3,0,0},
	}}, {{
		{3,3,3},
		{0,0,3},
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
	sameMino = true;
	s = FindGameObject<Stage>();
	assert(s != nullptr);
	p = FindGameObject<Player>();
	assert(p != nullptr);

	TurnSound=LoadSoundMem("data/sound/GameSE/�u���b�N��]�P.mp3");//��]��
	assert(TurnSound > 0);
	PutSound= LoadSoundMem("data/sound/GameSE/�u���b�N�ݒu�S.mp3");//�ݒu��
	assert(PutSound > 0);


	isMovedLeft = false;
	isMovedRight = false;
	isTurn = false;

	putBlock = false;

	position.x =WIDTH-5;
	position.y =0;

	blockSize = 30;

	timer = 1.3f;
	counter = 0.0f;
	quickCount = 17.0f;

	srand(time(NULL)); // ��������ƁA�N�����邽�тɗ������ς��悤�ɂȂ�

	nowBlock.shape = (ShapeType)(rand() % ShapeType::SHAPE_MAX);
	nowBlock.rotation = 0;
	while (sameMino) {
		nextBlock.shape = (ShapeType)(rand() % ShapeType::SHAPE_MAX);
		if (nextBlock.shape == nowBlock.shape) {//nowBlock��nextBlock�̌`�������Ƃ�
			sameMino = true;//�J��Ԃ�
		}
		else {
			sameMino = false;
		}
	}
	sameMino = true;
	nextBlock.rotation = 0;
	for (int i = 2; i < 6; i++) {
		hImage[i] = -1;
	}
	for (int i = 2; i < 6; i++) {
		NextImage[i] = -1;
	}
	hImage[2] = LoadGraph("data/image/Lmino.PNG");
	hImage[3] = LoadGraph("data/image/Jmino.PNG");
	hImage[4] = LoadGraph("data/image/Tmino.PNG");
	hImage[5] = LoadGraph("data/image/Omino.PNG");

	NextImage[2] = LoadGraph("data/image/Lmino_One.PNG");
	NextImage[3] = LoadGraph("data/image/Jmino_One.PNG");
	NextImage[4] = LoadGraph("data/image/Tmino_One.PNG");
	NextImage[5] = LoadGraph("data/image/Omino_One.PNG");

	pm = FindGameObject<PlayMode>();
	assert(pm != nullptr);
}

Block::~Block()
{
	for (int i = 2; i < 6; i++) {
		if (hImage[i] > 0) {
			DeleteGraph(hImage[i]);
		}
		if (NextImage[i] > 0) {
			DeleteGraph(NextImage[i]);
		}
	}
}


void Block::Update()
{
	if (!pm->IsGameStart)		 // �Q�[���J�n�O
	{
		return;
	}
	if (p->finished || p->goaled)// �Q�[���I��
	{
		return;
	}
	else if (pm->playMode == 0)	 // �e�g�����[�h
	{
		return;
	}

	//�p�b�h�p�֐�(���t���[���Ăяo��)
	GetJoypadXInputState(DX_INPUT_PAD1, &input);

	//�u���b�N�𗎂Ƃ�
	if (CheckHitKey(KEY_INPUT_S)||CheckHitKey(KEY_INPUT_DOWN)
		|| (input.Buttons[XINPUT_BUTTON_DPAD_LEFT])) {
		counter += Time::DeltaTime() * quickCount;
		//S��������Ă�����quickCount�{����count���i�ށ�����������
	}
	else {
		counter += Time::DeltaTime();//������Ă��Ȃ���΂��̂܂�
	}
	if (counter >= timer) {//�n�ʂɂ�����u��
		BlockPos block = GetBlockPos(nowBlock.shape, nowBlock.rotation);
		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {
				int id = block.blockPos[y][x];
				if (id > 0) {
					if (s->CheckBlock(position.x + x, (position.y + y) + 1)) { // �~�m�̉��ɏ�Q���������
						BlockPos block = GetBlockPos(nowBlock.shape, nowBlock.rotation);
						for (int y = 0; y < 3; y++) {
							for (int x = 0; x < 3; x++) {
								int id = block.blockPos[y][x];
								if (s->CheckOnGoal(position.x + x, position.y + y)) {//�S�[���ƃ~�m�����Ԃ��Ă��������
									nowBlock = nextBlock;
									position.x = WIDTH - 5;
									position.y = 0;
									while (sameMino) {
										nextBlock.shape = (ShapeType)(rand() % ShapeType::SHAPE_MAX);
										if (nextBlock.shape == nowBlock.shape) {//nowBlock��nextBlock�̌`�������Ƃ�
											sameMino = true;//�J��Ԃ�
										}
										else {
											sameMino = false;
										}
									}
									sameMino = true;
									nextBlock.rotation = 0;
									return;
								}
								else if(position.y+y < 4){//�ォ��l��ɐݒu�����~�m������
									nowBlock = nextBlock;
									position.x = WIDTH - 5;
									position.y = 0;
									while (sameMino) {
										nextBlock.shape = (ShapeType)(rand() % ShapeType::SHAPE_MAX);
										if (nextBlock.shape == nowBlock.shape) {//nowBlock��nextBlock�̌`�������Ƃ�
											sameMino = true;//�J��Ԃ�
										}
										else {
											sameMino = false;
										}
									}
									sameMino = true;
									nextBlock.rotation = 0;
									return;
								}
								else{
									if (id > 0) {
										s->PutBlock(position.x + x, position.y + y, id);//�~�m��z�u����
										PlaySoundMem(PutSound, DX_PLAYTYPE_BACK); // �ݒu���̍Đ�
									}
								}
							}
						}
						nowBlock = nextBlock;
						position.x = WIDTH - 5;
						position.y = 0;
						while (sameMino) {
							nextBlock.shape = (ShapeType)(rand() % ShapeType::SHAPE_MAX);
							if (nextBlock.shape == nowBlock.shape) {//nowBlock��nextBlock�̌`�������Ƃ�
								sameMino = true;//�J��Ԃ�
							}
							else {
								sameMino = false;
							}
						}
						sameMino = true;
							nextBlock.rotation = 0;
						return;
					}
				}
			}
		}
		if (position.y > 24) {//��ʊO��3�u���b�N���o���猻�݂̃u���b�N������
			nowBlock = nextBlock;
			position.x = WIDTH - 5;
			position.y = 0;
			while (sameMino) {
				nextBlock.shape = (ShapeType)(rand() % ShapeType::SHAPE_MAX);
				if (nextBlock.shape == nowBlock.shape) {//nowBlock��nextBlock�̌`�������Ƃ�
					sameMino = true;//�J��Ԃ�
				}
				else {
					sameMino = false;
				}
			}
			sameMino = true;
			nextBlock.rotation = 0;
			return;
		}
		
			position.y++;
		counter = 0.0f;
	}
	//���Ɉړ�(A�E���EPAD��)
	if (CheckHitKey(KEY_INPUT_A) || (CheckHitKey(KEY_INPUT_LEFT))
		|| (input.Buttons[XINPUT_BUTTON_DPAD_LEFT])) {
		if (isMovedLeft == false) {
			position.x--;
			isMovedLeft = true;
			pressTimerL = 20;//pressTimer��20F�ɐݒ�
		}
		pressTimerL--;
		if (pressTimerL <= 0 && isMovedLeft == true) {//pressTimer��0�ȉ�����������
			position.x--;
			pressTimerL = 3;//pressTimer��3F�ɐݒ�(3F���ɌJ��Ԃ�)
		}
		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {
				BlockPos block = GetBlockPos(nowBlock.shape, nowBlock.rotation);
				int id = block.blockPos[y][x];
				if (id > 0) {
					if (s->CheckBlock(position.x + x, position.y + y)) { 
						BlockPos block = GetBlockPos(nowBlock.shape, nowBlock.rotation);
						position.x += 1;
					}
				}
			}
		}
		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {
				BlockPos block = GetBlockPos(nowBlock.shape, nowBlock.rotation);
				int id = block.blockPos[y][x];
				if (id > 0) {
					if (position.x+x-1 <= WIDTH - 5 - 13) { // ���̕ǂɂ��Ԃ�����
						position.x +=1;
					}
				}
			}
		}
	}
	else {
		isMovedLeft = false;
	}
	//�E�Ɉړ�(D�E���EPAD��)
	if (CheckHitKey(KEY_INPUT_D) || (CheckHitKey(KEY_INPUT_RIGHT))
		|| (input.Buttons[XINPUT_BUTTON_DPAD_RIGHT])) {
		if (isMovedRight == false) {
			position.x++;
			isMovedRight = true;
			pressTimerR = 20;//pressTimer��20F�ɐݒ�
		}
		pressTimerR--;
		if (pressTimerR <= 0 && isMovedRight) {//pressTimer��0�ȉ�����������
			position.x++;
			pressTimerR = 3;//pressTimer��3F�ɐݒ�(3F���ɌJ��Ԃ�)
		}
		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {
				BlockPos block = GetBlockPos(nowBlock.shape, nowBlock.rotation);
				int id = block.blockPos[y][x];
				if (id > 0) {
					if (s->CheckBlock(position.x + x, position.y+y)) {
						BlockPos block = GetBlockPos(nowBlock.shape, nowBlock.rotation);
						position.x -= 1;
					}
				}
			}
		}
		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {
				BlockPos block = GetBlockPos(nowBlock.shape, nowBlock.rotation);
				int id = block.blockPos[y][x];
				if (id > 0) {
					if (position.x+x+1 >= WIDTH - 5 + 14) { // �E�̕ǂɂ��Ԃ�����
						BlockPos block = GetBlockPos(nowBlock.shape, nowBlock.rotation);
						position.x -=1;
					}
				}
			}
		}
	}
	else {
		isMovedRight = false;
	}
	// ��](�X�y�[�X�ARB�{�^��)
	if (CheckHitKey(KEY_INPUT_SPACE) ||
		input.Buttons[XINPUT_BUTTON_RIGHT_SHOULDER]) {
		if (not isTurn) {
			nowBlock.rotation = (nowBlock.rotation + 1) % 4; // �S��]�ň��
			PlaySoundMem(TurnSound, DX_PLAYTYPE_BACK); // ��]���̍Đ�
			isTurn = true;
			
		}
		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {
				BlockPos block = GetBlockPos(nowBlock.shape, nowBlock.rotation);
				int id = block.blockPos[y][x];
				if (id > 0) {
					if (s->CheckBlock(position.x + x, position.y + y)) { 
						BlockPos block = GetBlockPos(nowBlock.shape, nowBlock.rotation);
						position.y -= 1;
					}
				}
			}
		}
		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {
				BlockPos block = GetBlockPos(nowBlock.shape, nowBlock.rotation);
				int id = block.blockPos[y][x];
				if (id > 0) {
					if (id > 0) {
						if (position.x + x - 1 <= WIDTH - 5 - 13) { // ���̕ǂɂ��Ԃ�����
							position.x += 1;
						}
					}
				}
			}
		}
		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {
				BlockPos block = GetBlockPos(nowBlock.shape, nowBlock.rotation);
				int id = block.blockPos[y][x];
				if (id > 0) {
					if (position.x + x + 1 >= WIDTH - 5 + 14) { // �E�̕ǂɂ��Ԃ�����
						BlockPos block = GetBlockPos(nowBlock.shape, nowBlock.rotation);
						position.x -= 1;
					}
				}
			}
		}
	}
	//����](���E��Shift�ALB�{�^��)
	else if (CheckHitKey(KEY_INPUT_RSHIFT) || CheckHitKey(KEY_INPUT_LSHIFT)
		|| input.Buttons[XINPUT_BUTTON_LEFT_SHOULDER]) {
		if (not isTurn) {
			nowBlock.rotation -= 1;
			if (nowBlock.rotation <= -1) {
				nowBlock.rotation = 3;
			}
			PlaySoundMem(TurnSound, DX_PLAYTYPE_BACK); // �W�����v���̍Đ�
			isTurn = true;
		}
		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {
				BlockPos block = GetBlockPos(nowBlock.shape, nowBlock.rotation);
				int id = block.blockPos[y][x];
				if (id > 0) {
					if (s->CheckBlock(position.x + x, position.y + y)) { // �~�m�̉��ɏ�Q���������
						BlockPos block = GetBlockPos(nowBlock.shape, nowBlock.rotation);
						position.y -= 1;
					}
				}
			}
		}
		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {
				BlockPos block = GetBlockPos(nowBlock.shape, nowBlock.rotation);
				int id = block.blockPos[y][x];
				if (id > 0) {
					if (position.x + x - 1 <= WIDTH - 5 - 13) { // ���̕ǂɂ��Ԃ�����
						position.x += 1;
					}
				}
			}
		}
		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {
				BlockPos block = GetBlockPos(nowBlock.shape, nowBlock.rotation);
				int id = block.blockPos[y][x];
				if (id > 0) {
					if (position.x + x + 1 >= WIDTH - 5 + 14) { // �E�̕ǂɂ��Ԃ�����
						BlockPos block = GetBlockPos(nowBlock.shape, nowBlock.rotation);
						position.x -= 1;
					}
				}
			}
		}
	}
	else {
		isTurn = false;
	}

}

void Block::Draw()
{
	int Xmax = -9999999;
	int Xmin = 9999999;

	if (pm->playMode == 1)	 // �u���b�N�����͈͂̕\��
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
		DrawBox(240, 0, 960, 120, GetColor(255, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 256);
	}

	BlockPos block = GetBlockPos(nowBlock.shape, nowBlock.rotation);
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			int id = block.blockPos[y][x];
			if (id > 0) {
				if (position.x + x > Xmax) {//�~�m�̉E���̍��W�𓾂�
					Xmax = position.x + x;
				}
				if (position.x + x < Xmin) {//�����̍��W�𓾂�
					Xmin = position.x + x;
				}
			}
		}
	}
	if (pm->playMode == 1) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
		DrawBox(Xmin * blockSize, 0, (Xmax + 1) * blockSize, 690, GetColor(255, 255, 255), TRUE);//�u���b�N���͂ޘg�g�݂����
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 256);
	}
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			int id = block.blockPos[y][x];
			if (id > 0) {
				if (pm->playMode == 1) {
					DrawGraph((position.x + x) * blockSize, (position.y + y) * blockSize, hImage[id], TRUE);
				}
				else {
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
					DrawGraph((position.x + x) * blockSize, (position.y + y) * blockSize, hImage[id], TRUE);
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 256);
				}
			}
		}
	}



	block = GetBlockPos(nextBlock.shape, nextBlock.rotation);
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			int id = block.blockPos[y][x];
			if (id == 2 || id == 5) {
				DrawGraph(1115 + x * blockSize, 110 + y * blockSize, NextImage[id], TRUE);
			}
			else if (id == 4) {
				DrawGraph(1105 + x * blockSize, 95 + y * blockSize, NextImage[id], TRUE);
			}
			else if (id == 3) {
				DrawGraph(1090 + x * blockSize, 110 + y * blockSize, NextImage[id], TRUE);
			}
		}
	}
}

void Block::SetPosition(int x,int y)
{
			nowPosition.x =x;
			nowPosition.y =y;
}

