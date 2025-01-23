#pragma once 

#include "../Library/gameObject.h" 

class BestTime : public GameObject
{
private:
	float bestTime; // �ő��S�[���^�C��
	float bestScore;  // �ō��X�R�A

public:
	BestTime();

	// �x�X�g�^�C��
	float GetBestTime() { return bestTime; }
	void SetBestTime(float playTime) { bestTime = playTime; }

	// �x�X�g�X�R�A
	float GetBestScore() { return bestScore; }
	void SetBestScore(float score) { bestScore = score; }
};

