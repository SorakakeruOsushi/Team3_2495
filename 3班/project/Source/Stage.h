#pragma once
#include "../Library/gameObject.h"
#include "Vector2.h"

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

	int emptyImage; // 画像 マス目
	int blockImage; // 画像 灰ブロック
};
