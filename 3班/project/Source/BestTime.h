#pragma once 

#include "../Library/gameObject.h" 

class BestTime : public GameObject
{
private:
	float bestTime;
	int bestScore;

public:
	BestTime();

	// �x�X�g�^�C��
	float GetBestTime() { return bestTime; }
	void SetBestTime(float playTime) { bestTime = playTime; }
	// �x�X�g�X�R�A
	int GetBestScore() { return bestScore; }
	void SetBestScore(int gotCoin) { bestScore = gotCoin; }
};

