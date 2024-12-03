#pragma once
#include "../Library/SceneBase.h"
#include "Stage.h"
#include "GoalText.h"
#include "FinishText.h"
#include "GoalText.h"
#include "BestTime.h" 


class PlayScene : public SceneBase
{
public:
	PlayScene();
	~PlayScene();
	void Update() override;
	void Draw() override;

	int titleBackVoice;
	int changeModeVoice;
	int gameBGM;

	//int h10Voice;

	float playTime;		//プレイ時間

	int playMode;
	//std::string playMode; //プレイモード

	float height;	 //高さ
	float bestHeight; //最高の高さ

	Stage* s;
	Player* p;
	FinishText* f;
	GoalText* g;
	BestTime* bestTime;  // 最高得点管理GameObject

	void CheckBestTime();       // 最高得点の更新確認 
};