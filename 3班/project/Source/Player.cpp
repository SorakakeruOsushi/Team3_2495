#include "Player.h"
#include <cassert>
#include "Screen.h"
#include "Stage.h"
#include "GoalText.h"

const float Gravity = 0.2f;							 //�d��
const float JumpHight = 30 * 2;						 //�W�����v�̍���
//			v0 = -  ��   2   *   g     *    S
const float V0 = -sqrtf(2.0f * Gravity * JumpHight); //������(�W�����v)�̎�

Player::Player()
{
	// Player�͏c�Qx���P�}�X�̑傫��
	hImage = LoadGraph("data/image/Player_2-1.png");
		assert(hImage > 0);

	position.x = 0;
	position.y = 0;

	playerHeight = -10.0f; //�����̍���(10)������
	prePlayerY = 0;

	speed = 1.5f;

	finished = false;
	goaled = false;

	velocity = 0.0f;
}

Player::~Player()
{
	DeleteGraph(hImage);
}

void Player::Update()
{
	if (finished || goaled) {
		return;
	}

	Stage* s = FindGameObject<Stage>();

	// �v���C���[Y��������
	prePlayerY = position.y;

	//���E�ړ�
	if (CheckHitKey(KEY_INPUT_A))
	{
		//��
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
	if (CheckHitKey(KEY_INPUT_D))
	{
		//�E
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

	//�W�����v
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		if (prevJumpKey == false)
		{
			if (onGround == true)
			{
				//2�}�X����� velocity:���x
				velocity = V0; //"����"
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
	Stage* s = FindGameObject<Stage>();
	DrawGraph(position.x, position.y - s->scroll, hImage, TRUE);
}
