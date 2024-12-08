#include "TitleScene.h"
#include <DxLib.h>
#include <cassert>
#include "BestTime.h" 

TitleScene::TitleScene()
{
	titleImage = LoadGraph("data/image/Title.JPG");
		assert(titleImage > 0);
	pushKeyTextImage = LoadGraph("data/image/X/XpushAnyKey.png");
		assert(pushKeyTextImage > 0);

	// �ō����_�Ǘ��pGameObject�̍쐬
	Instantiate<BestTime>();

	alpha = 0;    // [PUSH SPACE KEY]�̃A���t�@�l 
	ofset = (int)((float)MAX_ALPHA / DRAW_KEY_WAIT);
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


	// �A���t�@�l�̌v�Z 
	alpha += (int)(ofset * Time::DeltaTime());
	// �O�t���[������̌o�ߎ��Ԃ��擾 
	DrawKeyTimer += Time::DeltaTime();
	// ��莞��(DRAW_KEY_WAIT)�o�߂�����A�A���t�@�l�̉��Z�E���Z��؂肩���� 
	if (DrawKeyTimer >= DRAW_KEY_WAIT)
	{
		ofset = -ofset;
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
	// �^�C�g����� 
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);  // �ʏ�`�� 
	DrawGraph(0, 0, titleImage, TRUE);

	// [PUSH SPACE KEY] 
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha); // �A���t�@�u�����f�B���O 
	DrawGraph(300, 500, pushKeyTextImage, TRUE);
}
