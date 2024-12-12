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

	XINPUT_STATE input; // PAD����p�ϐ�

	int nextTextImage;		// �摜�uNEXT�v�̕����摜
	int modeChangeTextImage;// �摜�uCHANGE:[C]KEY�v�̕����摜

	int playModeTextImage;  // �摜�u(���݂̃v���C���[�h)�v�̕����摜
	int playModeBGImage;	// �摜 �u(���݂̃v���C���[�h)�v�v���C�G���A�w�i�摜

	int gameBGImage;
	int changeBGheight;

	int hBGImageI;    // �摜 �w�i1
	int hBGImageII;   // �摜 �w�i2
	int hBGImageIII;  // �摜 �w�i3

	int titleBackVoice;		// ���� [T]�^�C�g���ɖ߂�Ƃ�
	int changeModeVoice;	// ���� [C]�v���C���[�h�ύX
	int gameBGM;			// ���y BGM

	float playTime;		//�v���C����

	float height;	  //����
	float bestHeight; //�ō��̍���()

	Stage* s;			// �}�b�v
	Player* p;			// �v���C���[
	FinishText* f;		// �Q�[���I�[�o�[���o�\��
	GoalText* g;		// �S�[�����o�\��
	BestTime* bestTime; // �ő��N���A�^�C���X�V
	PlayMode* pm;		// ���샂�[�h�؂�ւ�(TETRA/BLOCK)

	void CheckBestTime(); // �x�X�g�^�C���̍X�V�m�F
	void CheckBestScore(); // �x�X�g�X�R�A�̍X�V�m�F
};