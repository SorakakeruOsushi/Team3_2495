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

	int finishTextImage;	   // �摜�uFINISH!�v�̕����摜
	int gameOverTextImage;	   // �摜�uGAME OVER!�v�̕����摜
	int titleBackKeyTextImage; // �摜�u�X�y�[�X�L�[�������ďI���v�̕����摜
	int bannerImage;		   // �摜 �o�i�[
	int gameOverVoice;		   // ���� �Q�[���I�[�o�[

	float timer;
	float alpha;
	float bannerSlide;

	float resultTime;	// �^�C������
	float resultHeight; // �X�R�A����
};
