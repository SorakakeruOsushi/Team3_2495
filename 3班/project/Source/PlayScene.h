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

	XINPUT_STATE input; //PAD����p�ϐ�

	float playTime;		//�v���C����

	int playMode; //�v���C���[�h
	
	//bool IsPause; // ���f

	float height;	 //����
	float bestHeight; //�ō��̍���

	Stage* s;
	Player* p;
	FinishText* f;
	GoalText* g;
	BestTime* bestTime;  // �ō����_�Ǘ�GameObject

	void CheckBestTime(); // �ō����_�̍X�V�m�F
};