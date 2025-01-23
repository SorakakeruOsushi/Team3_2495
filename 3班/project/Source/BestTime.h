#pragma once 

#include "../Library/gameObject.h" 

class BestTime : public GameObject
{
private:
	float bestTime; // 最速ゴールタイム
	float bestScore;  // 最高スコア

public:
	BestTime();

	// ベストタイム
	float GetBestTime() { return bestTime; }
	void SetBestTime(float playTime) { bestTime = playTime; }

	// ベストスコア
	float GetBestScore() { return bestScore; }
	void SetBestScore(float score) { bestScore = score; }
};

