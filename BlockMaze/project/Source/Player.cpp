#include "Player.h"
#include "config.h"
#include "Stage.h"

Player::Player()
{
	hImage = LoadGraph("data/image/chara.png");
	position.x = 0;
	position.y = 0;
	speed.x = 0.0;
	speed.y = 0.0;
}

Player::~Player()
{
}

void Player::Update()
{
	Stage* s = FindGameObject<Stage>();
	if (CheckHitKey(KEY_INPUT_D)) {
		position.x += 2.0;
		//‰E‚É•Ç‚ª‚ ‚é‚©’²‚×‚é
		int push = s->IsWallRight(position + VECTOR2(39, 0));
			position.x -= push;
		 push = s->IsWallRight(position + VECTOR2(39, 39));
			position.x -= push;
	}
	else if (CheckHitKey(KEY_INPUT_A)) {
		position.x -= 2.0;
		//¶‚É•Ç‚ª‚ ‚é‚©’²‚×‚é
		int push = s->IsWallLeft(position + VECTOR2(0, 0));
		position.x += push;
		push = s->IsWallLeft(position + VECTOR2(0, 39));
		position.x += push;
	}
	else {
			speed.x = 0.0f;
	}
	position.x += speed.x;
	if (position.x < 0) {
		position.x = 0;
	}
	if (position.x > SCREEN_WIDTH - 64) {
		position.x = SCREEN_WIDTH - 64;
	}


	if (CheckHitKey(KEY_INPUT_W)) {
		position.y -= 2.0;
		//ã‚É•Ç‚ª‚ ‚é‚©’²‚×‚é
		int push = s->IsWallUp(position + VECTOR2(0, 0));
		position.y += push;
		push = s->IsWallUp(position + VECTOR2(39, 0));
		position.y += push;
	}
	else if (CheckHitKey(KEY_INPUT_S)) {
		position.y += 2.0;
		//‰º‚É•Ç‚ª‚ ‚é‚©’²‚×‚é
		int push = s->IsWallDown(position + VECTOR2(0, 39));
		position.y -= push;
		 push = s->IsWallDown(position + VECTOR2(39, 39));
		position.y -= push;

	}
	else {
			speed.y = 0.0f;
	}
	position.y += speed.y;
	if (position.y < 0) {
		position.y = 0;
	}
	if (position.y > SCREEN_HEIGHT - 64) {
		position.y = SCREEN_HEIGHT - 64;
	}

}

void Player::Draw()
{
	DrawRectGraph(position.x, position.y, 0, 0, 40, 40, hImage, TRUE);
}
