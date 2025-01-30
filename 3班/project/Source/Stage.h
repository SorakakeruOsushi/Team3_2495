#pragma once
#include <vector>
#include "../Library/gameObject.h"
#include "Vector2.h"
#include "Screen.h"
#include "Coin.h"
#include "CoinSP.h"
#include "PlayMode.h"
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

	int groundImage; // 画像 地面
	int blockImage;  // 画像 既存ブロック
	int goalImage;	 // 画像 ゴール(仮)
	int wallImage;   // 画像 横の壁
	int MinoImage[6];// 画像 ミノ

	int IsWallRight(VECTOR2 pos);//判定 衝突判定(右)
	int IsWallLeft(VECTOR2 pos); //判定 衝突判定(左)
	int IsWallDown(VECTOR2 pos); //判定 衝突判定(下)
	int IsWallUp(VECTOR2 pos);   //判定 衝突判定(上)
	bool IsGoal(VECTOR2 pos);	 //判定 ゴール

	void PutBlock(int x, int y, int id);
	bool CheckBlock(int x, int y);
	bool CheckOnGoal(int x, int y);
	bool CheckOnCoin(int x, int y);

	Player* p;
	Coin* c;
	CoinSP* cSP;
	Block* b;
	PlayMode* pm;

	int scroll;		//画面のスクロール
	bool cellBG;	//背景のマス目の表示

	int MinoLock;

	std::vector<std::string> split(const std::string& text, char delim);
};
