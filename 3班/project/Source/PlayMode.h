#pragma once
#include "../Library/gameObject.h"

class PlayMode : public GameObject
{
public:
	PlayMode();

	int playMode; //�v���C���[�h

	void changeMode(); // �v���C���[�h�ύX
};

