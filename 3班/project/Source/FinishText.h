#pragma once
//FinishText.h
#include "../Library/gameObject.h"
#include "../Library/Utility.h" 

class FinishText :public GameObject
{
public:
	FinishText();
	~FinishText();
	void Update() override;
	void Draw() override;

	XINPUT_STATE input; //PAD����p�ϐ�

	int finishTextImage;	   // �摜�uFINISH!�v
	int gameOverTextImage;	   // �摜�uGAME OVER!�v
	int titleBackKeyTextImage; // �摜�u�X�y�[�X�L�[�������ďI���v
	int gameOverSound;		   // �� �Q�[���I�[�o�[
	int titleBackSound;		   // �� �^�C�g���ɖ߂�

	int heightTextImage;	// �摜�uHEIGHT�v
	int scoreTextImage;		// �摜�uSCORE�v
	int timeTextImage;		// �摜�uTIME�v

	float timer; // �\���^�C�}�[
	float alpha; // �s�����x

	float DrawKeyTimer;		// �\���^�C�}�[�u�^�C�g���ɖ߂�v
	bool IsDraw;			// �`��

	float resultHeight; // ���B����
	float resultScore;	// �X�R�A���� 
	float resultTime;	// �^�C������

};
