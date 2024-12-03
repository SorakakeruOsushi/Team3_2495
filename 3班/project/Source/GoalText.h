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

	float timer;
	float alpha;

	float resultTime;
	float resultHeight;

	int goalBGImage; // �S�[���w�i�摜

	int goalVoice;
};
