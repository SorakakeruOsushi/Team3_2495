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
	bool isButtonDown;	// �v���C���[�h�؂�ւ��ŁA�{�^���̉������񂾎��̓��͂����̂Ɏg���܂�

	int ladyTextImage; // �摜�u���f�B�c�v
	int goTextImage;   // �摜�u�S�[�I�v

	int stageTextImage;     // �摜 [�Œ�\���������P���̉摜�ɂ܂Ƃ߂�]
	int nextTextImage;		// �摜�uNEXT�v
	int modeChangeTextImage;// �摜�uCHANGE:[C]KEY�v
	int heightTextImage;	// �摜�uHEIGHT�v
	int scoreTextImage;		// �摜�uSCORE�v
	int timeTextImage;		// �摜�uTIME�v
	int bestScoreTextImage;	// �摜�uBEST SCORE�v
	int bestTimeTextImage;	// �摜�uBEST TIME�v

	int playModeTextImage;  // �摜 (���݂̃v���C���[�h)
	int tetraModeTextImage; // �摜�uTETRA�v
	int blockModeTextImage; // �摜�uBLOCK�v
	int playModeBGImage;    // �摜 (���݂̃v���C���[�h)�v���C�G���A�w�i�摜
	int tetraModeBGImage;   // �摜 TETRA���[�h�̃v���C�G���A�w�i�摜
	int blockModeBGImage;   // �摜 BLOCK���[�h�̃v���C�G���A�w�i�摜

	int gameBGImage; // �摜 �Q�[���w�i
	int changeBGheight;
		int hBGImageI;    // �摜 �w�i1
		int hBGImageII;   // �摜 �w�i2
		int hBGImageIII;  // �摜 �w�i3

	int titleBackVoice;		// ���� [T]�^�C�g���ɖ߂�Ƃ�
	int changeModeVoice;	// ���� [C]�v���C���[�h�ύX

	float playTime;	  //�v���C����
	float height;	  // ����
	float bestHeight; // �ō��̍���

	Stage* s;			// �}�b�v
	Player* p;			// �v���C���[
	FinishText* f;		// �Q�[���I�[�o�[���o�\��
	GoalText* g;		// �S�[�����o�\��
	BestTime* bestTime; // �ő��N���A�^�C���X�V
	PlayMode* pm;		// ���샂�[�h�؂�ւ�(TETRA/BLOCK)

	void CheckBestTime();  // �x�X�g�^�C���̍X�V�m�F
	void CheckBestScore(); // �x�X�g�X�R�A�̍X�V�m�F
};