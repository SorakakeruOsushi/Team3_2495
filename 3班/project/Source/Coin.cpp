#include "Coin.h"
#include <cassert>
#include "Player.h"
#include "Stage.h"
#include "Time.h"

Coin::Coin()
{
	//�R���X�g���N�^�ŊG�����[�h
	coinImage = LoadGraph("data/image/Coin.PNG");			  // �摜 �R�C��
		assert(coinImage > 0);
	coinSound = LoadSoundMem("data/sound/GameSE/�R�C��.mp3"); // �� �R�C���擾
		assert(coinSound > 0);
	
	SetDrawOrder(6);

	got = false;
	CoinDraw = true;

	destroyTimer = 0.0f;     //�R�C���\���^�C�}�[
	destroyTimeLimit = 0.1f; //�R�C���\������

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
		DrawGraph(position.x, position.y - s->scroll, coinImage, TRUE);
	}
}

void Coin::destroyCountDownTimer()
{
	destroyCountDown -= Time::DeltaTime();

	if (destroyCountDown <= 0)
	{
		p->gotCoin += 1;
		DestroyMe(); //�R�C���̏���
	}
}
