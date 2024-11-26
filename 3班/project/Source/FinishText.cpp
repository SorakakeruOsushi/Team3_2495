#include "FinishText.h"
#include "../Library/time.h"

FinishText::FinishText()
{
	timer = 0.0f;
	
}

FinishText::~FinishText()
{
}

void FinishText::Update()
{
	//Time::DeltaTime();�F�b�ő���邽�߃��j�^�[���\�ɍ��E����Ȃ�
	timer += Time::DeltaTime();

	if (timer >= 2.0f)
	{
		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			SceneManager::ChangeScene("TITLE");
		}
	}

}

void FinishText::Draw()
{

	//���݂̃t�H���g�T�C�Y
	int size = GetFontSize();

	//"FINISH!"
	SetFontSize(100);
	DrawString(200, 200, "TETRA DEAD", GetColor(255, 100, 100)); //(x,y,������,�F)

	if (timer >= 1.0f) //�P�b�������炸���ƕ\��
	{
		//(x,y,�F,������,�ς�镶����)   �u%d�v��u��������
		//�u%6d�v �F�U���p�ӂ���@�iif���ŃJ���X�g������΃I�[�o�[���Ȃ��j
		//�u%06d�v�F�U���p�ӂ���@�󔒂��O�Ŗ��߂�
		//�u%06d%%�v�F�u�����v�\���o����

		//���B���������A���Ԃ�\��
		SetFontSize(25);
		//����(playerHeight)
		DrawFormatString(200, 300, GetColor(255, 255, 255), "SCORE:%3.0f", fabs(resultHeight));
		DrawFormatString(200, 400, GetColor(255, 255, 255), "TIME:%4.2f", resultTime);
	}

	// "�X�y�[�X�L�[�ŏI��"
	if (timer >= 1.5f) //�P.�T�b�������炸���ƕ\��
	{
		DrawString(200, 500, "�X�y�[�X�L�[�������ďI�� ", GetColor(255, 255, 255));
	}

	//���̃t�H���g�T�C�Y�ɖ߂�
	SetFontSize(size);
}
