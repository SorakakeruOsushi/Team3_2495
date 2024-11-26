#pragma once
#include "../Library/SceneBase.h"
#include "Stage.h"
#include "GoalText.h"
#include "FinishText.h"
#include "GoalText.h"

class PlayScene : public SceneBase
{
public:
	PlayScene();
	~PlayScene();
	void Update() override;
	void Draw() override;

	float playTime;		//プレイ時間
	float bestTime;		//ベストクリア時間

	float score;	 //高さ
	float highScore; //最高の高さ

	Stage* s;
	Player* p;
	FinishText* f;
	GoalText* g;
};