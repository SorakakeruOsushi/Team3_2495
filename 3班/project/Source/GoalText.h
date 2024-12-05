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

	XINPUT_STATE input; //PAD����p�ϐ�

	float timer;
	float alpha;

	float resultTime;
	float resultHeight;

	int goalBGImage; // �S�[���w�i�摜

	int goalVoice;
};
