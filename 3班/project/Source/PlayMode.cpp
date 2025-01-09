#include "PlayMode.h"
#include <cassert>

PlayMode::PlayMode()
{
	playMode = 0; //プレイモード
	IsGameStart = false; // ゲーム開始
}

void PlayMode::changeMode()
{
	playMode = (playMode + 1) % 2; // ０tか１bか
}


