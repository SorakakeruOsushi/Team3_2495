#pragma once
#include "../Library/gameObject.h"

class PlayMode : public GameObject
{
public:
	PlayMode();

	int playMode; // �v���C���[�h
	bool IsGameStart; // �Q�[���i�s��

	void changeMode(); // �v���C���[�h�ύX
};

