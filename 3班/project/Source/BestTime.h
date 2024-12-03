#pragma once 

#include "../Library/gameObject.h" 

class BestTime : public GameObject
{
private:
	float bestTime;

public:
	BestTime();
	~BestTime();

	float GetBestTime() { return bestTime; }
	void SetBestTime(float playTime) { bestTime = playTime; }
};

