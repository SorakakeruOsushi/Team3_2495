#pragma once
#include <vector>
#include "../Library/gameObject.h"
#include "Vector2.h"
#include "Screen.h"
#include "Coin.h"
//include "Block.h"

class Block;

class Player;
const int CHIP_SIZE = 30;   //チップサイズ
class Stage : public GameObject
{
public:
	Stage();
	~Stage();
	void Draw() override;

	int emptyImage;  // 画像 マス目
	int blockImage;  // 画像 灰ブロック
	int goalImage;	 // 画像 ゴール(仮)
	int wallImage;   // 画像 横の壁
	int MinoImage[6];//ミノの画像

	

	int IsWallRight(VECTOR2 pos);
	int IsWallLeft(VECTOR2 pos);
	int IsWallDown(VECTOR2 pos);
	int IsWallUp(VECTOR2 pos);
	bool IsGoal(VECTOR2 pos);	//ゴール判定

	void PutBlock(int x, int y, int id);

	int CheckBlock(int x, int y);

	Player* p;
	Coin* c;
	Block* b;

	int scroll;		//画面のスクロール
	bool cellBG;	//背景のマス目の表示

	std::vector<std::string> split(const std::string& text, char delim);
};
