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
const int CHIP_SIZE = 30;   //�`�b�v�T�C�Y
class Stage : public GameObject
{
public:
	Stage();
	~Stage();
	void Draw() override;

	int groundImage; // �摜 �n��
	int blockImage;  // �摜 �����u���b�N
	int goalImage;	 // �摜 �S�[��(��)
	int wallImage;   // �摜 ���̕�
	int MinoImage[6];// �摜 �~�m

	int IsWallRight(VECTOR2 pos);//���� �Փ˔���(�E)
	int IsWallLeft(VECTOR2 pos); //���� �Փ˔���(��)
	int IsWallDown(VECTOR2 pos); //���� �Փ˔���(��)
	int IsWallUp(VECTOR2 pos);   //���� �Փ˔���(��)
	bool IsGoal(VECTOR2 pos);	 //���� �S�[��

	void PutBlock(int x, int y, int id);
	bool CheckBlock(int x, int y);
	bool CheckOnGoal(int x, int y);
	bool CheckOnCoin(int x, int y);

	Player* p;
	Coin* c;
	CoinSP* cSP;
	Block* b;
	PlayMode* pm;

	int scroll;		//��ʂ̃X�N���[��
	bool cellBG;	//�w�i�̃}�X�ڂ̕\��

	int MinoLock;

	std::vector<std::string> split(const std::string& text, char delim);
};
