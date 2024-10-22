#include "Player.h"
#include "config.h"
#include "Stage.h"

Player::Player()
{
	hImage = LoadGraph("data/image/chara.png");
	position.x = 0;
	position.y = 0;
	speed.x = 2.0;
	speed.y = 2.0;
}

Player::~Player()
{
	DeleteGraph(hImage);
}

void Player::Update()
{
	Stage* s = FindGameObject<Stage>();

	if (CheckHitKey(KEY_INPUT_D)) //右移動
	{
		position.x += speed.x;
		//右に壁があるか調べる
		int push = s->IsWallRight(position + VECTOR2(39, 0));
			position.x -= push;
			push = s->IsWallRight(position + VECTOR2(39, 39));
			position.x -= push;
	}
	else if (CheckHitKey(KEY_INPUT_A)) //左移動
	{
		position.x -= speed.x;
		//左に壁があるか調べる
		int push = s->IsWallLeft(position + VECTOR2(0, 0));
		position.x += push;
		push = s->IsWallLeft(position + VECTOR2(0, 39));
		position.x += push;
	}

	if (CheckHitKey(KEY_INPUT_W)) //上移動
	{
		position.y -= speed.y;
		//上に壁があるか調べる
		int push = s->IsWallUp(position + VECTOR2(0, 0));
		position.y += push;
		push = s->IsWallUp(position + VECTOR2(39, 0));
		position.y += push;
	}
	else if (CheckHitKey(KEY_INPUT_S)) //下移動
	{
		position.y += speed.y;
		//下に壁があるか調べる
		int push = s->IsWallDown(position + VECTOR2(0, 39));
		position.y -= push;
		 push = s->IsWallDown(position + VECTOR2(39, 39));
		position.y -= push;
	}


	//画面外に出さない(X)
	if (position.x < 0) {
		position.x = 0;
	}
	if (position.x > SCREEN_WIDTH - 64) {
		position.x = SCREEN_WIDTH - 64;
	}
	//画面外に出さない(Y)
	if (position.y < 0) 
	{
		position.y = 0;
	}
	if (position.y > SCREEN_HEIGHT - 40) 
	{
		position.y = SCREEN_HEIGHT - 40;
	}
}

void Player::Draw()
{
	DrawRectGraph(position.x, position.y, 0, 0, 40, 40, hImage, TRUE);
}
