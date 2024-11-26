#pragma once
#include "../Library/gameObject.h"
#include "Vector2.h"
#include "Player.h"

class Stage : public GameObject
{
public:
	Stage();
	~Stage();
	void Draw() override;

	int IsWallRight(VECTOR2 pos);
	int IsWallLeft(VECTOR2 pos);
	int IsWallDown(VECTOR2 pos);
	int IsWallUp(VECTOR2 pos);

	bool IsGoal(VECTOR2 pos);

	Player* p;

	int emptyImage;  // 画像 マス目
	int blockImage;  // 画像 灰ブロック
	int goalImage;	 // 画像 ゴール(仮)

	int scroll;		//画面のスクロール
};
