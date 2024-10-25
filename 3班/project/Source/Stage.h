#pragma once
#include "../Library/gameObject.h"
#include "Vector2.h"

class Stage : public GameObject 
{
public:
	Stage();
	~Stage();
	void Draw() override;
};

