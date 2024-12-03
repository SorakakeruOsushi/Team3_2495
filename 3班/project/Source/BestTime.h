#pragma once 

#include "../Library/gameObject.h" 

class BestTime : public GameObject
{
private:
	static const int DEFAULT_HIGH_SCORE = 1000;  // �N�����̍ō����_ 

private:
	int bestTime;

public:
	BestTime();
	~BestTime();

	int GetbestTime() { return bestTime; }
	void SetbestTime(int score) { bestTime = score; }
};

