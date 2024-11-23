#include "FinishText.h"
#include "../Library/time.h"

FinishText::FinishText()
{
	timer = 0.0f;
}

FinishText::~FinishText()
{
}

int score = 100;


void FinishText::Update()
{
	//Time::DeltaTime();�F�b�ő���邽�߃��j�^�[���\�ɍ��E����Ȃ�
	timer += Time::DeltaTime();

	if (timer >= 2.0f)
	{
		//��ň�x�������͔���ɂ���
		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			SceneManager::ChangeScene("TitleScene");
		}
	}

}

void FinishText::Draw()
{

	//���݂̃t�H���g�T�C�Y
	int size = GetFontSize();

	//"FINISH!"
	SetFontSize(50);
	DrawString(200, 200, "FINISH! ", GetColor(255, 255, 127)); //(x,y,������,�F)

	// "SCORE�F��m"
	// "TIME �F��s"
	if (timer >= 1.0f) //�P�b�������炸���ƕ\��
	{
		//(x,y,�F,������,�ς�镶����)   �u%d�v��u��������
		//�u%6d�v �F�U���p�ӂ���@�iif���ŃJ���X�g������΃I�[�o�[���Ȃ��j
		//�u%06d�v�F�U���p�ӂ���@�󔒂��O�Ŗ��߂�
		//�u%06d%%�v�F�u�����v�\���o����

		SetFontSize(25);
		DrawFormatString(200, 300, GetColor(255, 255, 255), "SCORE:%06d", score); 
		DrawFormatString(200, 300, GetColor(255, 255, 255), "SCORE:%06d", score);
		
		//���B�����A�N���A�^�C���iABC�]���j�i�N���A���̂݁j
		//Finish(Dead)��Clear(�S�[������Ȃ�)�ŕʁH
	}

	// "�X�y�[�X�L�[�ŏI��"
	if (timer >= 1.5f) //�P.�T�b�������炸���ƕ\��
	{
		DrawString(200, 500, "�X�y�[�X�L�[�������ďI�� ", GetColor(255, 255, 255));
	}

	//���̃t�H���g�T�C�Y�ɖ߂�
	SetFontSize(size);
}
