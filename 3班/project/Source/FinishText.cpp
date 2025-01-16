#include "FinishText.h"
#include "../Library/time.h"
#include <cassert>

FinishText::FinishText()
{
	finishTextImage = LoadGraph("data/image/font/Finish.png");		   // �摜�uFINISH�v
		assert(finishTextImage > 0);
	gameOverTextImage = LoadGraph("data/image/font/GameOver.png");	   // �摜�uGAME OVER�v
		assert(gameOverTextImage > 0);
	titleBackKeyTextImage = LoadGraph("data/image/font/PushSpace.png");// �摜�uSPACE�ŏI���v
		assert(titleBackKeyTextImage > 0);

	heightTextImage = LoadGraph("data/image/font/���ʂɓ�������O�̃t�H���g����/Hight.png"); // �摜�uHEIGHT�v
		assert(heightTextImage > 0);
	scoreTextImage = LoadGraph("data/image/font/���ʂɓ�������O�̃t�H���g����/Score.png");  // �摜�uSCORE�v
		assert(scoreTextImage > 0);
	timeTextImage = LoadGraph("data/image/font/���ʂɓ�������O�̃t�H���g����/Time.png");    // �摜�uTIME�v
		assert(timeTextImage > 0);

	titleBackSound = LoadSoundMem("data/sound/���ʉ����{/voice/�u����������v.mp3"); // �� �^�C�g���ɖ߂�
		assert(titleBackSound > 0);
	gameOverSound = LoadSoundMem("data/sound/GameSE/�Q�[���I�[�o�[�Q.mp3");	 // �� �Q�[���I�[�o�[SE
		assert(gameOverSound > 0);
	PlaySoundMem(gameOverSound, DX_PLAYTYPE_BACK); // �ߖ{�C�X�Đ�

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

	DeleteGraph(heightTextImage);
	DeleteGraph(scoreTextImage);
	DeleteGraph(timeTextImage);

	DeleteSoundMem(titleBackSound);
	DeleteSoundMem(gameOverSound);
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
			// �T�E���h���I������܂ő҂� 
			PlaySoundMem(titleBackSound, DX_PLAYTYPE_NORMAL);
			SceneManager::ChangeScene("TITLE");
		}
	}

	//alpha�l ����
	if (timer >= 0.3f)
	{
		alpha += 3.0f;
		if (alpha >= 170)
		{
			alpha = 170;
		}
	}
}

void FinishText::Draw()
{
	//�uFINISH!�v�\��
	DrawGraph(0, 0, finishTextImage, TRUE);
	// �Ó]
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha); //���߂���
	DrawBox(0, 0, 1280, 720, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);   //���߂��Ȃ�

	//�uGAME OVER!�v�\��
	if (timer >= 0.3f) 
	{
		DrawGraph(0, 0, gameOverTextImage, TRUE);
	}
	SetFontSize(80);
	if (timer >= 0.5f)
	{
		// ���B�����\��
		DrawGraph(326, 300, heightTextImage, TRUE);
		DrawFormatString(615, 300, GetColor(255, 255, 255), "%3.0f", fabs(resultHeight));
	}
	if (timer >= 0.75f)
	{
		// �X�R�A�\��
		DrawGraph(340, 400, scoreTextImage, TRUE);
		DrawFormatString(615, 400, GetColor(255, 255, 255), "%3.0d", resultScore);
	}
	if (timer >= 1.0f)
	{
		// �^�C���\��
		DrawGraph(421, 500, timeTextImage, TRUE);
		DrawFormatString(615, 500, GetColor(255, 255, 255), "%6.2f", resultTime);
	}

	// "�X�y�[�X�L�[�ŏI��"
	if (IsDraw)
	{
		//�u�X�y�[�X�L�[�������ďI���v�\��
		DrawGraph(450, 600, titleBackKeyTextImage, TRUE);
		SetFontSize(25);
		DrawString(450, 650, "test[0]�Ń��g���C", GetColor(255, 0, 0), TRUE);
	}

}
