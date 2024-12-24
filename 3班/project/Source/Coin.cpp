#include "Coin.h"
#include <cassert>
#include "Player.h"
#include "Stage.h"
#include "Time.h"

Coin::Coin()
{
	//コンストラクタで絵をロード
	coinImage = LoadGraph("data/image/Coin.PNG");				 // 画像 コイン画像
		assert(coinImage > 0);
	coinSE = LoadSoundMem("data/sound/効果音ラボ/ボヨン.mp3"); // SE コイン取得音
		assert(coinSE > 0);
	
	got = false;
	CoinDraw = true;

	destroyTimer = 0.0f;     //コイン表示タイマー
	destroyTimeLimit = 0.1f; //コイン表示時間

	s = FindGameObject<Stage>();
}

Coin::~Coin()
{
	DeleteGraph(coinImage);
	DeleteSoundMem(coinSE);
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
			// 取得SE　なったりならなかったり
			PlaySoundMem(coinSE, DX_PLAYTYPE_BACK);
			// 取得
			p->gotCoin += 1;
			DestroyMe(); //死ぬしかないじゃない！
		}
		return;			 //終わり！閉廷！以上！皆解散！
	}

	//取られる前
	//当たり判定
   	VECTOR2 playerPos = p->position;	  //playerPosにplayerのpositionを入れる

	//当たり判定："playerPos"と"position"が当たったら
	if (CircleHit(position, playerPos, 30))
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