#include "Player.h"
#include <cassert>
#include "Screen.h"
#include "GoalText.h"
#include "Stage.h"
#include "../Library/Utility.h"


const float Gravity = 0.3f;							 //重力
const float JumpHight = 30 * 2.5f;				     //ジャンプの高さ
//			v0 = -  √   2   *   g     *    S
const float V0 = -sqrtf(2.0f * Gravity * JumpHight); //放物線(ジャンプ)の式

Player::Player()
{
	playerIdolImage = LoadGraph("data/image/Player_2-1.PNG"); // 画像 IDOLプレイヤー
		assert(playerIdolImage > 0);
	playerAnimImage = LoadGraph("data/image/niaa1.png");	  // 画像 ANIMプレイヤー
		assert(playerAnimImage > 0);
	playerImage = playerIdolImage; //デフォルトはIDOL

	jumpSound = LoadSoundMem("data/sound/GameSE/ジャンプ(3).mp3"); // 音 ジャンプ
		assert(jumpSound > 0);
	fallSound = LoadSoundMem("data/sound/GameSE/落下.mp3");		   // 音 落下
		assert(fallSound > 0);


	pm = FindGameObject<PlayMode>();
		assert(pm != nullptr);
	s = FindGameObject<Stage>();
		assert(pm != nullptr);

	position.x = 0.0f;
	position.y = 0.0f;

	playerHeight = -10.0f; //床分の高さ(10)分引く
	prePlayerY = 0;
	playerBestHeight = 0.0f; //最高到達点

	speed = 2.0f;

	//プレイヤーの表示関連
	patternX = 0;
	patternY = 0;
	timer = 0;
	collisionDown = 9;
	//
	prevJumpKey = false;
	onGround = false;

	finished = false;
	goaled = false;

	velocity = 0.0f;
	
	gotCoin = 0;	  // コイン取得数
	gotCoinSP = 0;	  // SPコイン取得数
	alpha = 0;		  //プレイヤー透明度
	outOfScreen = 39; // プレイヤーがどの程度画面の外に出たらゲームオーバーになるか
}

Player::~Player()
{
	DeleteGraph(playerIdolImage);
	DeleteGraph(playerAnimImage);
	DeleteSoundMem(jumpSound);
	DeleteSoundMem(fallSound);
}

