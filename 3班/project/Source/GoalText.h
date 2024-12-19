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

	XINPUT_STATE input; //PAD操作用変数

	int goalBGImage;		   // 画像 ゴール背景画像
	int finishTextImage;	   // 画像「FINISH!」
	int gameClearTextImage;	   // 画像「GAME CLEAR!」
	int titleBackKeyTextImage; // 画像「スペースキーを押して終了」
	int thanksTextImage;	   // 画像「Thank You For Playing!」
	int bannerImage;		   // 画像 バナー
	int newRecordTextImage;    // 画像「新記録」
	int goalVoice;			   // 音声 ゲームクリア

	float timer;
	float alpha;
	float bannerSlide;

	float resultTime;
	float resultHeight;
};
