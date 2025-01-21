#pragma once
#include "../Library/gameObject.h"
#include "Vector2.h"
#include "time.h"
//#include "Stage.h"
#include "PlayMode.h"
class Stage;

class Player : public GameObject {
public:
	Player();
	~Player();
	void Update() override;
	void Draw() override;

	int playerImage; // �摜 �v���C���[
	int playerIdolImage; // �摜 IDOL�v���C���[
	int playerAnimImage; // �摜 ANIM�v���C���[

	int jumpSound;   // �� �W�����v
	int fallSound;	 // �� ��ʊO��

	XINPUT_STATE input; //PAD����p�ϐ�
	
	Stage* s;
	PlayMode* pm;

	VECTOR2 position;

	int alpha;

	float playerHeight;
	float prePlayerY;
	float playerBestHeight;

	float speed;		// ���x

	float velocity;		// �͂ƕ���
	bool prevJumpKey;	// �O�̃W�����v�L�[
	bool onGround;		// �ڒn����

	int gotCoin;		// �R�C���擾��

	bool finished;		// ���񂾁I
	bool goaled;		// �S�[��

	bool IsWalkLeft;
	bool IsWalkRight;
	int patternX;
	int patternY;
	float timer;
	int outOfScreen;   // �v���C���[���ǂ̒��x��ʂ̊O�ɏo����Q�[���I�[�o�[�ɂȂ邩
};