#include "PlayMode.h"
#include <cassert>
#include "Stage.h"
#include "Player.h"

PlayMode::PlayMode()
{
	playMode = 0; //�v���C���[�h
	IsGameStart = false; // �Q�[���J�n
}

void PlayMode::changeMode()
{
	playMode = (playMode + 1) % 2; // �Ot���Pb��
	if (playMode == 0) {
		Stage* st = FindGameObject<Stage>();
		Player* pl = FindGameObject<Player>();
		VECTOR2 leftTop = pl->position + VECTOR2(0, 9);
		VECTOR2 rightDown = pl->position + VECTOR2(29, 68);
		st->Erase(leftTop, rightDown);
	}
}


