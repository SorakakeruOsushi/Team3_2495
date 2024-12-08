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
	int finishTextImage;	   // �摜�uFINISH!�v�̕����摜
	int gameClearTextImage;	   // �摜�uGAME CLEAR!�v�̕����摜
	int titleBackKeyTextImage; // �摜�u�X�y�[�X�L�[�������ďI���v�̕����摜
	int thanksTextImage;	   // �摜�uThank You For Playing!�v�̕����摜
	int bannerImage;		   // �摜 �o�i�[
	int goalVoice;			   // ���� �Q�[���N���A

	float timer;
	float alpha;
	float bannerSlide;

	float resultTime;
	float resultHeight;
};
