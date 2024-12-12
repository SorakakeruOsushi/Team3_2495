#include "Coin.h"
#include "Player.h"
#include "Stage.h"

Coin::Coin()
{
	//コンストラクタで絵をロード
	coinImage = LoadGraph("data/image/Xgoal.png");
	got = false;

	s = FindGameObject<Stage>();
	p = FindGameObject<Player>();
}

Coin::~Coin()
{
	DeleteGraph(coinImage);
}

void Coin::Update()
{
	//取られたら
	if (got)
	{
		p->gotCoin += 1;

		position.y += v; //浮遊感与えちゃったか…
		v += 9.8f / 60;  // 重力/60フレーム

		counter -= 1;
		if (counter == 0)
		{
			//取得
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
		got = true;	  //取られた！
		counter = 20; //死へのカウンター２０フレーム
		v = -2.5;	  //跳ねる力(上方向なので「-」符号)
	}
}

void Coin::Draw()
{
	DrawGraph(position.x - s->scroll, position.y, coinImage, TRUE);
}


//放物線（二次方程式）　
//[数学]　y = ax ^ 2 + bx + c;	　		←まぁ、使いませんケド！
//[物理]　v = v0 + at／v = v0 + gt　	←ｖ:速 = v0:初速 + gt:初速　ｔ:時間
//[プログラム]　x += v; v += g;