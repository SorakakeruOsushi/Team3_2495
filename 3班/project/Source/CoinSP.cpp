#include "CoinSP.h"
#include <cassert>
#include "Player.h"
#include "Stage.h"
#include "Time.h"

CoinSP::CoinSP()
{
	//コンストラクタで絵をロード
	coinSPImage = LoadGraph("data/image/CoinSP.png");			  // 画像 コイン
	assert(coinSPImage > 0);
	coinSPSound = LoadSoundMem("data/sound/GameSE/ビックコイン(5).mp3"); // 音 コイン取得
	assert(coinSPSound > 0);

	patternX = 0;
	animTimer = 0.0f;

	position.x = 0.0f;
	position.y = 0.0f;

	SetDrawOrder(6); //描画順

	got = false;
	CoinDraw = true;

	destroyTimer = 0.0f;     //コイン表示タイマー
	destroyTimeLimit = 0.1f; //コイン表示時間
	v = 0.0f;

	destroyCountDown = 1.0f;

	s = FindGameObject<Stage>();
}

CoinSP::~CoinSP()
{
	DeleteGraph(coinSPImage);
	DeleteSoundMem(coinSPSound);
}

void CoinSP::Update()
{
	p = FindGameObject<Player>();

	// 回るアニメーション
	animTimer += Time::DeltaTime();
	if (animTimer >= 0.1f)
	{
		patternX += 1;
		animTimer = 0.0f;
		if (patternX >= 4)
		{
			patternX = 0;
		}
	}

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
				PlaySoundMem(coinSPSound, DX_PLAYTYPE_BACK);
				nowPlaySE = true;
				p->gotCoinSP += 1;
			}
			// 取得
			CoinDraw = false;
			destroyCountDownTimer();
		}
		return;			 //終わり！閉廷！以上！皆解散！
	}

	//当たり判定
	VECTOR2 playerPos = p->position;	  //playerPosにplayerのpositionを入れる
	//当たり判定："playerPos"と"position"が当たったら
	if (CircleHit(position, playerPos + VECTOR2(0, 0 + 9), 29) || CircleHit(position, playerPos + VECTOR2(0, 30 + 9), 29))
	{
		got = true;	      //取られた
		v = -2.5;//跳ねる力(上方向なので「-」符号)
	}
}

void CoinSP::Draw()
{
	if (CoinDraw)
	{
		DrawRectGraph(position.x, position.y - s->scroll, patternX * 30, 0, 30, 30, coinSPImage, TRUE);
		//DrawGraph(position.x, position.y - s->scroll, coinSPImage, TRUE);
	}
}

void CoinSP::destroyCountDownTimer()
{
	destroyCountDown -= Time::DeltaTime();

	if (destroyCountDown <= 0)
	{
		DestroyMe(); //コインの消失
	}
}
