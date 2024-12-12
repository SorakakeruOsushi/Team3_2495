#pragma once 

#include "../Library/gameObject.h" 

class BestTime : public GameObject
{
private:
	float bestTime;
	int bestScore;

public:
	BestTime();

	// ベストタイム
	float GetBestTime() { return bestTime; }
	void SetBestTime(float playTime) { bestTime = playTime; }
	// ベストスコア
	int GetBestScore() { return bestScore; }
	void SetBestScore(int gotCoin) { bestScore = gotCoin; }
};

