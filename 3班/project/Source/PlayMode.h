#pragma once
#include "../Library/gameObject.h"

class PlayMode : public GameObject
{
public:
	PlayMode();

	int playMode; //プレイモード

	void changeMode(); // プレイモード変更
};

