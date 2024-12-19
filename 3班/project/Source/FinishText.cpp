#include "FinishText.h"
#include "../Library/time.h"
#include <cassert>

FinishText::FinishText()
{
	finishTextImage = LoadGraph("data/image/font/Finish.png");						  // �摜�uFINISH�v
		assert(finishTextImage > 0);
	gameOverTextImage = LoadGraph("data/image/font/GameOver.png");					  // �摜�uGAME OVER�v
		assert(gameOverTextImage > 0);
	bannerImage = LoadGraph("data/image/XA1/x�o�i�[1.png");
		assert(bannerImage > 0);
	titleBackKeyTextImage = LoadGraph("data/image/XA1/x�X�y�[�X�L�[�������ďI��.png");// �摜�uSPACE�ŏI���v
		assert(titleBackKeyTextImage > 0);

	gameOverVoice = LoadSoundMem("data/sound/���ʉ����{/voice/�u�Ђ�[���I�v.mp3");	  // �����u(�ߖ�)�v
		assert(gameOverVoice > 0);
	PlaySoundMem(gameOverVoice, DX_PLAYTYPE_BACK); // �ߖ{�C�X�Đ�

	timer = 0.0f;
	alpha = 0.0f;
	bannerSlide = -1280.0f;
}

FinishText::~FinishText()
{
	DeleteGraph(finishTextImage);
	DeleteGraph(gameOverTextImage);
	DeleteGraph(bannerImage);
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
	//�уX���C�h
	if (timer >= 1.5f)
	{
		bannerSlide +=30;
		if (bannerSlide >= 1280.0f)
		{
			bannerSlide = 1280.0f;
		}
	}
}

void FinishText::Draw()
{
	/*
	//�u�Q�[���I�[�o�[�I�v�I�ȕ\�����s��"
	SetFontSize(100);
	DrawString(310, 200, "����ˁ`��", GetColor(255, 255, 127)); //(x,y,������,�F)

	
	if (timer >= 0.3f) //�P�b�������炸���ƕ\��
	{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha); //���߂���
	DrawBox(0, 0, 1280, 720, GetColor(0,0,0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //���߂��Ȃ�

	DrawString(310, 200, "����ˁ`��", GetColor(255, 255, 127));
	}

	SetFontSize(50);
	if (timer >= 0.5f)
	{
		DrawFormatString(450, 350, GetColor(255, 255, 255), "SCORE:%3.0f", fabs(resultHeight));//�X�R�A�ɕς��A�����͎��̂�
	}
	if (timer >= 1.0f)
	{
		DrawFormatString(450, 450, GetColor(255, 255, 255), "TIME:%4.2f", resultTime);
	}
	// "�X�y�[�X�L�[�ŏI��"
	if (timer >= 1.5f)
	{
		DrawString(300, 600, "�X�y�[�X�L�[�������ďI�� ", GetColor(255, 255, 255));
	}
	*/

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
		// �X�R�A�\��
		DrawFormatString(500, 450, GetColor(255, 255, 255), "SCORE:%3.0f", fabs(resultHeight));//�X�R�A�ɕς��A�����͎��̂�
	}
	if (timer >= 1.0f)
	{
		// �^�C���\��
		DrawFormatString(500, 500, GetColor(255, 255, 255), "TIME:%4.2f", resultTime);
	}

	// "�X�y�[�X�L�[�ŏI��"
	if (timer >= 1.5f)
	{
		/* //�{�b�N�X
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255); //���߂���
		DrawBox(0, 600, bannerSlide, 650, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //���߂��Ȃ�
		*/
		//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		//DrawRectGraph(0, 600, 0,0, bannerSlide,50, bannerImage, TRUE);
		//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		if (timer >= 2.0f)
		{
			//�u�X�y�[�X�L�[�������ďI���v�\��
			DrawGraph(450, 600, titleBackKeyTextImage, TRUE);
		}
	}
}
