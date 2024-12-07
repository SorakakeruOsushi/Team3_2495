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

	XINPUT_STATE input; //PAD����p�ϐ�

	float playTime;		//�v���C����

	float height;	 //����
	float bestHeight; //�ō��̍���()

	Stage* s;			// �}�b�v
	Player* p;			// �v���C���[
	FinishText* f;		// �Q�[���I�[�o�[���o�\��
	GoalText* g;		// �S�[�����o�\��
	BestTime* bestTime; // �ő��N���A�^�C���X�V
	PlayMode* pm;		// ���샂�[�h�؂�ւ�(TETRA/BLOCK)

	void CheckBestTime(); // �ō����_�̍X�V�m�F
};