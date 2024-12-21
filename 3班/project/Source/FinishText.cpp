#include "FinishText.h"
#include "../Library/time.h"
#include <cassert>

FinishText::FinishText()
{
	finishTextImage = LoadGraph("data/image/font/Finish.png");						  // �摜�uFINISH�v
		assert(finishTextImage > 0);
	gameOverTextImage = LoadGraph("data/image/font/GameOver.png");					  // �摜�uGAME OVER�v
		assert(gameOverTextImage > 0);
	titleBackKeyTextImage = LoadGraph("data/image/XA1/x�X�y�[�X�L�[�������ďI��.png");// �摜�uSPACE�ŏI���v
		assert(titleBackKeyTextImage > 0);

	gameOverVoice = LoadSoundMem("data/sound/���ʉ����{/voice/�u�Ђ�[���I�v.mp3");	  // �����u(�ߖ�)�v
		assert(gameOverVoice > 0);
	PlaySoundMem(gameOverVoice, DX_PLAYTYPE_BACK); // �ߖ{�C�X�Đ�

	timer = 0.0f;
	alpha = 0.0f;

	DrawKeyTimer = 0.0f;
	IsDraw = false;

	resultHeight =0.0f; // ���B����
	resultScore = 0;	// �X�R�A���� 
	resultTime = 0.0f;	// �^�C������
}

FinishText::~FinishText()
{
	DeleteGraph(finishTextImage);
	DeleteGraph(gameOverTextImage);
	DeleteGraph(titleBackKeyTextImage);
	DeleteSoundMem(gameOverVoice);
}

void FinishText::Update()
{
	//�p�b�h�p�֐�(���t���[���Ăяo��)
	GetJoypadXInputState(DX_INPUT_PAD1, &input);

	//Time::DeltaTime();�F�b�ő���邽�߃��j�^�[���\�ɍ��E����Ȃ�
	timer += Time::DeltaTime();

	if (timer >= 1.5f)
	{
		//�u�^�C�g���ɖ߂�v�\���ؑ�
		DrawKeyTimer += Time::DeltaTime();
		if (DrawKeyTimer >= 0.5f)
		{
			IsDraw = !IsDraw;
			DrawKeyTimer = 0.0f;
		}

		if ( (CheckHitKey(KEY_INPUT_SPACE)) || (input.Buttons[XINPUT_BUTTON_A]) || (input.Buttons[XINPUT_BUTTON_B]) )
		{
			SceneManager::ChangeScene("TITLE");
		}
	}

	//alpha�l ����
	if (timer >= 0.3f)
	{
		alpha += 3.0f;
		if (alpha >= 125)
		{
			alpha = 125;
		}
	}
}

void FinishText::Draw()
{
	//�uFINISH!�v�\��
	DrawGraph(340, 280, finishTextImage, TRUE);
	// �Ó]
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha); //���߂���
	DrawBox(0, 0, 1280, 720, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //���߂��Ȃ�

	//�uGAME OVER!�v�\��
	if (timer >= 0.3f) 
	{
		DrawGraph(255, 260, gameOverTextImage, TRUE);
	}
	SetFontSize(30);
	if (timer >= 0.5f)
	{
		// ���B�����\��
		DrawFormatString(500, 450, GetColor(255, 255, 255), "������%3.0f", fabs(resultHeight));
		// �X�R�A�\��
		DrawFormatString(500, 480, GetColor(255, 255, 255), "������%3.0d", resultScore);
	}
	if (timer >= 1.0f)
	{
		// �^�C���\��
		DrawFormatString(500, 500, GetColor(255, 255, 255), "������%4.2f", resultTime);
	}

	// "�X�y�[�X�L�[�ŏI��"
	if (IsDraw)
	{
		//�u�X�y�[�X�L�[�������ďI���v�\��
		DrawGraph(450, 600, titleBackKeyTextImage, TRUE);
	}
}
