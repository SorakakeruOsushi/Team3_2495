#include "GoalText.h"
#include "../Library/time.h"
#include <cassert>

GoalText::GoalText()
{
	goalBGImage = LoadGraph("data/image/Goal.JPG");						  // �摜 �S�[���w�i�摜
		assert(goalBGImage > 0);
	finishTextImage = LoadGraph("data/image/font/Finish.png");		      // �摜�uFINISH�v
		assert(finishTextImage > 0);
	gameClearTextImage = LoadGraph("data/image/font/Clear.png");	      // �摜�uGAME CLEAR�v
		assert(gameClearTextImage > 0);
	newRecordTextImage = LoadGraph("data/image/font/NewRecord.png");	  // �摜�uNEW RECORD!�v
		assert(newRecordTextImage > 0);
	
	heightTextImage = LoadGraph("data/image/font/���ʂɓ�������O�̃t�H���g����/Hight.png"); // �摜�uHEIGHT�v
		assert(heightTextImage > 0);
	scoreTextImage = LoadGraph("data/image/font/���ʂɓ�������O�̃t�H���g����/Score.png");  // �摜�uSCORE�v
		assert(scoreTextImage > 0);
	timeTextImage = LoadGraph("data/image/font/���ʂɓ�������O�̃t�H���g����/Time.png");    // �摜�uTIME�v
		assert(timeTextImage > 0);

	titleBackKeyTextImage = LoadGraph("data/image/font/PushSpace.png"); // �摜�uTITLE�ɖ߂�v
		assert(titleBackKeyTextImage > 0);

	titleBackSound = LoadSoundMem("data/sound/GameSE/�{�^���P.mp3");
		assert(titleBackSound > 0);
	//goalSound = LoadSoundMem("data/sound/���ʉ����{/voice/�u�ς�ς��ρ[��I�v.mp3");
	goalSound = LoadSoundMem("data/sound/GameSE/�������S�[��SE.mp3");
	//goalSound = LoadSoundMem("data/sound/GameSE/�S�[��.mp3");
		assert(goalSound > 0);
	PlaySoundMem(goalSound, DX_PLAYTYPE_BACK); // �S�[���{�C�X�Đ�

	timer = 0.0f;
	alpha = 0.0f;

	DrawKeyTimer = 0.0f;
	IsDraw = false;

	IsNewBestScore = false;
	IsNewBestTime = false;

	resultScore = 0;   // �X�R�A����
	resultTime = 0.0f; // �^�C������
}

GoalText::~GoalText()
{
	DeleteGraph(goalBGImage);
	DeleteGraph(finishTextImage);
	DeleteGraph(gameClearTextImage);
	DeleteGraph(newRecordTextImage);
	DeleteGraph(titleBackKeyTextImage);

	DeleteGraph(heightTextImage);
	DeleteGraph(scoreTextImage);
	DeleteGraph(timeTextImage);

	DeleteSoundMem(titleBackSound);
	DeleteSoundMem(goalSound);
}

void GoalText::Update()
{
	//�p�b�h�p�֐�(���t���[���Ăяo��)
	GetJoypadXInputState(DX_INPUT_PAD1, &input);

	//Time::DeltaTime();�F�b�ő���邽�߃��j�^�[���\�ɍ��E����Ȃ�
	timer += Time::DeltaTime();

	if (timer >= 7.0f)
	{
		//�u�^�C�g���ɖ߂�v�\���ؑ�
		DrawKeyTimer += Time::DeltaTime();
		if (DrawKeyTimer >= 0.5f)
		{
			IsDraw = !IsDraw;
			DrawKeyTimer = 0.0f;
		}

		if ((CheckHitKey(KEY_INPUT_SPACE)) || (input.Buttons[XINPUT_BUTTON_A]) || (input.Buttons[XINPUT_BUTTON_B]))
		{
			// �T�E���h���I������܂ő҂� 
			PlaySoundMem(titleBackSound, DX_PLAYTYPE_NORMAL);
			SceneManager::ChangeScene("TITLE");
		}
	}

	//alpha�l ����
	if (timer >= 0.5f)
	{
		alpha += 2.5f;
		if (alpha >= 255)
		{
			alpha = 255;
		}
	}
}

void GoalText::Draw()
{
	//�uFINISH!�v�\��
	DrawGraph(0, 0, finishTextImage, TRUE);
	// �S�[���摜 �\��
	if (timer >= 0.3f)
	{
		// ���U���g��ʔw�i
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha); //	�A���t�@�u�����f�B���O
		DrawGraph(0, 0, goalBGImage, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	 // ���߂��Ȃ�
	}

	if (timer >= 3.5f)
	{
		// �Ó]
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50); // ���߂���
		DrawBox(0, 0, 1280, 720, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);   // ���߂��Ȃ�
	}

	//�uGAME CLEAR!�v�\��
	if (timer >= 4.0f)
	{
		DrawGraph(0, -175, gameClearTextImage, TRUE);
	}
	SetFontSize(80);
	if (timer >= 5.0f)
	{
		// ����(�Œ�\��)
		DrawGraph(326, 300, heightTextImage, TRUE);
		DrawString(615, 300, " 50/50", GetColor(255, 255, 255)); // �n���{�e
	}
	if (timer >= 5.5f)
	{
		// �X�R�A�\��
		DrawGraph(340, 400, scoreTextImage, TRUE);
		DrawFormatString(615, 400, GetColor(255, 255, 255)," %.0f", resultScore);
		if (IsNewBestScore)
		{
			DrawGraph(900, 400, newRecordTextImage, TRUE);
		}

	}
	if (timer >= 6.0f)
	{
		// �^�C���\��
		DrawGraph(421, 500, timeTextImage, TRUE);
		DrawFormatString(615, 500, GetColor(255, 255, 255), " %.2f", resultTime);
		if (IsNewBestTime)
		{
			DrawGraph(900, 500, newRecordTextImage, TRUE);
		}
	}

	// "�X�y�[�X�L�[�ŏI��"
	if (IsDraw)
	{
		//�u�X�y�[�X�L�[�������ďI���v�\��
		DrawGraph(0, 0, titleBackKeyTextImage, TRUE);
	}

	//�����p�Z���^�[�h�b�g
	//DrawString(1280/2, 720/2, ".", GetColor(255, 0, 0), TRUE);
}
