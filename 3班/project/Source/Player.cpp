#include "Player.h"
#include "Stage.h"
#include <cassert>

Player::Player()
{
	hImage = LoadGraph("data/image/player.png");
	assert(hImage > 0);//�ǂݍ��߂Ă�H

	position.x = 100;
	position.y = 500;

	speed = 2.0f;
}

Player::~Player()
{
	DeleteGraph(hImage);
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
	DrawGraph(position.x, position.y, hImage, TRUE);
	//DrawRectGraph(position.x, position.y,	0, 0,	 40, 40, hImage, TRUE);
}
