#pragma once
#include "../Library/gameObject.h"

class PlayMode : public GameObject
{
public:
	PlayMode();

	int playMode;	  // プレイモード
	bool IsGameStart; // ゲーム進行中
	bool IsGamePause; // ゲーム中断中

	void changeMode(); // プレイモード変更
	void gameStart();  // ゲーム開始
	void gamePause();  // ゲーム中断
};

