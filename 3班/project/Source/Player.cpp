#include "Player.h"
#include <cassert>
#include "Screen.h"
#include "GoalText.h"
#include "Stage.h"

const float Gravity = 0.2f;							 //�d��
const float JumpHight = 30 * 32.5f;						 //�W�����v�̍���
//			v0 = -  ��   2   *   g     *    S
const float V0 = -sqrtf(2.0f * Gravity * JumpHight); //������(�W�����v)�̎�

Player::Player()
{
	// Player�͏c�Qx���P�}�X�̑傫��
	hImage = LoadGraph("data/image/TETRAall.png");
		assert(hImage > 0);
	// Jump�T�E���h�f�[�^��ǂݍ��� 
	jumpSE = LoadSoundMem("data/sound/���ʉ����{/�W�����v.mp3");  // �v���C���[Jump�T�E���h
		assert(jumpSE > 0);

		//pm = Instantiate<PlayMode>();

	pm = FindGameObject<PlayMode>();
		assert(pm != nullptr);

	s = FindGameObject<Stage>();

	position.x = 0;
	position.y = 0;

	playerHeight = -10.0f; //�����̍���(10)������
	prePlayerY = 0;

	speed = 2.0f;

	//�v���C���[�̕��s�A�j���[�V�����֘A
	patternX = 0;
	patternY = 2;
	timer = 0;
	IsWalkLeft = false;
	IsWalkRight = false;
	//
	prevJumpKey = false;
	onGround = false;

	finished = false;
	goaled = false;

	velocity = 0.0f;

	gotCoin = 0;
}

Player::~Player()
{
	DeleteGraph(hImage);
	DeleteSoundMem(jumpSE);
}

