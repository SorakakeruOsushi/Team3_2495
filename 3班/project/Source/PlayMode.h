#pragma once
#include "../Library/gameObject.h"

class PlayMode : public GameObject
{
public:
	PlayMode();

	int playMode; // プレイモード
	bool IsGameStart; // ゲーム進行中

	void changeMode(); // プレイモード変更
};

