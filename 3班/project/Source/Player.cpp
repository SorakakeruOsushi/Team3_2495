#include "Player.h"
#include <cassert>

Player::Player()
{
	hImage = LoadGraph("data/image/chara.png");
	assert(hImage > 0);//読み込めてる？

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
	//表示テスト用
	DrawRectGraph(position.x, position.y,0,0,40,40, hImage, TRUE);
}
