#include "Block.h"
#include "Stage.h"
#include <cassert>


Block::Block()
{
	hImage = LoadGraph("data/image/Tmino.png");
	assert(hImage > 0);

	position.x = 400;
	position.y = 500;
}

Block::~Block()
{
	DeleteGraph(hImage);
}

void Block::Update()
{
}

void Block::Draw()
{
	DrawGraph(position.x, position.y, hImage, TRUE);
}
