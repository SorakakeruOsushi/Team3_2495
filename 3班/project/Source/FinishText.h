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
	int gameOverVoice;		   // ���� �Q�[���I�[�o�[

	float timer; // �\���^�C�}�[
	float alpha; // �s�����x

	float resultTime;	// �^�C������
	float resultHeight; // �X�R�A���ʁ@���O�����Ȃ���I
};
