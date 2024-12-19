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
	int thanksTextImage;	   // �摜�uThank You For Playing!�v
	int bannerImage;		   // �摜 �o�i�[
	int newRecordTextImage;    // �摜�u�V�L�^�v
	int goalVoice;			   // ���� �Q�[���N���A

	float timer;
	float alpha;
	float bannerSlide;

	float resultTime;
	float resultHeight;
};
