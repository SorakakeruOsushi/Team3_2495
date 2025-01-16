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

	int readyGoTextImage; // 
	int readyTextImage;   // �摜�u���f�B�c�v
	int goTextImage;      // �摜�u�S�[�I�v

	int stageTextImage;     // �摜 [�Œ�\���������P���̉摜�ɂ܂Ƃ߂�]
	int resetTextImage;		// �摜�uRESET[0]KEY�v

	int playModeTextImage;  // �摜 (���݂̃v���C���[�h)
	int tetraModeTextImage; // �摜�uTETRA�v
	int blockModeTextImage; // �摜�uBLOCK�v
	int playModeBGImage;    // �摜 (���݂̃v���C���[�h)�v���C�G���A�w�i�摜
	int tetraModeBGImage;   // �摜 TETRA���[�h�̃v���C�G���A�w�i�摜
	int blockModeBGImage;   // �摜 BLOCK���[�h�̃v���C�G���A�w�i�摜

	int gameBGImage; // �摜 �Q�[���w�i
	//int changeBGheight;
	//	int hBGImageI;    // �摜 �w�i1
	//	int hBGImageII;   // �摜 �w�i2
	//	int hBGImageIII;  // �摜 �w�i3

	int titleBackSound; // �� [T]�^�C�g���ɖ߂�Ƃ�
	int startSound;		// �� �Q�[���J�n
	int resetSound;		// �� [0]���Z�b�g��
	int modeChangeSound;// �� [C]���[�h�ύX��

	float playTime;	  //�v���C����
	float height;	  // ����
	float bestHeight; // �ō��̍���

	float startCountDown;

	Stage* s;			// �}�b�v
	Player* p;			// �v���C���[
	FinishText* f;		// �Q�[���I�[�o�[���o�\��
	GoalText* g;		// �S�[�����o�\��
	BestTime* bestTime; // �ő��N���A�^�C���X�V
	PlayMode* pm;		// ���샂�[�h�؂�ւ�(TETRA/BLOCK)

	void CheckBestTime();  // �x�X�g�^�C���̍X�V�m�F
	void CheckBestScore(); // �x�X�g�X�R�A�̍X�V�m�F
};