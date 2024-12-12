#include "Coin.h"
#include "Player.h"
#include "Stage.h"

Coin::Coin()
{
	//�R���X�g���N�^�ŊG�����[�h
	coinImage = LoadGraph("data/image/Xgoal.png");
	got = false;

	s = FindGameObject<Stage>();
	p = FindGameObject<Player>();
}

Coin::~Coin()
{
	DeleteGraph(coinImage);
}

void Coin::Update()
{
	//���ꂽ��
	if (got)
	{
		p->gotCoin += 1;

		position.y += v; //���V���^������������c
		v += 9.8f / 60;  // �d��/60�t���[��

		counter -= 1;
		if (counter == 0)
		{
			//�擾
			DestroyMe(); //���ʂ����Ȃ�����Ȃ��I
		}
		return;			 //�I���I��I�ȏ�I�F���U�I
	}

	//�����O
		//�����蔻��
	VECTOR2 playerPos = p->position;	  //playerPos��player��position������

	//�����蔻��F"playerPos"��"position"������������
	if (CircleHit(position, playerPos, 30))
	{
		got = true;	  //���ꂽ�I
		counter = 20; //���ւ̃J�E���^�[�Q�O�t���[��
		v = -2.5;	  //���˂��(������Ȃ̂Łu-�v����)
	}
}

void Coin::Draw()
{
	DrawGraph(position.x - s->scroll, position.y, coinImage, TRUE);
}


//�������i�񎟕������j�@
//[���w]�@y = ax ^ 2 + bx + c;	�@		���܂��A�g���܂���P�h�I
//[����]�@v = v0 + at�^v = v0 + gt�@	����:�� = v0:���� + gt:�����@��:����
//[�v���O����]�@x += v; v += g;