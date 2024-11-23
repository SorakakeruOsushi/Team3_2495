#include <DxLib.h>
#include "../Library/sceneManager.h"
#include "PlayScene.h"
#include "Player.h"
#include "Block.h"
#include "Stage.h"
#include "time.h"


PlayScene::PlayScene()
{
	Stage* s = Instantiate<Stage>();

	//Instantiate<Player>();
	Instantiate<Block>();

	playTime = 0;
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	// �^�C�g���֖߂�i�B���@�\�j
	if (CheckHitKey(KEY_INPUT_T)) 
	{
		SceneManager::ChangeScene("TITLE");
	}

	//�^�C�}�[(�Q�[���i�s���̂݉��Z)
	//if(gamePlay)
	{
		playTime += Time::DeltaTime();
	}
	//playTime�̃J���X�g(9999)
	if (playTime >= 9999)
	{
		playTime = 9999;
	}

}

void PlayScene::Draw()
{
	DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));

	SetFontSize(40);
	DrawString(900, 100, "N E X T", GetColor(255, 255, 255));

	//(x,y,�F,������,�ς�镶����)   �u%d�v��u��������
	//�u%6d�v �F�U���p�ӂ���@�iif���ŃJ���X�g������΃I�[�o�[���Ȃ��j
	//�u%06d�v�F�U���p�ӂ���@�󔒂��O�Ŗ��߂�
	//�u%06d%%�v�F�u�����v�\���o����

	SetFontSize(25);
	//����(p->playerHeight)
	DrawFormatString(900, 400, GetColor(255, 255, 255), "SCORE:%04d", 810);
	
	//�^�C�}�[(playTime)
	DrawFormatString(900, 500, GetColor(255, 255, 255), "TIME(s):%04d", playTime);

	//���݂̃��[�h��\��(��)
	DrawString(900, 600, "MODE�FPLAYER", GetColor(255, 255, 255));

	SetFontSize(15);
	//���[�h�ύX
	DrawString(900, 650, "CHANGE�Fpush [C] key", GetColor(255, 255, 255));
}
