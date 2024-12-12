#include "BestTime.h" 

// コンストラクタ 
BestTime::BestTime()
{
	bestTime = 9999.0f;
	bestScore = 0;

	DontDestroyOnLoad(); // シーン変更で削除されないようにする 
}