#pragma once
//FinishText.h
#include "../Library/gameObject.h"

class FinishText :public GameObject
{
public:
	FinishText();
	~FinishText();
	void Update() override;
	void Draw() override;

	float timer;
};
