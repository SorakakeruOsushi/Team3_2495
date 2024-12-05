#pragma once
//GoalText.h
#include "../Library/gameObject.h"
#include "../Library/Utility.h" 

class GoalText :public GameObject
{
public:
	GoalText();
	~GoalText();
	void Update() override;
	void Draw() override;

	XINPUT_STATE input; //PAD‘€ì—p•Ï”

	float timer;
	float alpha;

	float resultTime;
	float resultHeight;

	int goalBGImage; // ƒS[ƒ‹”wŒi‰æ‘œ

	int goalVoice;
};