void Player::Update()
{
	if(!pm->IsGameStart)		 // ゲームを開始する
	{
		return;
	}
	else if (finished || goaled) // ゲームが終了する
	{
		return;
	}
	else if (pm->playMode == 1)	 // ブロックモードになる
	{
		alpha = 100;
		return;
	}
	else if (pm->playMode == 0)	 // テトラモードになる
	{
		alpha = 255;
	}

	// プレイヤーY軸を入れる
	prePlayerY = position.y;

	IsWalkLeft = false;
	IsWalkRight = false;
	
	// パッド用関数(毎フレーム呼び出す)
	GetJoypadXInputState(DX_INPUT_PAD1, &input);


	//上へ行こう、ランララン
	/*
	int push = s->IsWallDown(position + VECTOR2(0, 29 + collisionDown));
	if (push > 0)	//地面に触れたので
		{
			velocity = 0;			//地面に触ったら速度を0に
			position.y -= push - 1; //地面の上に押し返す	1個下を見るのでpush-1
			onGround = true;		//接地してる
		}
		push = s->IsWallDown(position + VECTOR2(29, 29 + collisionDown));
		if (push > 0)	//地面に触れたので
		{
			velocity = 0;			//地面に触ったら速度を0に
			position.y -= push - 1; //地面の上に押し返す	1個下を見るのでpush-1
			onGround = true;		//接地してる
		}

		push = s->IsWallDown(position + VECTOR2(0, 30 + collisionDown));
		if (push > 0)	//地面に触れたので
		{
			velocity = 0;			//地面に触ったら速度を0に
			position.y -= push - 1; //地面の上に押し返す	1個下を見るのでpush-1
			onGround = true;		//接地してる
		}
		push = s->IsWallDown(position + VECTOR2(29, 30 + collisionDown));
		if (push > 0)	//地面に触れたので
		{
			velocity = 0;			//地面に触ったら速度を0に
			position.y -= push - 1; //地面の上に押し返す	1個下を見るのでpush-1
			onGround = true;		//接地してる
		}

		push = s->IsWallDown(position + VECTOR2(0, 59 + collisionDown));
		if (push > 0)	//地面に触れたので
		{
			velocity = 0;			//地面に触ったら速度を0に
			position.y -= push - 1; //地面の上に押し返す	1個下を見るのでpush-1
			onGround = true;		//接地してる
		}
		push = s->IsWallDown(position + VECTOR2(29, 59 + collisionDown));
		if (push > 0)	//地面に触れたので
		{
			velocity = 0;			//地面に触ったら速度を0に
			position.y -= push - 1; //地面の上に押し返す	1個下を見るのでpush-1
			onGround = true;		//接地してる
		}*/

	// 左右移動
	if ( (CheckHitKey(KEY_INPUT_A)) || (CheckHitKey(KEY_INPUT_LEFT)) || (input.Buttons[XINPUT_BUTTON_DPAD_LEFT]) ) //左(A・←・PAD←)
	{
		IsWalkLeft = true;
		position.x -= speed;
		
		//左に壁があるか調べる
		int push = s->IsWallLeft(position + VECTOR2(0, 0 + collisionDown));
		position.x += push;
		push = s->IsWallLeft(position + VECTOR2(0, 30 + collisionDown));
		position.x += push;
		push = s->IsWallLeft(position + VECTOR2(0, 31 + collisionDown));
		position.x += push;
		push = s->IsWallLeft(position + VECTOR2(0, 59 + collisionDown));
		position.x += push;
	}
	else if ((CheckHitKey(KEY_INPUT_D)) || (CheckHitKey(KEY_INPUT_RIGHT)) || (input.Buttons[XINPUT_BUTTON_DPAD_RIGHT]) ) //右(D・→・PAD→)
	{
		IsWalkRight = true;
		position.x += speed;
		
		//右に壁があるか調べる
		int push = s->IsWallRight(position + VECTOR2(29, 0 + collisionDown));
		position.x -= push;
		push = s->IsWallRight(position + VECTOR2(29, 30 + collisionDown));
		position.x -= push;
		push = s->IsWallRight(position + VECTOR2(29, 31 + collisionDown));
		position.x -= push;
		push = s->IsWallRight(position + VECTOR2(29, 59 + collisionDown));
		position.x -= push;
	}



	// 歩行アニメーション
	if ((!onGround) && (IsWalkLeft)) //3
	{
		if (patternX <= 1)
		{
			patternX = 1;
		}
		else
		{
			patternX = 3;
		}
		patternY = 0;
	}
	else if (IsWalkLeft)
	{
		playerImage = playerAnimImage; // Anim画像
		patternY = 0;

		timer += Time::DeltaTime();
		if (timer >= 0.25f)
		{
			patternX += 1;
			timer = 0.0f;
			if (patternX > 3)
			{
				patternX = 0;
			}
		}
	}
	else if ((!onGround) && (IsWalkRight)) // 1
	{
		if (patternX <= 1)
		{
			patternX = 1;
		}
		else
		{
			patternX = 3;
		}
		patternY = 1;
	}
	else if (IsWalkRight)
	{
		playerImage = playerAnimImage; // Anim画像
		patternY = 1;

		timer += Time::DeltaTime();
		if (timer >= 0.15f)
		{
			patternX += 1;
			timer = 0.0f;
			if (patternX > 3)
			{
				patternX = 0;
			}
		}
	}
	else
	{
		// 立ち止まる
		patternX = 0;
		// 正面を向く
		timer += Time::DeltaTime();
		if (timer >= 1.0f)
		{
			playerImage = playerIdolImage;
		}
	}

	
	// ジャンプ
	if (CheckHitKey(KEY_INPUT_SPACE) || (input.Buttons[XINPUT_BUTTON_A]) || (input.Buttons[XINPUT_BUTTON_B]) )
	{
		if (prevJumpKey == false)
		{
			if (onGround == true)
			{
				//2マス分飛ぶ velocity:速度
				velocity = V0; //"初速"
				PlaySoundMem(jumpSound, DX_PLAYTYPE_BACK); // ジャンプ音の再生
			}
		}
		prevJumpKey = true;
	}
	else
	{
		prevJumpKey = false;
	}

	// 重力
	position.y += velocity; //座標には速度を足す
	velocity += Gravity;	//下向きの力　速度には重力を足す
	onGround = false;


	// 下に壁があるか調べる
	if (velocity >= 0)// velocity:速度
	{
		int push = s->IsWallDown(position + VECTOR2(0, 60 + collisionDown)); //一個下を見る一個下を見るので60
		if (push > 0)	//地面に触れたので
		{
			velocity = 0;			//地面に触ったら速度を0に
			position.y -= push - 1; //地面の上に押し返す	1個下を見るのでpush-1
			onGround = true;		//接地してる
		}
		push = s->IsWallDown(position + VECTOR2(29, 60 + collisionDown));	 //一個下を見る一個下を見るので60
		if (push > 0)	//地面に触れたので
		{
			velocity = 0;			//地面に触ったら速度を0に
			position.y -= push - 1; //地面の上に押し返す	1個下を見るのでpush-1
			onGround = true;		//接地してる
		}
		if (abs(velocity - Gravity) < DBL_EPSILON)
		{
			onGround = true;
		}
	}
	// 上に壁があるか調べる
	else
	{
		int push = s->IsWallUp(position + VECTOR2(0, 0 + collisionDown));
		if (push > 0)
		{
			velocity = 0.0f;
			position.y += push;
		}
		push = s->IsWallUp(position + VECTOR2(29, 0 + collisionDown));
		if (push > 0)
		{
			velocity = 0.0f;
			position.y += push;
		}
	}
	
	//プレイヤーをプレイエリアに閉じ込める
	if (position.x <= CHIP_SIZE * 8)
	{
		position.x = CHIP_SIZE * 8;
	}
	if (position.x >= (CHIP_SIZE * 8) + (CHIP_SIZE * 24) - 30 )
	{
		position.x = (CHIP_SIZE * 8) + (CHIP_SIZE * 24) - 30;
	}

	////プレイヤーに合わせてスクロール(上方向)
	//if (position.y - s->scroll < (CHIP_SIZE * 15) ) //プレイヤーのY座標が〇マス以上(仮)
	//{
	//	//s->scroll = position.y + collisionDown - CHIP_SIZE * 15; //スクロール速度をプレイヤーに合わせる
	//	s->scroll = position.y +9 - CHIP_SIZE * 15; //スクロール速度をプレイヤーに合わせる
	//}
	if ((position.y - s->scroll <= 240) && (onGround))
	{
		s->scroll -= 240;
	}

	//画面外に出たら死亡
	if (position.y - outOfScreen >= Screen::HEIGHT + s->scroll)
	{
		PlaySoundMem(fallSound, DX_PLAYTYPE_NORMAL); // 落下SE再生
		finished = true;
	}

	//ゴールした
	if (!goaled && s->IsGoal(position + VECTOR2(15, 25 + collisionDown))) //ゴールは左上でなく中心で（右に15,下に30ずれる）
	{
		Instantiate<GoalText>();
		goaled = true;
	}
	
	// プレイヤー現在高さ = ２点の差 
	playerHeight += prePlayerY - position.y;

	//最高到達点の更新
	if (onGround)
	{
		if (playerHeight/30 >= playerBestHeight/30)
		{
			playerBestHeight = playerHeight/30;
		}
	}
}

void Player::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

	if (playerImage == playerIdolImage) // 正面
	{
		DrawGraph(position.x-7.5, position.y - s->scroll, playerImage, TRUE);
	}
	if (playerImage == playerAnimImage) // 左右
	{
		DrawRectGraph(position.x, position.y - s->scroll, patternX * 30, patternY * 69, 30, 69, playerImage, TRUE);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}