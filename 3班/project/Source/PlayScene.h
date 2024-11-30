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

	int titleBackVoice;
	int changeModeVoice;
	int gameBGM;

	//int h10Voice;

	float playTime;		//�v���C����
	float bestTime;		//�x�X�g�N���A����

	//std::string playMode; //�v���C���[�h

	float score;	 //����
	float highScore; //�ō��̍���

	Stage* s;
	Player* p;
	FinishText* f;
	GoalText* g;
};