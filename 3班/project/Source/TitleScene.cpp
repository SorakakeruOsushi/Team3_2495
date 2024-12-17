#include "TitleScene.h"
#include <DxLib.h>
#include <cassert>
#include "BestTime.h" 

TitleScene::TitleScene()
{
	titleImage = LoadGraph("data/image/Title.JPG"); // �^�C�g�����
		assert(titleImage > 0);
	titleLogoImage = LoadGraph("data/image/���S_����.png"); // �^�C�g�����S
		assert(titleLogoImage > 0);
	titleBGImage = LoadGraph("data/image/Back1.png"); // �^�C�g�����S
		assert(titleBGImage > 0);
	pushKeyTextImage = LoadGraph("data/image/XA1/xPushAnyKey.png"); //�uPUSH ANY KEY�v
		assert(pushKeyTextImage > 0);
	
	DrawKeyTimer = 0.0f;  // �^�C�}�[ 
	IsDraw = true;
}

TitleScene::~TitleScene()
{
	DeleteGraph(titleImage);
	DeleteGraph(titleLogoImage);
	DeleteGraph(titleBGImage);
	DeleteGraph(pushKeyTextImage);
}

void TitleScene::Update()
{
	//�p�b�h�p�֐�(���t���[���Ăяo��)
	GetJoypadXInputState(DX_INPUT_PAD1, &input);

	// �\���ؑ�
	DrawKeyTimer += Time::DeltaTime();
	if (DrawKeyTimer >= 0.7f)
	{
		IsDraw = !IsDraw;
		DrawKeyTimer = 0.0f;
	}


	// �L�[���͂Ȃ牽�ł�OK(�P�񂾂�����)
	if ( (KeyUtility::CheckTriggerAll(DX_CHECKINPUT_KEY)) || (input.Buttons[XINPUT_BUTTON_B]))
	{
		// �T�E���h���I������܂ő҂� 
		//PlaySoundFile(  , DX_PLAYTYPE_NORMAL);
		SceneManager::ChangeScene("PLAY");
	}
	if (KeyUtility::CheckTrigger(KEY_INPUT_ESCAPE))
	{
		SceneManager::Exit();
	}
}


void TitleScene::Draw()
{
	// �^�C�g���摜
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);  // �ʏ�`��
	//DrawGraph(0, 0, titleImage, TRUE);
	DrawGraph(0, 0, titleBGImage, TRUE);
	DrawGraph(0, 0, titleLogoImage, TRUE);

	// [PUSH ANY KEY]�\�� 
	SetFontSize(50);
	if (IsDraw)
	{
		// DrawString(340, 500, "�o�t�r�g �`�m�x �j�d�x", GetColor(255, 255, 255), TRUE);
		DrawGraph(270, 500, pushKeyTextImage, TRUE);
	}

	SetFontSize(25);
	DrawString(585, 615, "�g�d�k�o", GetColor(255, 255, 255));
	DrawString(560, 650, "�b�n�m�e�h�f", GetColor(255, 255, 255));

	//�����p�Z���^�[�h�b�g
	//DrawString(1280/2, 720/2, ".", GetColor(255, 0, 0), TRUE);
}
