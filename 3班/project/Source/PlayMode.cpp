#include "PlayMode.h"
#include <cassert>

PlayMode::PlayMode()
{
	playMode = 0; //�v���C���[�h
	IsGameStart = false; // �Q�[���J�n
	IsGamePause = false; // �Q�[�����f
}

void PlayMode::changeMode()
{
	playMode = (playMode + 1) % 2; // �Ot���Pb��
}

void PlayMode::gameStart()
{
	IsGameStart = true;			   // �Q�[���J�n
}


