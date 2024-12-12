#include <DxLib.h>
#include <cassert>
#include "../Library/sceneManager.h"
#include "PlayScene.h"
#include "Player.h"
#include "Block.h"
#include "time.h"
#include "../Library/Utility.h"

PlayScene::PlayScene()
{
	pm = Instantiate<PlayMode>();
	s = Instantiate<Stage>();
	
	//
	p = FindGameObject<Player>();
		assert(pm != nullptr);
	pm = FindGameObject<PlayMode>();
		assert(pm != nullptr);
	bestTime = FindGameObject<BestTime>(); // �ō����_�Ǘ��pGameObject�̎擾 
		assert(bestTime != nullptr);

	Instantiate<Block>();
	// �摜�ǂݍ���
	nextTextImage = LoadGraph("data/image/XA1/xNEXT.png");
		assert(nextTextImage > 0);
	modeChangeTextImage = LoadGraph("data/image/XA1/xChangeCKey.png");
		assert(modeChangeTextImage > 0);
	// �����Ă�����?
	playModeTextImage = LoadGraph("data/image/XA1/xTETRA.png"); // �v���C���[�h�̃f�t�H���g�́uTETRA�v
		assert(modeChangeTextImage > 0);
	playModeBGImage = LoadGraph("data/image/X/XmodeBGtetra.png");   // �v���C���[�h�̃f�t�H���g�́uTETRA�v
		assert(modeChangeTextImage > 0);

	// �摜 �w�i1,2,3
	hBGImageI = LoadGraph("data/image/Back1.JPG");
		assert(hBGImageI > 0);
	hBGImageII = LoadGraph("data/image/Back2.JPG");
		assert(hBGImageII > 0);
	hBGImageIII = LoadGraph("data/image/Back3.JPG");
		assert(hBGImageIII > 0);
	// �����ǂݍ���
	titleBackVoice = LoadSoundMem("data/sound/���ʉ����{/voice/�u����������v.mp3");
		assert(titleBackVoice > 0);
	changeModeVoice = LoadSoundMem("data/sound/���ʉ����{/voice/�u�͂��́`����v.mp3");
		assert(changeModeVoice > 0);
	/*
	// BGM�̃��[�v�Đ�
	gameBGM = LoadSoundMem("data/sound/���ʉ����{/���̂������铴�A.mp3");
		assert(gameBGM > 0);
	PlaySoundMem(gameBGM, DX_PLAYTYPE_LOOP);
	*/

	g = nullptr;
	f = nullptr;

	playTime = 0.0f;		//�v���C����

	height = 0.0f;			//�����̍���(10)������
	bestHeight = 0.0f;
}

PlayScene::~PlayScene()
{
	DeleteGraph(hBGImageI);			 // �v���C�V�[�� �w�i
	DeleteGraph(hBGImageII);
	DeleteGraph(hBGImageIII);

	DeleteGraph(playModeTextImage); //�uTETRA�v���uBLOCK�v
	DeleteGraph(playModeTextImage); // �v���C�G���A �v���C���[�h�w�i

	DeleteGraph(nextTextImage);		 //�uNEXT�v
	DeleteGraph(modeChangeTextImage);//�uCHANGE:[C]KEY�v
	DeleteSoundMem(titleBackVoice);
	DeleteSoundMem(changeModeVoice);
	// DeleteSoundMem(gameBGM);
}

