#include "FinishText.h"
#include "../Library/time.h"
#include <cassert>

FinishText::FinishText()
{
	gameOverVoice = LoadSoundMem("data/sound/���ʉ����{/voice/�u�Ђ�[���I�v.mp3");
		assert(gameOverVoice > 0);
	PlaySoundMem(gameOverVoice, DX_PLAYTYPE_BACK); // �ߖ{�C�X

	timer = 0.0f;
	alpha = 0.0f;
}

FinishText::~FinishText()
{
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

	if (timer >= 0.3f)
	{
		alpha += 3.0f;
		if (alpha >= 150)
		{
			alpha = 150;
		}
	}
}

void FinishText::Draw()
{
	//�u�Q�[���I�[�o�[�I�v�I�ȕ\�����s��"
	SetFontSize(100);
	DrawString(310, 200, "����ˁ`��", GetColor(255, 255, 127)); //(x,y,������,�F)

	
	if (timer >= 0.3f) //�P�b�������炸���ƕ\��
	{
		//(x,y,�F,������,�ς�镶����)   �u%d�v��u��������
		//�u%6d�v �F�U���p�ӂ���@�iif���ŃJ���X�g������΃I�[�o�[���Ȃ��j
		//�u%06d�v�F�U���p�ӂ���@�󔒂��O�Ŗ��߂�
		//�u%06d%%�v�F�u�����v�\���o����

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
}
