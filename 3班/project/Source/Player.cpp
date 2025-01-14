#include "Player.h"
#include <cassert>
#include "Screen.h"
#include "GoalText.h"
#include "Stage.h"

const float Gravity = 0.3f;							 //�d��
const float JumpHight = 30 * 2.5f;				     //�W�����v�̍���
//			v0 = -  ��   2   *   g     *    S
const float V0 = -sqrtf(2.0f * Gravity * JumpHight); //������(�W�����v)�̎�

Player::Player()
{



	playerIdolImage = LoadGraph("data/image/Player_2-1.PNG"); // �摜 IDOL�v���C���[
		assert(playerIdolImage > 0);
	playerAnimImage = LoadGraph("data/image/niaa1.png");	  // �摜 ANIM�v���C���[
		assert(playerAnimImage > 0);
	playerImage = playerIdolImage; //�f�t�H���g��IDOL


	jumpSound = LoadSoundMem("data/sound/���ʉ����{/�W�����v.mp3");  // �� �W�����v
		assert(jumpSound > 0);

	pm = FindGameObject<PlayMode>();
		assert(pm != nullptr);
	s = FindGameObject<Stage>();
		assert(pm != nullptr);

	position.x = 0.0f;
	position.y = 0.0f;

	playerHeight = -10.0f; //�����̍���(10)������
	prePlayerY = 0;

	speed = 2.0f;

	//�v���C���[�̕��s�A�j���[�V�����֘A
	patternX = 0;
	patternY = 0;
	timer = 0;
	IsWalkLeft = false;
	IsWalkRight = false;
	//
	prevJumpKey = false;
	onGround = false;

	inGround = false;

	finished = false;
	goaled = false;

	velocity = 0.0f;
	//
	gotCoin = 0;
	//�v���C���[�����x
	alpha = 0;
}

Player::~Player()
{
	DeleteGraph(playerImage);
	DeleteSoundMem(jumpSound);
}

