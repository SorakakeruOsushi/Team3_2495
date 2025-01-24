#include "Coin.h"
#include <cassert>
#include "Player.h"
#include "Stage.h"
#include "Time.h"

Coin::Coin()
{
	//�R���X�g���N�^�ŊG�����[�h
	//coinImage = LoadGraph("data/image/Coin.PNG");			  // �摜 �R�C��
	coinImage = LoadGraph("data/image/Xcoin.png");			  // �摜 �R�C��
		assert(coinImage > 0);
	coinSound = LoadSoundMem("data/sound/GameSE/�R�C��.mp3"); // �� �R�C���擾
		assert(coinSound > 0);
	
	position.x = 0.0f;
	position.y = 0.0f;

	SetDrawOrder(6); //�`�揇

	got = false;
	CoinDraw = true;

	destroyTimer = 0.0f;     //�R�C���\���^�C�}�[
	destroyTimeLimit = 0.1f; //�R�C���\������
	v = 0.0f;

	destroyCountDown = 1.0f;

	s = FindGameObject<Stage>();
}

Coin::~Coin()
{
	DeleteGraph(coinImage);
	DeleteSoundMem(coinSound);
}

void Coin::Update()
{
	p = FindGameObject<Player>();

	// ���A�j���[�V����
	animTimer += Time::DeltaTime();
	if (animTimer >= 0.1f)
	{
		patternX += 1;
		animTimer = 0.0f;
		if (patternX >= 3)
		{
			patternX = 0;
		}
	}

	//���ꂽ��
	if (got)
	{
		position.y += v;//���V���^������������c
		v += 9.8f / 60; // �d��/60�t���[��

		destroyTimer += Time::DeltaTime();
		if (destroyTimer >= destroyTimeLimit)
		{
			if (!nowPlaySE)
			{
				PlaySoundMem(coinSound, DX_PLAYTYPE_BACK);
				nowPlaySE = true;
				p->gotCoin += 1;
			}
			// �擾
			CoinDraw = false;
			destroyCountDownTimer();
		}
		return;			 //�I���I��I�ȏ�I�F���U�I
	}

	//�����O

	//�����蔻��
   	VECTOR2 playerPos = p->position;	  //playerPos��player��position������

	//�����蔻��F"playerPos"��"position"������������
	if (CircleHit(position, playerPos + VECTOR2(0, 0+9), 29) || CircleHit(position, playerPos + VECTOR2(0, 30+9), 29))
	{
		got = true;	      //���ꂽ
		v = -2.5;//���˂��(������Ȃ̂Łu-�v����)
	}
}

void Coin::Draw()
{
	if (CoinDraw)
	{
		//DrawGraph(position.x, position.y - s->scroll, coinImage, TRUE);
		DrawRectGraph(position.x, position.y - s->scroll, patternX * 30, 0, 30, 30, coinImage, TRUE);
	}
}

void Coin::destroyCountDownTimer()
{
	destroyCountDown -= Time::DeltaTime();

	if (destroyCountDown <= 0)
	{
		DestroyMe(); //�R�C���̏���
	}
}
