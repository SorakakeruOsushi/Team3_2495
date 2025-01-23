#pragma once
//GoalText.h
#include "../Library/gameObject.h"
#include "../Library/Utility.h" 

class GoalText :public GameObject
{
public:
	GoalText();
	~GoalText();
	void Update() override;
	void Draw() override;

	XINPUT_STATE input; //PAD����p�ϐ�

	int goalBGImage;		   // �摜 �S�[���w�i�摜
	int finishTextImage;	   // �摜�uFINISH!�v
	int gameClearTextImage;	   // �摜�uGAME CLEAR!�v
	int titleBackKeyTextImage; // �摜�u�X�y�[�X�L�[�������ďI���v
	//int thanksTextImage;	   // �摜�uThank You For Playing!�v
	int newRecordTextImage;    // �摜�u�V�L�^�v
	int goalSound;			   // �� �Q�[���N���A
	int titleBackSound;		   // �� �^�C�g���ɖ߂�

	int heightTextImage;	   // �摜�uHEIGHT�v
	int scoreTextImage;		   // �摜�uSCORE�v
	int timeTextImage;		   // �摜�uTIME�v

	float timer; // �\���^�C�}�[
	float alpha; // �s�����x

	float DrawKeyTimer;	 // �\���^�C�}�[�u�^�C�g���ɖ߂�v
	bool IsDraw;		 // �`��

	bool IsNewBestScore; // �ō��X�R�A�X�V
	bool IsNewBestTime;  // �ő��^�C���X�V

	float resultScore;  // �X�R�A����
	float resultTime; // �^�C������
};
