#include "Player.h"
#include <cassert>

Player::Player()
{
	hImage = LoadGraph("data/image/chara.png");
	assert(hImage > 0);//�ǂݍ��߂Ă�H

	position.x = 100;
	position.y = 500;
}

Player::~Player()
{
	DeleteGraph(hImage);
}

void Player::Update()
{
}

void Player::Draw()
{
	//�\���e�X�g�p
	DrawRectGraph(position.x, position.y,0,0,40,40, hImage, TRUE);
}
