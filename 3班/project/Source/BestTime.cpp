#include "BestTime.h" 

// コンストラクタ 
BestTime::BestTime()
{
	bestTime = 9999.0f;

	DontDestroyOnLoad(); // シーン変更で削除されないようにする 
}

// デストラクタ 
BestTime::~BestTime()
{

}