#include "PlayMode.h"
#include <cassert>

PlayMode::PlayMode()
{
	playMode = 0; //�v���C���[�h
	IsGameStart = false; // �Q�[���J�n
}

void PlayMode::changeMode()
{
	playMode = (playMode + 1) % 2; // �Ot���Pb��
}


