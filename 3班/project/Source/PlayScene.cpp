#include <DxLib.h>
#include "../Library/sceneManager.h"
#include "PlayScene.h"
#include "Player.h"
#include "Block.h"
#include "time.h"

PlayScene::PlayScene()
{
	s = Instantiate<Stage>();
	p = FindGameObject<Player>();

	Instantiate<Block>();

	f = nullptr;

	playTime = 0.0f;		//�v���C����

	bestTime = 0.0f;		//�x�X�g�N���A����

	score = 0.0f;			//�����̍���(10)������
	highScore = 0.0f;
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	
	if (!p->finished && !p->goaled)
	{
		//�^�C�}�[
		playTime += Time::DeltaTime();
		//playTime�̃J���X�g(9999)
		if (playTime >= 9999)
		{
			playTime = 9999;
		}

		//�X�R�A
		if ((s != nullptr) && (s->p != nullptr))
		{
			score = s->p->playerHeight;
		}
		//�n�C�X�R�A
		if (highScore <= score/30)
		{
			highScore = score/30;
		}
	}
	

	// �^�C�g���֖߂�i�B���@�\�j
	if (CheckHitKey(KEY_INPUT_T)) 
	{
		SceneManager::ChangeScene("TITLE");
	}

	//GOAL��FINISH���Ăяo��
	if (p->goaled)
	{
		g = FindGameObject<GoalText>();
		g->resultTime = playTime;
		g->resultHeight = highScore;
		return;
	}
	if (p->finished && f == nullptr)
	{
		f = Instantiate<FinishText>();
		f->resultTime = playTime;
		f->resultHeight = highScore;
		return;
	}
}

void PlayScene::Draw()
{
	DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));

	SetFontSize(40);
	DrawString(1000, 100, "N E X T", GetColor(255, 255, 255));

	//(x,y,�F,������,�ς�镶����)   �u%d�v��u��������
	//�u%6d�v �F�U���p�ӂ���@�iif���ŃJ���X�g������΃I�[�o�[���Ȃ��j
	//�u%06d�v�F�U���p�ӂ���@�󔒂��O�Ŗ��߂�
	//�u%06d%%�v�F�u�����v�\���o����
	//�f�t�H���g�ł͉E�l�Ȃ̂ŁA���l�ɂ������Ƃ��͌����w��̂܂��Ƀ}�C�i�X�����Ȃ���΂Ȃ�Ȃ��B
	/*
	�w���	�o�͌���
	printf("[%15s]", "I am a boy.");	[I am a boy.]
	printf("[%8.3f]", 123.45678);		[123.456]
	printf("[%5d]", 1);				[     1]
	*/

	SetFontSize(25);
	//���x��(stageLevel)
	DrawFormatString(1000, 400, GetColor(255, 255, 255), "LEVEL:%02d", 1);

	//����(playerHeight)
	DrawFormatString(1000, 450, GetColor(255, 255, 255), "SCORE:%3.0f", fabs(highScore));
	
	//�^�C�}�[(playTime)
	DrawFormatString(1000, 500, GetColor(255, 255, 255), "TIME:%4.2f", playTime);

	//���݂̃��[�h��\��(��) PLAYER/BLOCK
	DrawString(1000, 600, "MODE�FPLAYER", GetColor(255, 255, 255));

	SetFontSize(15);
	//���[�h�ύX
	DrawString(1000, 650, "CHANGE�Fpush [C] key", GetColor(255, 255, 255));

	//���݂�LEVEL�Ƃ�
}