void Player::Update()
{
	if (finished || goaled)
	{
		return;
	}
	else if (pm->playMode == 1)
	{
		return;
	}

	IsWalkLeft = false;
	IsWalkRight = false;

	// �v���C���[Y��������
	prePlayerY = position.y;

	
	//�p�b�h�p�֐�(���t���[���Ăяo��)
	GetJoypadXInputState(DX_INPUT_PAD1, &input);

	//���E�ړ�
	if ( (CheckHitKey(KEY_INPUT_A)) || (CheckHitKey(KEY_INPUT_LEFT)) || (input.Buttons[XINPUT_BUTTON_DPAD_LEFT]) ) //��(A�E���EPAD��)
	{
		IsWalkLeft = true;
		position.x -= speed;

		//���ɕǂ����邩���ׂ�
		int push = s->IsWallLeft(position + VECTOR2(0, 0));
		position.x += push;
		push = s->IsWallLeft(position + VECTOR2(0, 34));
		position.x += push;
		push = s->IsWallLeft(position + VECTOR2(0, 35));
		position.x += push;
		push = s->IsWallLeft(position + VECTOR2(0, 69));
		position.x += push;

	}
	else if ((CheckHitKey(KEY_INPUT_D)) || (CheckHitKey(KEY_INPUT_RIGHT)) || (input.Buttons[XINPUT_BUTTON_DPAD_RIGHT]) ) //�E(D�E���EPAD��)
	{
		IsWalkRight = true;
		position.x += speed;


		//�E�ɕǂ����邩���ׂ�
		int push = s->IsWallRight(position + VECTOR2(44, 0));
		position.x -= push;
		push = s->IsWallRight(position + VECTOR2(44, 34));
		position.x -= push;
		push = s->IsWallRight(position + VECTOR2(44, 35));
		position.x -= push;
		push = s->IsWallRight(position + VECTOR2(44, 69));
		position.x -= push;
	}

	//���s�A�j���[�V����
	if (IsWalkLeft)
	{
		patternY = 0;

		timer += Time::DeltaTime();
		if (timer >= 0.1f)
		{
			patternX += 1;
			timer = 0.0f;
			if (patternX >= 4)
			{
				patternX = 1;
			}
		}
	}
	else if (IsWalkRight)
	{
		patternY = 1;

		timer += Time::DeltaTime();
		if (timer >= 0.1f)
		{
			patternX += 1;
			timer = 0.0f;
			if (patternX >= 4)
			{
				patternX = 1;
			}
		}
	}
	else
	{
		//�����~�܂�
		patternX = 0;
		//���ʂ�����
		timer += Time::DeltaTime();
		if (timer >= 1.5f)
		{
			patternY = 2;
		}
	}

	//�W�����v
	if (CheckHitKey(KEY_INPUT_SPACE) || (input.Buttons[XINPUT_BUTTON_A]) || (input.Buttons[XINPUT_BUTTON_B]) )
	{
		if (prevJumpKey == false)
		{
			if (onGround == true)
			{
				//2�}�X����� velocity:���x
				velocity = V0; //"����"
				PlaySoundMem(jumpSE, DX_PLAYTYPE_BACK);
			}
		}
		prevJumpKey = true;
	}
	else
	{
		prevJumpKey = false;
	}

	//�d��
	position.y += velocity; //���W�ɂ͑��x�𑫂�
	velocity += Gravity;	//�������̗́@���x�ɂ͏d�͂𑫂�
	onGround = false;


	//���ɕǂ����邩���ׂ�
	if (velocity >= 0)// velocity:���x
	{
		int push = s->IsWallDown(position + VECTOR2(0, 70)); //���������̂�70
		if (push > 0)	//�n�ʂɐG�ꂽ�̂�
		{
			velocity = 0;			//�n�ʂɐG�����瑬�x��0��
			position.y -= push - 1; //�n�ʂ̏�ɉ����Ԃ�	1��������̂�push-1
			onGround = true;		//�ڒn���Ă�
		}
		push = s->IsWallDown(position + VECTOR2(22, 70));	 //�����������������̂�70
		if (push > 0)	//�n�ʂɐG�ꂽ�̂�
		{
			velocity = 0;			//�n�ʂɐG�����瑬�x��0��
			position.y -= push - 1; //�n�ʂ̏�ɉ����Ԃ�	1��������̂�push-1
			onGround = true;		//�ڒn���Ă�
		}
		push = s->IsWallDown(position + VECTOR2(44, 70));	 //�����������������̂�70
		if (push > 0)	//�n�ʂɐG�ꂽ�̂�
		{
			velocity = 0;			//�n�ʂɐG�����瑬�x��0��
			position.y -= push - 1; //�n�ʂ̏�ɉ����Ԃ�	1��������̂�push-1
			onGround = true;		//�ڒn���Ă�
		}
	}
	//��ɕǂ����邩���ׂ�
	else
	{
		int push = s->IsWallUp(position + VECTOR2(0, 0));
		if (push > 0)
		{
			velocity = 0.0f;
			position.y += push;
		}
		push = s->IsWallUp(position + VECTOR2(22, 0));
		if (push > 0)
		{
			velocity = 0.0f;
			position.y += push;
		}
		push = s->IsWallUp(position + VECTOR2(44, 0));
		if (push > 0)
		{
			velocity = 0.0f;
			position.y += push;
		}
	}
	
	//�v���C���[���v���C�G���A�ɕ����߂�
	if (position.x <= CHIP_SIZE*8)
	{
		position.x = CHIP_SIZE * 8;
	}
	if (position.x >= (CHIP_SIZE * 8) + (CHIP_SIZE * 24) - 45 )
	{
		position.x = (CHIP_SIZE * 8) + (CHIP_SIZE * 24) - 45;
	}

	//�v���C���[�ɍ��킹�ăX�N���[��(�����)
	if (position.y - s->scroll < CHIP_SIZE * 15) //�v���C���[��Y���W���Z�}�X�ȏ�(��)
	{
		s->scroll = position.y - CHIP_SIZE * 15; //�X�N���[�����x���v���C���[�ɍ��킹��
	}

	//��ʊO�ɏo���玀�S
	if (position.y >= Screen::HEIGHT + s->scroll)
	{
		finished = true;
	}

	//�S�[������
	if (!goaled && s->IsGoal(position + VECTOR2(22.5, 35))) //�S�[���͍���łȂ����S�Łi�E��20,����20�����j
	{
		Instantiate<GoalText>();
		goaled = true;
	}

	// �v���C���[���ݍ��� = �Q�_�̍� 
	playerHeight += prePlayerY - position.y;
}

void Player::Draw()
{
	DrawRectGraph(position.x, position.y - s->scroll, patternX*45, patternY*70, 45, 70, hImage, TRUE);
}