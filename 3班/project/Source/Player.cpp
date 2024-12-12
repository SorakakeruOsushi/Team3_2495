#include "Player.h"
#include <cassert>
#include "Screen.h"
#include "GoalText.h"
#include "Stage.h"

const float Gravity = 0.2f;							 //重力
const float JumpHight = 30 * 32.5f;						 //ジャンプの高さ
//			v0 = -  √   2   *   g     *    S
const float V0 = -sqrtf(2.0f * Gravity * JumpHight); //放物線(ジャンプ)の式

Player::Player()
{
	// Playerは縦２x横１マスの大きさ
	hImage = LoadGraph("data/image/TETRAall.png");
		assert(hImage > 0);
	// Jumpサウンドデータを読み込む 
	jumpSE = LoadSoundMem("data/sound/効果音ラボ/ジャンプ.mp3");  // プレイヤーJumpサウンド
		assert(jumpSE > 0);

		//pm = Instantiate<PlayMode>();

	pm = FindGameObject<PlayMode>();
		assert(pm != nullptr);

	s = FindGameObject<Stage>();

	position.x = 0;
	position.y = 0;

	playerHeight = -10.0f; //床分の高さ(10)分引く
	prePlayerY = 0;

	speed = 2.0f;

	//プレイヤーの歩行アニメーション関連
	patternX = 0;
	patternY = 2;
	timer = 0;
	IsWalkLeft = false;
	IsWalkRight = false;
	//
	prevJumpKey = false;
	onGround = false;

	finished = false;
	goaled = false;

	velocity = 0.0f;

	gotCoin = 0;
}

Player::~Player()
{
	DeleteGraph(hImage);
	DeleteSoundMem(jumpSE);
}

void Player::Update()
{
	if (finished || goaled)
	{
		return;
	}
	else if (pm->playMode == 1)
	{
		return;
	}

	IsWalkLeft = false;
	IsWalkRight = false;

	// プレイヤーY軸を入れる
	prePlayerY = position.y;

	
	//パッド用関数(毎フレーム呼び出す)
	GetJoypadXInputState(DX_INPUT_PAD1, &input);

	//左右移動
	if ( (CheckHitKey(KEY_INPUT_A)) || (CheckHitKey(KEY_INPUT_LEFT)) || (input.Buttons[XINPUT_BUTTON_DPAD_LEFT]) ) //左(A・←・PAD←)
	{
		IsWalkLeft = true;
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
	else if ((CheckHitKey(KEY_INPUT_D)) || (CheckHitKey(KEY_INPUT_RIGHT)) || (input.Buttons[XINPUT_BUTTON_DPAD_RIGHT]) ) //右(D・→・PAD→)
	{
		IsWalkRight = true;
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

	//歩行アニメーション
	if (IsWalkLeft)
	{
		patternY = 0;

		timer += Time::DeltaTime();
		if (timer >= 0.1f)
		{
			patternX += 1;
			timer = 0.0f;
			if (patternX >= 4)
			{
				patternX = 1;
			}
		}
	}
	else if (IsWalkRight)
	{
		patternY = 1;

		timer += Time::DeltaTime();
		if (timer >= 0.1f)
		{
			patternX += 1;
			timer = 0.0f;
			if (patternX >= 4)
			{
				patternX = 1;
			}
		}
	}
	else
	{
		//立ち止まる
		patternX = 0;
		//正面を向く
		timer += Time::DeltaTime();
		if (timer >= 1.5f)
		{
			patternY = 2;
		}
	}

	//ジャンプ
	if (CheckHitKey(KEY_INPUT_SPACE) || (input.Buttons[XINPUT_BUTTON_A]) || (input.Buttons[XINPUT_BUTTON_B]) )
	{
		if (prevJumpKey == false)
		{
			if (onGround == true)
			{
				//2マス分飛ぶ velocity:速度
				velocity = V0; //"初速"
				PlaySoundMem(jumpSE, DX_PLAYTYPE_BACK);
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
	
	//プレイヤーをプレイエリアに閉じ込める
	if (position.x <= CHIP_SIZE*8)
	{
		position.x = CHIP_SIZE * 8;
	}
	if (position.x >= (CHIP_SIZE * 8) + (CHIP_SIZE * 24) - 45 )
	{
		position.x = (CHIP_SIZE * 8) + (CHIP_SIZE * 24) - 45;
	}

	//プレイヤーに合わせてスクロール(上方向)
	if (position.y - s->scroll < CHIP_SIZE * 15) //プレイヤーのY座標が〇マス以上(仮)
	{
		s->scroll = position.y - CHIP_SIZE * 15; //スクロール速度をプレイヤーに合わせる
	}

	//画面外に出たら死亡
	if (position.y >= Screen::HEIGHT + s->scroll)
	{
		finished = true;
	}

	//ゴールした
	if (!goaled && s->IsGoal(position + VECTOR2(22.5, 35))) //ゴールは左上でなく中心で（右に20,下に20ずれる）
	{
		Instantiate<GoalText>();
		goaled = true;
	}

	// プレイヤー現在高さ = ２点の差 
	playerHeight += prePlayerY - position.y;
}

void Player::Draw()
{
	DrawRectGraph(position.x, position.y - s->scroll, patternX*45, patternY*70, 45, 70, hImage, TRUE);
}