#include "PlayMode.h"

PlayMode::PlayMode()
{
	playMode = 0; //�v���C���[�h
}

void PlayMode::changeMode()
{
	playMode = (playMode + 1) % 2; // �O���P*/
	
}


