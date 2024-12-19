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

	XINPUT_STATE input; //PADμpΟ

	int goalBGImage;		   // ζ S[wiζ
	int finishTextImage;	   // ζuFINISH!v
	int gameClearTextImage;	   // ζuGAME CLEAR!v
	int titleBackKeyTextImage; // ζuXy[XL[π΅ΔIΉv
	int thanksTextImage;	   // ζuThank You For Playing!v
	int bannerImage;		   // ζ oi[
	int newRecordTextImage;    // ζuVL^v
	int goalVoice;			   // ΉΊ Q[NA

	float timer;
	float alpha;
	float bannerSlide;

	float resultTime;
	float resultHeight;
};
