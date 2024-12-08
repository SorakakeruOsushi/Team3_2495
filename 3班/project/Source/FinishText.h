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

	int gameOverVoice;
	int finishTextImage;
	int gameOverTextImage;
	int bannerImage;
	int titleBackKeyTextImage;
	//int playerSDcryImage;

	float timer;
	float alpha;
	float bannerSlide;

	float resultTime;
	float resultHeight;
};
