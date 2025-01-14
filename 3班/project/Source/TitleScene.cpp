#include "TitleScene.h"
#include <DxLib.h>
#include <cassert>
#include "BestTime.h" 

TitleScene::TitleScene()
{
	titleImage = LoadGraph("data/image/Title.JPG");			  // �摜 �^�C�g�����
		assert(titleImage > 0);
	titleLogoImage = LoadGraph("data/image/���S_����.png");   // �摜 �^�C�g�����S
		assert(titleLogoImage > 0);
	titleBGImage = LoadGraph("data/image/Back1.png");		  // �摜 �^�C�g����ʔw�i
		assert(titleBGImage > 0);
	pushKeyTextImage = LoadGraph("data/image/font/Push.png"); //�uPUSH ANY KEY�v
		assert(pushKeyTextImage > 0);

	startSound = LoadSoundMem("data/sound/���ʉ����{/voice/�u����������v.mp3");   // �� [T]�^�C�g���ɖ߂�
		assert(startSound > 0);
	
	DrawKeyTimer = 0.0f;  // �^�C�}�[ 
	IsDraw = true;
}

TitleScene::~TitleScene()
{
	DeleteGraph(titleImage);
	DeleteGraph(titleLogoImage);
	DeleteGraph(titleBGImage);
	DeleteGraph(pushKeyTextImage);

	DeleteSoundMem(startSound);
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
		PlaySoundMem(startSound, DX_PLAYTYPE_NORMAL);
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
		DrawGraph(330, 500, pushKeyTextImage, TRUE);
	}

	//�����p�Z���^�[�h�b�g
	DrawString(1280/2, 720/2, ".", GetColor(255, 0, 0), TRUE);
}
