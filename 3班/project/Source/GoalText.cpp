#include "GoalText.h"
#include "../Library/time.h"
#include <cassert>

GoalText::GoalText()
{
	goalVoice = LoadSoundMem("data/sound/���ʉ����{/voice/�u�ς�ς��ρ[��I�v.mp3");
		assert(goalVoice > 0);
	PlaySoundMem(goalVoice, DX_PLAYTYPE_BACK); // �S�[���{�C�X

	timer = 0.0f;
}

GoalText::~GoalText()
{
}

void GoalText::Update()
{
	//Time::DeltaTime();�F�b�ő���邽�߃��j�^�[���\�ɍ��E����Ȃ�
	timer += Time::DeltaTime();

	if (timer >= 2.5f)
	{
		if (KeyUtility::CheckTrigger(KEY_INPUT_SPACE))
		{
			SceneManager::ChangeScene("TITLE");
		}
	}
}

void GoalText::Draw()
{

	//���݂̃t�H���g�T�C�Y
	int size = GetFontSize();

	//"Goal!"
	SetFontSize(100);
	DrawString(200, 200, "CLEAR! ", GetColor(255, 255, 127)); //(x,y,������,�F)

	if (timer >= 1.0f) //�P�b�������炸���ƕ\��
	{
		//(x,y,�F,������,�ς�镶����)   �u%d�v��u��������
		//�u%6d�v �F�U���p�ӂ���@�iif���ŃJ���X�g������΃I�[�o�[���Ȃ��j
		//�u%06d�v�F�U���p�ӂ���@�󔒂��O�Ŗ��߂�
		//�u%06d%%�v�F�u�����v�\���o����

		//(�ꉞ)�����A���ԁA�]����\��
		SetFontSize(25);
		DrawFormatString(200, 300, GetColor(255, 255, 255), "SCORE:%3.0f", fabs(resultHeight));
		DrawFormatString(200, 400, GetColor(255, 255, 255), "TIME:%4.2f", resultTime);
		if (timer >= 1.5f)
		{
			SetFontSize(40);
			//DrawFormatString(200, 500, GetColor(255, 255, 255), "�]��:%d",A�`E  );
		}
	}

	// "�X�y�[�X�L�[�ŏI��"
	if (timer >= 2.0f)
	{
		DrawString(200, 600, "�X�y�[�X�L�[�������ďI�� ", GetColor(255, 255, 255));
	}

	//���̃t�H���g�T�C�Y�ɖ߂�
	SetFontSize(size);
}
