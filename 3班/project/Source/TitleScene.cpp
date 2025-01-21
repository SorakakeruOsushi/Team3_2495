#include "TitleScene.h"
#include <DxLib.h>
#include <cassert>
#include "BestTime.h" 

TitleScene::TitleScene()
{
	titleImage = LoadGraph("data/image/�w�i/newTitle.jpeg");	  // �摜 �^�C�g�����
		assert(titleImage > 0);
	pushKeyTextImage = LoadGraph("data/image/font/PushKey.png"); //�uPUSH ANY KEY�v
		assert(pushKeyTextImage > 0);

	startSound = LoadSoundMem("data/sound/GameSE/����{�^��������24.mp3"); // �� [ANY]�Q�[����ʂ�
		assert(startSound > 0);
	
	DrawKeyTimer = 0.0f;  // �^�C�}�[ 
	IsDraw = true;

	changeSceneCountDown = 1.0f;
	IsPushAnyKey = false;
}

TitleScene::~TitleScene()
{
	DeleteGraph(titleImage);
	DeleteGraph(pushKeyTextImage);

	DeleteSoundMem(startSound);
}

void TitleScene::Update()
{
	//�p�b�h�p�֐�(���t���[���Ăяo��)
	GetJoypadXInputState(DX_INPUT_PAD1, &input);

	if (KeyUtility::CheckTrigger(KEY_INPUT_ESCAPE))
	{
		SceneManager::Exit();
	}

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
		IsDraw = true;
		IsPushAnyKey = true;
		// �T�E���h�Đ�
		PlaySoundMem(startSound, DX_PLAYTYPE_BACK);
		
	}
	if (IsPushAnyKey)
	{
		changeSceneCountDown -= Time::DeltaTime();

		if (changeSceneCountDown <= 0)
		{
			SceneManager::ChangeScene("PLAY");
		}
	}
}


void TitleScene::Draw()
{
	// �^�C�g���摜
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);  // �ʏ�`��
	DrawGraph(0, 0, titleImage, TRUE);

	// [PUSH ANY KEY]�\�� 
	SetFontSize(50);
	if (IsDraw)
	{
		DrawGraph(0, 0, pushKeyTextImage, TRUE);
	}

	//�����p�Z���^�[�h�b�g
	//DrawString(1280/2, 720/2, ".", GetColor(255, 0, 0), TRUE);
}