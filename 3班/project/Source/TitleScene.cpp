#include "TitleScene.h"
#include <DxLib.h>
#include <cassert>
#include "BestTime.h" 

TitleScene::TitleScene()
{
	titleImage = LoadGraph("data/image/Title.JPG");
		assert(titleImage > 0);
	pushKeyTextImage = LoadGraph("data/image/XA1/xPushAnyKey.png");
		assert(pushKeyTextImage > 0);
	
	DrawKeyTimer = 0.0f;  // �^�C�}�[ 
}

TitleScene::~TitleScene()
{
	DeleteGraph(titleImage);
	DeleteGraph(pushKeyTextImage);
}

void TitleScene::Update()
{
	//�p�b�h�p�֐�(���t���[���Ăяo��)
	GetJoypadXInputState(DX_INPUT_PAD1, &input);


	//

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
	// �^�C�g����� 
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);  // �ʏ�`�� 
	DrawGraph(0, 0, titleImage, TRUE);

	// [PUSH ANY KEY]�\�� 
	DrawGraph(300, 500, pushKeyTextImage, TRUE);
}
