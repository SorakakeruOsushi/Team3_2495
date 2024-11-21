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
};

