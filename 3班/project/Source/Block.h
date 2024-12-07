#pragma once
#include "../Library/GameObject.h"
#include "Vector2.h"


class Block :
    public GameObject
{
public:
	Block();
	~Block();
	void Update() override;
	void Draw() override;


	int hImage;
	VECTOR2 position;

	float blockSize;

	float downBlock;
	float nextBlock;

	float time;
	float counter;
	float quickCount;//Sを押している時にcounterを増やす倍率

	bool isMovedLeft;//右に移動したか
	bool isMovedRight;//左に移動したか
};

