#include "Player.h"
#include "Stage.h"
#include <cassert>

Player::Player()
{
	hImage = LoadGraph("data/image/player.png");
	assert(hImage > 0);//�ǂݍ��߂Ă�H

	//�\���e�X�g�p
	TestImage = LoadGraph("data/image/trpg_dot_maker2x.png");
	assert(TestImage > 0);//�ǂݍ��߂Ă�H

	position.x = 100;
	position.y = 500;

	speed = 2.0f;
}

Player::~Player()
{
	DeleteGraph(hImage);

	//�\���e�X�g�p
	DeleteGraph(TestImage);
}

void Player::Update()
{
	Stage* s = FindGameObject<Stage>();
	if (CheckHitKey(KEY_INPUT_W))
	{
		position.y -= speed;//[W]��ړ�
	}
	if (CheckHitKey(KEY_INPUT_S))
	{
		position.y += speed;//[S]���ړ�
	}
	if (CheckHitKey(KEY_INPUT_A))
	{
		position.x -= speed;//[A]���ړ�
	}
	if (CheckHitKey(KEY_INPUT_D))
	{
		position.x += speed;//[D]�E�ړ�
	}
}

void Player::Draw()
{
	DrawGraph(0, 0, hImage, TRUE);

	//�\���e�X�g�p
	DrawGraph(0, 0, TestImage, TRUE);
	//DrawRectGraph(position.x, position.y,	0, 0,	 40, 40, hImage, TRUE);
}
