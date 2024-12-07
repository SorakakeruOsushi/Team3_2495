#pragma once
#include "../Library/SceneBase.h"
#include "Stage.h"
#include "GoalText.h"
#include "FinishText.h"
#include "BestTime.h" 

#include "PlayMode.h"


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

	XINPUT_STATE input; //PAD操作用変数

	float playTime;		//プレイ時間

	float height;	 //高さ
	float bestHeight; //最高の高さ()

	Stage* s;			// マップ
	Player* p;			// プレイヤー
	FinishText* f;		// ゲームオーバー演出表示
	GoalText* g;		// ゴール演出表示
	BestTime* bestTime; // 最速クリアタイム更新
	PlayMode* pm;		// 操作モード切り替え(TETRA/BLOCK)

	void CheckBestTime(); // 最高得点の更新確認
};