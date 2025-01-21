#include "Coin.h"
#include <cassert>
#include "Player.h"
#include "Stage.h"
#include "Time.h"

Coin::Coin()
{
	//コンストラクタで絵をロード
	coinImage = LoadGraph("data/image/Coin.PNG");			  // 画像 コイン
		assert(coinImage > 0);
	coinSound = LoadSoundMem("data/sound/GameSE/コイン.mp3"); // 音 コイン取得
		assert(coinSound > 0);
	
	SetDrawOrder(6);

	got = false;
	CoinDraw = true;

	destroyTimer = 0.0f;     //コイン表示タイマー
	destroyTimeLimit = 0.1f; //コイン表示時間

	destroyCountDown = 1.0f;

	s = FindGameObject<Stage>();
}

Coin::~Coin()
{
	DeleteGraph(coinImage);
	DeleteSoundMem(coinSound);
}

void Coin::Update()
{
	p = FindGameObject<Player>();

	//取られたら
	if (got)
	{
		position.y += v;//浮遊感与えちゃったか…
		v += 9.8f / 60; // 重力/60フレーム

		destroyTimer += Time::DeltaTime();
		if (destroyTimer >= destroyTimeLimit)
		{
			if (!nowPlaySE)
			{
				PlaySoundMem(coinSound, DX_PLAYTYPE_BACK);
				nowPlaySE = true;
			}
			// 取得
			CoinDraw = false;
			destroyCountDownTimer();
		}
		return;			 //終わり！閉廷！以上！皆解散！
	}

	//取られる前
	//当たり判定
   	VECTOR2 playerPos = p->position;	  //playerPosにplayerのpositionを入れる

	//当たり判定："playerPos"と"position"が当たったら
	if (CircleHit(position, playerPos + VECTOR2(0, 0+9), 29) || CircleHit(position, playerPos + VECTOR2(0, 30+9), 29))
	{
		got = true;	      //取られた
		v = -2.5;//跳ねる力(上方向なので「-」符号)
	}
}

void Coin::Draw()
{
	if (CoinDraw)
	{
		DrawGraph(position.x, position.y - s->scroll, coinImage, TRUE);
	}
}

void Coin::destroyCountDownTimer()
{
	destroyCountDown -= Time::DeltaTime();

	if (destroyCountDown <= 0)
	{
		p->gotCoin += 1;
		DestroyMe(); //コインの消失
	}
}