void PlayScene::Update()
{
	//�p�b�h�p�֐�(���t���[���Ăяo��)
	GetJoypadXInputState(DX_INPUT_PAD1, &input);

	//[T]�^�C�g���֖߂�i�B���@�\�j
	if (CheckHitKey(KEY_INPUT_T))
	{
		// �T�E���h���I������܂ő҂� 
		PlaySoundMem(titleBackVoice, DX_PLAYTYPE_NORMAL);
		SceneManager::ChangeScene("TITLE");
	}
	//[Tab]�|�[�Y&����w���v
	if (KeyUtility::CheckTrigger(KEY_INPUT_TAB))
	{
		// COMING SOON
	}
	//[0]���X�^�[�g
	if (KeyUtility::CheckTrigger(KEY_INPUT_0))
	{
		//�P�t���[������"RESTART�V�[��"�ɍs���A"PLAY�V�[��"�ɖ߂��Ă���
		SceneManager::ChangeScene("RESTART");
	}
	//[1]�Z���\���؂�ւ�
	if (KeyUtility::CheckTrigger(KEY_INPUT_1))
	{
		s->cellBG = !s->cellBG;
	}
	
	
	if (!p->finished && !p->goaled)
	{
		//�^�C�}�[
		playTime += Time::DeltaTime();
		//playTime�̃J���X�g(9999)
		if (playTime >= 9999)
		{
			playTime = 9999;
		}

		//����(height)
		if ((s != nullptr) && (s->p != nullptr))
		{
			height = s->p->playerHeight / 30;
		}
	}

	// �v���C���[�h�؂�ւ�
	if ( (KeyUtility::CheckTrigger(KEY_INPUT_C)) || (input.Buttons[XINPUT_BUTTON_Y]) )
	{
		PlaySoundMem(changeModeVoice, DX_PLAYTYPE_BACK);
		//PlayMode�N���X����֐����Ăяo��
		pm->changeMode();
	}
	if (pm->playMode == 0) // �e�g�����[�h
	{
		playModeTextImage = LoadGraph("data/image/XA1/xTETRA.png");
		playModeBGImage = LoadGraph("data/image/X/XmodeBGtetra.png");
	}
	else 				   // �u���b�N���[�h
	{
		playModeTextImage = LoadGraph("data/image/XA1/xBLOCK.png");
		playModeBGImage = LoadGraph("data/image/X/XmodeBGblock.png");
	}

	
	//GOAL��FINISH���Ăяo��
	if (p->goaled && g == nullptr)
	{
		g = FindGameObject<GoalText>();
		g->resultTime = playTime;
		g->resultHeight = bestHeight;
		// �x�X�g�^�C���m�F 
		CheckBestTime();
		// �m�F 
		CheckBestScore();
		return;
	}
	if (p->finished && f == nullptr)
	{
		f = Instantiate<FinishText>();
		f->resultTime = playTime;
		f->resultHeight = bestHeight;
		return;
	}

}

void PlayScene::Draw()
{
	// �w�i�摜�\��(�{���͘A��png��z��ł�肽��)
	DrawGraph(0, -(Screen::HEIGHT * 0) - s->scroll, hBGImageI, TRUE);   //������P�Ԗ�
	DrawGraph(0, -(Screen::HEIGHT * 1) - s->scroll, hBGImageII, TRUE);  //������Q�Ԗ�
	DrawGraph(0, -(Screen::HEIGHT * 2) - s->scroll, hBGImageIII, TRUE); //������R�Ԗ�

	//��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	DrawGraph(30 * 8, -(Screen::HEIGHT * 0), playModeBGImage, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�uNEXT�v�\��
	DrawGraph(1025, 50, nextTextImage, TRUE);

	//(x,y,�F,������,�ς�镶����)   �u%d�v��u��������
	//�u%6d�v �F�U���p�ӂ���@�iif���ŃJ���X�g������΃I�[�o�[���Ȃ��j
	//�u%06d�v�F�U���p�ӂ���@�󔒂��O�Ŗ��߂�
	//�u%06d%%�v�F�u�����v�\���o����
	//�f�t�H���g�ł͉E�l�Ȃ̂ŁA���l�ɂ������Ƃ��͌����w��̂܂��Ƀ}�C�i�X�����Ȃ���΂Ȃ�Ȃ��B

	SetFontSize(25);
	//����(playerHeight)
	DrawFormatString(1030, 400, GetColor(255, 255, 255), "HEIGHT:%.0f/50", fabs(height));
	//�X�R�A(Coin?)
	DrawFormatString(1030, 500, GetColor(255, 255, 255), "SCORE:%d", p->gotCoin);
	//�^�C��(playTime)
	DrawFormatString(1030, 600, GetColor(255, 255, 255), "TIME:%4.2f", playTime);
	
	SetFontSize(15);
	//�x�X�g�X�R�A(bestScore)
	DrawFormatString(1030, 530, GetColor(255, 255, 255), "BEST SCORE:%d", bestTime->GetBestScore() );
	//�x�X�g�^�C��(bestTime)
	DrawFormatString(1030, 630, GetColor(255, 255, 255), "BEST TIME:%4.2f", bestTime->GetBestTime() );

	//�v���C���[�h(TETRA/BLOCK)
	DrawGraph(5, 530, playModeTextImage, TRUE); //playModeImage�ɓ����摜��؂�ւ���?
	//�uCHANGE�F[C] KEY�v�\��
	DrawGraph(5, 600, modeChangeTextImage, TRUE);
}

void PlayScene::CheckBestTime()
{
	// �x�X�g�^�C�����X�V���� 
	if (playTime < bestTime->GetBestTime())
	{
		bestTime->SetBestTime(playTime);
	}
}

// �x�X�g�X�R�A���X�V
void PlayScene::CheckBestScore()
{
	if (p->gotCoin > bestTime->GetBestScore())
	{
		bestTime->SetBestScore(p->gotCoin);
	}
}

