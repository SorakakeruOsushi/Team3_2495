#include "Player.h"
#include "Stage.h"
#include <cassert>

const float Gravity = 0.3f;							 //�d��
const float JumpHight = 40 * 2;						 //�W�����v�̍���
//			v0 = -  ��   2   *   g     *    S
const float V0 = -sqrtf(2.0f * Gravity * JumpHight); //������(�W�����v)�̎�

Player::Player()
{
	// Player�͏c�Qx���P�}�X�̑傫��
	hImage = LoadGraph("data/image/player_2-1.png");
		assert(hImage > 0);

	position.x = 0;
	position.y = 0;

	speed = 1.5f;

	dead = false;
}

Player::~Player()
{
	DeleteGraph(hImage);
}

void Player::Update()
{
	if(dead)
	{
		return;
	}

	Stage* s = FindGameObject<Stage>();

	//�e�X�g�p�㉺����
	if (CheckHitKey(KEY_INPUT_W))
	{
		position.y -= speed;//��
	}
	if (CheckHitKey(KEY_INPUT_S))
	{
		position.y += speed;//��
	}
	
	//���E�ړ�
	if (CheckHitKey(KEY_INPUT_A))
	{
		//��
		position.x -= speed;
		/*
		//���ɕǂ����邩���ׂ�
		int push = s->IsWallLeft(position + VECTOR2(0, 0));
		position.x += push;
		push = s->IsWallLeft(position + VECTOR2(0, 29));
		position.x += push;
		*/
	}
	if (CheckHitKey(KEY_INPUT_D))
	{
		//�E
		position.x += speed;
		/*
		//�E�ɕǂ����邩���ׂ�
		int push = s->IsWallRight(position + VECTOR2(59, 0));
		position.x -= push;
		push = s->IsWallRight(position + VECTOR2(59, 59));
		position.x -= push;
		*/
	}

	/*
	//���wBlockMaze�x����̃R�s�y�ɂȂ�܂��B
	//�� ���s����Ɨ�O����������̂ŃR�����g�A�E�g���܂����B
	//�� �����蔻�菈������肭�����������܂�����A������͍폜���Ă��\���܂���B

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
		int push = s->IsWallDown(position + VECTOR2(0, 60)); //���������̂�60
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
	//��ɕǂ����邩���ׂ�
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
	*/

	//�v���C���[�ɍ��킹�ăX�N���[��(�����)
	if (position.y - s->scroll < 30 * 15) //�v���C���[��Y���W���Z�}�X�ȏ�(��)
	{
		s->scroll = position.y - 30 * 15; //�X�N���[�����x���v���C���[�ɍ��킹��
	}
	//�v���C���[�ɍ��킹�ăX�N���[��(������)
	if (position.y - s->scroll > 30 * 20) //�v���C���[��Y���W���Z�}�X�ȉ�(��)
	{
		s->scroll = position.y - 30 * 20; //�X�N���[�����x���v���C���[�ɍ��킹��
	}
	
}

void Player::Draw()
{
	Stage* s = FindGameObject<Stage>();
	DrawGraph(position.x, position.y - s->scroll, hImage, TRUE);
}
