#include "GoalText.h"
#include "../Library/time.h"
#include <cassert>

GoalText::GoalText()
{
	goalBGImage = LoadGraph("data/image/Goal.JPG");						  // �摜 �S�[���w�i�摜
		assert(goalBGImage > 0);
	finishTextImage = LoadGraph("data/image/font/Finish.png");		      // �摜�uFINISH�v
		assert(finishTextImage > 0);
	gameClearTextImage = LoadGraph("data/image/font/Clear.png");	      // �摜�uGAME CLEAR�v
		assert(gameClearTextImage > 0);
	newRecordTextImage = LoadGraph("data/image/font/NewRecord.png");	  // �摜�uNEW RECORD!�v
		assert(newRecordTextImage > 0);
	thanksTextImage = LoadGraph("data/image/XA1/xThankYouForPlaying.png");// �摜�u�v���C���Ă���Ă��肪�ƃi�X�I�v
		assert(thanksTextImage > 0);
	titleBackKeyTextImage = LoadGraph("data/image/XA1/x�X�y�[�X�L�[�������ďI��.png"); // �摜�uTITLE�ɖ߂�v
		assert(titleBackKeyTextImage > 0);

	goalVoice = LoadSoundMem("data/sound/���ʉ����{/voice/�u�ς�ς��ρ[��I�v.mp3");
		assert(goalVoice > 0);
	PlaySoundMem(goalVoice, DX_PLAYTYPE_BACK); // �S�[���{�C�X�Đ�

	timer = 0.0f;
	alpha = 0.0f;

	DrawKeyTimer = 0.0f;
	IsDraw = false;

	IsNewBestScore = false;
	IsNewBestTime = false;

	resultScore = 0;   // �X�R�A����
	resultTime = 0.0f; // �^�C������
}

GoalText::~GoalText()
{
	DeleteGraph(goalBGImage);
	DeleteGraph(finishTextImage);
	DeleteGraph(gameClearTextImage);
	DeleteGraph(newRecordTextImage);
	DeleteGraph(titleBackKeyTextImage);
	DeleteGraph(thanksTextImage);
	DeleteSoundMem(goalVoice);
}

void GoalText::Update()
{
	//�p�b�h�p�֐�(���t���[���Ăяo��)
	GetJoypadXInputState(DX_INPUT_PAD1, &input);

	//Time::DeltaTime();�F�b�ő���邽�߃��j�^�[���\�ɍ��E����Ȃ�
	timer += Time::DeltaTime();

	if (timer >= 6.0f)
	{
		//�u�^�C�g���ɖ߂�v�\���ؑ�
		DrawKeyTimer += Time::DeltaTime();
		if (DrawKeyTimer >= 0.5f)
		{
			IsDraw = !IsDraw;
			DrawKeyTimer = 0.0f;
		}

		if ((CheckHitKey(KEY_INPUT_SPACE)) || (input.Buttons[XINPUT_BUTTON_A]) || (input.Buttons[XINPUT_BUTTON_B]))
		{
			SceneManager::ChangeScene("TITLE");
		}
	}

	//alpha�l ����
	if (timer >= 0.3f)
	{
		alpha += 1.0f;
		if (alpha >= 255)
		{
			alpha = 255;
		}
	}
}

void GoalText::Draw()
{
	//�uFINISH!�v�\��
	DrawGraph(340, 280, finishTextImage, TRUE);
	// �S�[���摜 �\��
	if (timer >= 0.3f)
	{
		// ���U���g��ʔw�i
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha); //	�A���t�@�u�����f�B���O
		DrawGraph(0, 0, goalBGImage, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	 //���߂��Ȃ�
	}

	//�uGAME CLEAR!�v�\��
	if (timer >= 3.0f)
	{
		DrawGraph(255, 160, gameClearTextImage, TRUE);
	}
	SetFontSize(30);
	if (timer >= 4.0f)
	{
		//����(�Œ�\��)
		DrawString(500, 300, "50/50", GetColor(255, 255, 255)); // �n���{�e
	}
	if (timer >= 4.5f)
	{
		// �X�R�A�\��
		DrawFormatString(500, 350, GetColor(255, 255, 255), "%3.0d", resultScore);
		if (IsNewBestScore)
		{
			DrawGraph(600, 350, newRecordTextImage, TRUE);
		}

	}
	//�^�C��
	if (timer >= 5.0f)
	{
		// �^�C���\��
		DrawFormatString(500, 400, GetColor(255, 255, 255), "%4.2f", resultTime);
		if (IsNewBestTime)
		{
			DrawGraph(600, 400, newRecordTextImage, TRUE);
		}
	}

	if (timer >= 5.3f)
	{
		//�uThank You For Playing!�v�\��
		DrawGraph(275, 500, thanksTextImage, TRUE);
	}

	// "�X�y�[�X�L�[�ŏI��"
	if (IsDraw)
	{
		//�u�X�y�[�X�L�[�������ďI���v�\��
		DrawGraph(450, 600, titleBackKeyTextImage, TRUE);
	}
}