void Player::Update()
{
	if(!pm->IsGameStart)		 // �Q�[���J�n�O
	{
		return;
	}
	else if (finished || goaled) // �Q�[���I��
	{
		return;
	}
	else if (pm->playMode == 1)	 // �u���b�N���[�h
	{
		alpha = 100;
		return;
	}
	else if (pm->playMode == 0)	 // �e�g�����[�h
	{
		alpha = 255;
	}

	IsWalkLeft = false;
	IsWalkRight = false;

	// �v���C���[Y��������
	prePlayerY = position.y;
	
	// �p�b�h�p�֐�(���t���[���Ăяo��)
	GetJoypadXInputState(DX_INPUT_PAD1, &input);

		int push = s->IsWallDown(position + VECTOR2(0, 29));
		if (push > 0)	//�n�ʂɐG�ꂽ�̂�
		{
			velocity = 0;			//�n�ʂɐG�����瑬�x��0��
			position.y -= push - 1; //�n�ʂ̏�ɉ����Ԃ�	1��������̂�push-1
			onGround = true;		//�ڒn���Ă�
		}
		push = s->IsWallDown(position + VECTOR2(29, 29));
		if (push > 0)	//�n�ʂɐG�ꂽ�̂�
		{
			velocity = 0;			//�n�ʂɐG�����瑬�x��0��
			position.y -= push - 1; //�n�ʂ̏�ɉ����Ԃ�	1��������̂�push-1
			onGround = true;		//�ڒn���Ă�
		}

		push = s->IsWallDown(position + VECTOR2(0, 30 + 6.6));
		if (push > 0)	//�n�ʂɐG�ꂽ�̂�
		{
			velocity = 0;			//�n�ʂɐG�����瑬�x��0��
			position.y -= push - 1; //�n�ʂ̏�ɉ����Ԃ�	1��������̂�push-1
			onGround = true;		//�ڒn���Ă�
		}
		push = s->IsWallDown(position + VECTOR2(29, 30));
		if (push > 0)	//�n�ʂɐG�ꂽ�̂�
		{
			velocity = 0;			//�n�ʂɐG�����瑬�x��0��
			position.y -= push - 1; //�n�ʂ̏�ɉ����Ԃ�	1��������̂�push-1
			onGround = true;		//�ڒn���Ă�
		}

		push = s->IsWallDown(position + VECTOR2(0, 59));
		if (push > 0)	//�n�ʂɐG�ꂽ�̂�
		{
			velocity = 0;			//�n�ʂɐG�����瑬�x��0��
			position.y -= push - 1; //�n�ʂ̏�ɉ����Ԃ�	1��������̂�push-1
			onGround = true;		//�ڒn���Ă�
		}
		push = s->IsWallDown(position + VECTOR2(29, 59));
		if (push > 0)	//�n�ʂɐG�ꂽ�̂�
		{
			velocity = 0;			//�n�ʂɐG�����瑬�x��0��
			position.y -= push - 1; //�n�ʂ̏�ɉ����Ԃ�	1��������̂�push-1
			onGround = true;		//�ڒn���Ă�
		}

	// ���E�ړ�
	if ( (CheckHitKey(KEY_INPUT_A)) || (CheckHitKey(KEY_INPUT_LEFT)) || (input.Buttons[XINPUT_BUTTON_DPAD_LEFT]) ) //��(A�E���EPAD��)
	{
		IsWalkLeft = true;
		position.x -= speed;
		
		//���ɕǂ����邩���ׂ�
		int push = s->IsWallLeft(position + VECTOR2(0, 0));
		position.x += push;
		push = s->IsWallLeft(position + VECTOR2(0, 30));
		position.x += push;
		push = s->IsWallLeft(position + VECTOR2(0, 31));
		position.x += push;
		push = s->IsWallLeft(position + VECTOR2(0, 59));
		position.x += push;
	}
	else if ((CheckHitKey(KEY_INPUT_D)) || (CheckHitKey(KEY_INPUT_RIGHT)) || (input.Buttons[XINPUT_BUTTON_DPAD_RIGHT]) ) //�E(D�E���EPAD��)
	{
		IsWalkRight = true;
		position.x += speed;
		
		//�E�ɕǂ����邩���ׂ�
		int push = s->IsWallRight(position + VECTOR2(29, 0));
		position.x -= push;
		push = s->IsWallRight(position + VECTOR2(29, 30));
		position.x -= push;
		push = s->IsWallRight(position + VECTOR2(29, 31));
		position.x -= push;
		push = s->IsWallRight(position + VECTOR2(29, 59));
		position.x -= push;
	}

	// ���s�A�j���[�V����
	if (IsWalkLeft)
	{
		playerImage = playerAnimImage; // Anim�摜
		patternY = 0;

		timer += Time::DeltaTime();
		if (timer >= 0.1f)
		{
			patternX += 1;
			timer = 0.0f;
			if (patternX >= 3)
			{
				patternX = 0;
			}
		}
	}
	else if (IsWalkRight)
	{
		playerImage = playerAnimImage; // Anim�摜
		patternY = 1;

		timer += Time::DeltaTime();
		if (timer >= 0.1f)
		{
			patternX += 1;
			timer = 0.0f;
			if (patternX >= 3)
			{
				patternX = 0;
			}
		}
	}
	else
	{
		// �����~�܂�
		patternX = 0;
		// ���ʂ�����
		timer += Time::DeltaTime();
		if (timer >= 1.5f)
		{
			playerImage = playerIdolImage;
		}
	}

	
	// �W�����v
	if (CheckHitKey(KEY_INPUT_SPACE) || (input.Buttons[XINPUT_BUTTON_A]) || (input.Buttons[XINPUT_BUTTON_B]) )
	{
		if (prevJumpKey == false)
		{
			if (onGround == true)
			{
				//2�}�X����� velocity:���x
				velocity = V0; //"����"
				PlaySoundMem(jumpSound, DX_PLAYTYPE_BACK); // �W�����v���̍Đ�
			}
		}
		prevJumpKey = true;
	}
	else
	{
		prevJumpKey = false;
	}

	// �d��
	position.y += velocity; //���W�ɂ͑��x�𑫂�
	velocity += Gravity;	//�������̗́@���x�ɂ͏d�͂𑫂�
	onGround = false;


	// ���ɕǂ����邩���ׂ�
	if (velocity >= 0)// velocity:���x
	{
		int push = s->IsWallDown(position + VECTOR2(0, 60)); //�����������������̂�60
		if (push > 0)	//�n�ʂɐG�ꂽ�̂�
		{
			velocity = 0;			//�n�ʂɐG�����瑬�x��0��
			position.y -= push - 1; //�n�ʂ̏�ɉ����Ԃ�	1��������̂�push-1
			onGround = true;		//�ڒn���Ă�
		}
		push = s->IsWallDown(position + VECTOR2(29, 60));	 //�����������������̂�60
		if (push > 0)	//�n�ʂɐG�ꂽ�̂�
		{
			velocity = 0;			//�n�ʂɐG�����瑬�x��0��
			position.y -= push - 1; //�n�ʂ̏�ɉ����Ԃ�	1��������̂�push-1
			onGround = true;		//�ڒn���Ă�
		}
	}
	// ��ɕǂ����邩���ׂ�
	else
	{
		int push = s->IsWallUp(position + VECTOR2(0, 0));
		if (push > 0)
		{
			velocity = 0.0f;
			position.y += push;
		}
		push = s->IsWallUp(position + VECTOR2(29, 0));
		if (push > 0)
		{
			velocity = 0.0f;
			position.y += push;
		}
	}
	
	//�v���C���[���v���C�G���A�ɕ����߂�
	if (position.x <= CHIP_SIZE * 8)
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
	if (!goaled && s->IsGoal(position + VECTOR2(15, 30))) //�S�[���͍���łȂ����S�Łi�E��15,����30�����j
	{
		Instantiate<GoalText>();
		goaled = true;
	}

	// �v���C���[���ݍ��� = �Q�_�̍� 
	playerHeight += prePlayerY - position.y;
}

void Player::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

	if (playerImage == playerIdolImage)
	{
		DrawGraph(position.x-7.5, position.y - s->scroll, playerImage, TRUE);
	}
	if (playerImage == playerAnimImage) 
	{
		DrawRectGraph(position.x, position.y - s->scroll, patternX * 30, patternY * 69, 30, 69, playerImage, TRUE);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}