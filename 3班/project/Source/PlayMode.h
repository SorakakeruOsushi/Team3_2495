#pragma once
#include "../Library/gameObject.h"

class PlayMode : public GameObject
{
public:
	PlayMode();

	int playMode;	  // �v���C���[�h
	bool IsGameStart; // �Q�[���i�s��
	bool IsGamePause; // �Q�[�����f��

	void changeMode(); // �v���C���[�h�ύX
	void gameStart();  // �Q�[���J�n
	void gamePause();  // �Q�[�����f
};

