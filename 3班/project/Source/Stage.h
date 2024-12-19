#pragma once
#include <vector>
#include "../Library/gameObject.h"
#include "Vector2.h"
#include "Screen.h"
#include "Coin.h"
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

	int emptyImage;  // �摜 �}�X��
	int blockImage;  // �摜 �D�u���b�N
	int goalImage;	 // �摜 �S�[��(��)
	int wallImage;   // �摜 ���̕�
	int MinoImage[6];//�~�m�̉摜

	

	int IsWallRight(VECTOR2 pos);
	int IsWallLeft(VECTOR2 pos);
	int IsWallDown(VECTOR2 pos);
	int IsWallUp(VECTOR2 pos);
	bool IsGoal(VECTOR2 pos);	//�S�[������

	void PutBlock(int x, int y, int id);

	int CheckBlock(int x, int y);

	Player* p;
	Coin* c;
	Block* b;

	int scroll;		//��ʂ̃X�N���[��
	bool cellBG;	//�w�i�̃}�X�ڂ̕\��

	std::vector<std::string> split(const std::string& text, char delim);
};
