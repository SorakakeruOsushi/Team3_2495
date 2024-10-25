#include "Player.h"
#include "Stage.h"
#include <cassert>

Player::Player()
{
	hImage = LoadGraph("data/image/chara.png");
	assert(hImage > 0);//読み込めてる？

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
		position.y -= speed;//[W]上移動
	}
	if (CheckHitKey(KEY_INPUT_S))
	{
		position.y += speed;//[S]下移動
	}
	if (CheckHitKey(KEY_INPUT_A))
	{
		position.x -= speed;//[A]左移動
	}
	if (CheckHitKey(KEY_INPUT_D))
	{
		position.x += speed;//[D]右移動
	}
}

void Player::Draw()
{
	//表示テスト用
	DrawRectGraph(position.x, position.y,	0, 0,	 40, 40, hImage, TRUE);
}
