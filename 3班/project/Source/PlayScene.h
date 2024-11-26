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

	float playTime;		//�v���C����
	float bestTime;		//�x�X�g�N���A����

	float score;	 //����
	float highScore; //�ō��̍���

	Stage* s;
	Player* p;
	FinishText* f;
	GoalText* g;
};