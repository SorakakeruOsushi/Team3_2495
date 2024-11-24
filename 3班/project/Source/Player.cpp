#include "Player.h"
#include "Stage.h"
#include <cassert>
#include "FinishText.h"
#include "GoalText.h"

const float Gravity = 0.2f;							 //重力
const float JumpHight = 30 * 2;						 //ジャンプの高さ
//			v0 = -  √   2   *   g     *    S
const float V0 = -sqrtf(2.0f * Gravity * JumpHight); //放物線(ジャンプ)の式

Player::Player()
{
	// Playerは縦２x横１マスの大きさ
	hImage = LoadGraph("data/image/Player_2-1.png");
	assert(hImage > 0);

	position.x = 0;
	position.y = 0;

	speed = 1.5f;

	finished = false;
	goaled = false;

	velocity = 0.0f;

	playerHeight = 0;
}

Player::~Player()
{
	DeleteGraph(hImage);
}

void Player::Update()
{
	if (goaled)
	{
		Instantiate<GoalText>();
		return;
	}
	if (finished)
	{
		Instantiate<FinishText>();
		return;
	}


	Stage* s = FindGameObject<Stage>();

	//左右移動
	if (CheckHitKey(KEY_INPUT_A))
	{
		//左
		position.x -= speed;

		//左に壁があるか調べる
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
		//右
		position.x += speed;

		//右に壁があるか調べる
		int push = s->IsWallRight(position + VECTOR2(44, 0));
		position.x -= push;
		push = s->IsWallRight(position + VECTOR2(44, 34));
		position.x -= push;
		push = s->IsWallRight(position + VECTOR2(44, 35));
		position.x -= push;
		push = s->IsWallRight(position + VECTOR2(44, 69));
		position.x -= push;

	}

	//ジャンプ
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		if (prevJumpKey == false)
		{
			if (onGround == true)
			{
				//2マス分飛ぶ velocity:速度
				velocity = V0; //"初速"
			}
		}
		prevJumpKey = true;
	}
	else
	{
		prevJumpKey = false;
	}

	//重力
	position.y += velocity; //座標には速度を足す
	velocity += Gravity;	//下向きの力　速度には重力を足す
	onGround = false;


	//下に壁があるか調べる
	if (velocity >= 0)// velocity:速度
	{
		int push = s->IsWallDown(position + VECTOR2(0, 70)); //一個下を見るので70
		if (push > 0)	//地面に触れたので
		{
			velocity = 0;			//地面に触ったら速度を0に
			position.y -= push - 1; //地面の上に押し返す	1個下を見るのでpush-1
			onGround = true;		//接地してる
		}
		push = s->IsWallDown(position + VECTOR2(22, 70));	 //一個下を見る一個下を見るので70
		if (push > 0)	//地面に触れたので
		{
			velocity = 0;			//地面に触ったら速度を0に
			position.y -= push - 1; //地面の上に押し返す	1個下を見るのでpush-1
			onGround = true;		//接地してる
		}
		push = s->IsWallDown(position + VECTOR2(44, 70));	 //一個下を見る一個下を見るので70
		if (push > 0)	//地面に触れたので
		{
			velocity = 0;			//地面に触ったら速度を0に
			position.y -= push - 1; //地面の上に押し返す	1個下を見るのでpush-1
			onGround = true;		//接地してる
		}
	}
	//上に壁があるか調べる
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

	/*
	* //score更新(仮)
	* 後でChipサイズに合わせる
	// スコアの更新確認
	int high = position.y;
	if (score < high)
	{
		score = high;
	}
	*/

	/*
	//プレイヤーに合わせてスクロール(上方向)
	if (position.y - s->scroll < 30 * 15) //プレイヤーのY座標が〇マス以上(仮)
	{
		s->scroll = position.y - 30 * 15; //スクロール速度をプレイヤーに合わせる
	}
	*/

	//ゴールした
	if (s->IsGoal(position + VECTOR2(22.5, 35))) //ゴールは左上でなく中心で（右に20,下に20ずれる）
	{
		goaled = true;
	}
	//「GOAL/FINISH」より「CLEAR/GAME OVER」のが良かったかも？変更するかも
}

void Player::Draw()
{
	Stage* s = FindGameObject<Stage>();
	DrawGraph(position.x, position.y - s->scroll, hImage, TRUE);
}
