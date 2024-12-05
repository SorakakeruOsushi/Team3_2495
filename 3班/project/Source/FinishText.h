#pragma once
//FinishText.h
#include "../Library/gameObject.h"
#include "../Library/Utility.h" 

class FinishText :public GameObject
{
public:
	FinishText();
	~FinishText();
	void Update() override;
	void Draw() override;

	XINPUT_STATE input; //PAD‘€ì—p•Ï”

	float timer;

	float resultTime;
	float resultHeight;

	int gameOverVoice;

	float alpha;
};
