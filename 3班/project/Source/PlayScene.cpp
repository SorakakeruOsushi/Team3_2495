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
	s = Instantiate<Stage>();
	p = FindGameObject<Player>();
	/*
	pm = FindGameObject<PlayMode>();
		assert(pm != nullptr);
	*/
	bestTime = FindGameObject<BestTime>(); // �ō����_�Ǘ��pGameObject�̎擾 
		assert(bestTime != nullptr);

	Instantiate<Block>();

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

	//IsPause = false; // �|�[�Y
}

PlayScene::~PlayScene()
{
	DeleteSoundMem(titleBackVoice);
	DeleteSoundMem(changeModeVoice);
	DeleteSoundMem(gameBGM);
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
	
	//GOAL��FINISH���Ăяo��
	if (p->goaled && g == nullptr)
	{
		g = FindGameObject<GoalText>();
		g->resultTime = playTime;
		g->resultHeight = bestHeight;
		// �ō����_�m�F 
		CheckBestTime();
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
	SetFontSize(40);
	DrawString(1035, 50, "N E X T", GetColor(255, 255, 255));

	//(x,y,�F,������,�ς�镶����)   �u%d�v��u��������
	//�u%6d�v �F�U���p�ӂ���@�iif���ŃJ���X�g������΃I�[�o�[���Ȃ��j
	//�u%06d�v�F�U���p�ӂ���@�󔒂��O�Ŗ��߂�
	//�u%06d%%�v�F�u�����v�\���o����
	//�f�t�H���g�ł͉E�l�Ȃ̂ŁA���l�ɂ������Ƃ��͌����w��̂܂��Ƀ}�C�i�X�����Ȃ���΂Ȃ�Ȃ��B

	SetFontSize(25);
	//����(playerHeight)
	DrawFormatString(1030, 400, GetColor(255, 255, 255), "HEIGHT:%.0f/50", fabs(height));
	//�X�R�A(highScore + Coin?)
	DrawFormatString(1030, 500, GetColor(255, 255, 255), "SCORE:%0.0f", 0);
	//�^�C��(playTime)
	DrawFormatString(1030, 600, GetColor(255, 255, 255), "TIME:%4.2f", playTime);
	
	SetFontSize(15);
	//�x�X�g�X�R�A(bestScore)
	DrawFormatString(1030, 530, GetColor(255, 255, 255), "BEST SCORE:%0.0f", 0);
	//�x�X�g�^�C��(bestTime)
	DrawFormatString(1030, 630, GetColor(255, 255, 255), "BEST TIME:%4.2f", bestTime->GetBestTime() );

	//�v���C���[�h(TETRA/BLOCK)
	SetFontSize(60);
	//DrawFormatString(25, 530, GetColor(255, 255, 255), "%5s", pm->playMode == 0 ? "TETRA" : "BLOCK");
	SetFontSize(20);
	//���[�h�ύX
	DrawString(20, 600, "CHANGE�F[C] KEY", GetColor(255, 255, 255));
}

void PlayScene::CheckBestTime()
{
	// ���Ԃ�Z�k�X�V���� 
	if (playTime < bestTime->GetBestTime())
	{
		bestTime->SetBestTime(playTime);
	}
}
