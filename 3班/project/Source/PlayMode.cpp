#include "PlayMode.h"

PlayMode::PlayMode()
{
	playMode = 0; //プレイモード
}

void PlayMode::changeMode()
{
	playMode = (playMode + 1) % 2; // ０か１*/
	
}


