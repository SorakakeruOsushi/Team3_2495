#include <DxLib.h>
#include <cassert>
#include "../Library/sceneManager.h"
#include "PlayScene.h"
#include "Player.h"
#include "Block.h"
#include "time.h"
#include "../Library/Utility.h"

PlayScene::PlayScene()
{
	pm = Instantiate<PlayMode>();
	s = Instantiate<Stage>();
	
	// �R���X�g���N�^
	p = FindGameObject<Player>();
		assert(pm != nullptr);
	pm = FindGameObject<PlayMode>();
		assert(pm != nullptr);
	bestTime = FindGameObject<BestTime>(); // �ō����_�Ǘ��pGameObject�̎擾 
		assert(bestTime != nullptr);

	Instantiate<Block>();
	// �摜�ǂݍ���
	stageTextImage = LoadGraph("data/image/font/StageFont.png"); // �摜 [�Œ�\���������P���̉摜�ɂ܂Ƃ߂�]
		assert(stageTextImage > 0);

	ladyTextImage = LoadGraph("data/image/XA1/x���f�BA1.png");	   //�摜�u���f�B�c�v
		assert(ladyTextImage > 0);
	goTextImage = LoadGraph("data/image/XA1/x�S�[A1.png");		   //�摜�u�S�[�I�v
		assert(goTextImage > 0);
	ladyGoTextImage = ladyTextImage;		// LadyGo�̃f�t�H���g�́uLady�v
	
	tetraModeTextImage = LoadGraph("data/image/font/TETRA.png"); // �摜�uTETRA�v
		assert(tetraModeTextImage > 0);
	blockModeTextImage = LoadGraph("data/image/font/Block.png"); // �摜�uBLOCK�v
		assert(blockModeTextImage > 0);
	playModeTextImage = tetraModeTextImage;	// �v���C���[�h�̃f�t�H���g�́uTETRA�v

	tetraModeBGImage = LoadGraph("data/image/XA1/x�v���C���[�h�ĂƂ�.jpg");   // �摜 TETRA���[�h�̃v���C�G���A�w�i�摜
		assert(tetraModeBGImage > 0);
	blockModeBGImage = LoadGraph("data/image/XA1/x�v���C���[�h�Ԃ����.jpg"); // �摜 BLOCK���[�h�̃v���C�G���A�w�i�摜
		assert(blockModeBGImage > 0);
	playModeBGImage = tetraModeBGImage;		// �v���C���[�h�̃f�t�H���g�́uTETRA�v
	// �摜 �w�i1,2,3
	hBGImageI = LoadGraph("data/image/Back1.png");
		assert(hBGImageI > 0);
	hBGImageII = LoadGraph("data/image/Back2.png");
		assert(hBGImageII > 0);
	hBGImageIII = LoadGraph("data/image/Back3.png");
		assert(hBGImageIII > 0);
	gameBGImage = hBGImageI; // �f�t�H���g�̔w�i�摜
	// �摜 �|�[�Y���
	pauseImage = LoadGraph("data/image/xPause.png"); // �摜 �|�[�Y���
		assert(pauseImage > 0);
	//�uRESET!�v
	//resetTextImage = LoadGraph("data/image/XA1/xRESET.png"); // �摜�uRESET�v
	//	assert(resetTextImage > 0);

	// �����ǂݍ���
	titleBackSound = LoadSoundMem("data/sound/���ʉ����{/voice/�u����������v.mp3");   // �� [T]�^�C�g���ɖ߂�
		assert(titleBackSound > 0);
	tetraModeSound = LoadSoundMem("data/sound/���ʉ����{/voice/�u����������v.mp3");   // �� [C]�e�g�����[�h
		assert(tetraModeSound > 0);
	blockModeSound = LoadSoundMem("data/sound/���ʉ����{/voice/�u����������v.mp3");   // �� [C]�u���b�N���[�h
		assert(blockModeSound > 0);
	startSound = LoadSoundMem("data/sound/���ʉ����{/voice/�u����������v.mp3");   // �� �Q�[���J�n
		assert(startSound > 0);
	pauseSound = LoadSoundMem("data/sound/���ʉ����{/voice/�u����������v.mp3");   // �� [Tab]�|�[�Y
		assert(pauseSound > 0);
	//resetSound = LoadSoundMem("data/sound/���ʉ����{/voice/�u����������v.mp3");   // �� [0]���Z�b�g
	//	assert(resetSound > 0);

	g = nullptr;
	f = nullptr;

	playTime = 0.0f;		// �v���C����

	//IsReset = false;
	startCountDown = 5.0f;

	height = 0.0f;			// �����̍���(10)������
	bestHeight = 0.0f;		// ���S���̃��U���g�ŕ\��

	changeBGheight = 50 / 3;
}

PlayScene::~PlayScene()
{
	DeleteGraph(hBGImageI);			 // �摜 �v���C�V�[�� �w�i1
	DeleteGraph(hBGImageII);		 // �摜 �v���C�V�[�� �w�i2
	DeleteGraph(hBGImageIII);		 // �摜 �v���C�V�[�� �w�i3

	DeleteGraph(stageTextImage);	 // �摜 [�Œ�\���������P���̉摜�ɂ܂Ƃ߂�]

	DeleteGraph(tetraModeTextImage); // �摜�uTETRA�v
	DeleteGraph(blockModeTextImage); // �摜�uBLOCK�v
	DeleteGraph(tetraModeBGImage);   // �摜 TETRA���[�h�w�i
	DeleteGraph(blockModeBGImage);   // �摜 BLOCK���[�h�w�i
	DeleteGraph(ladyTextImage);		 // �摜�u���f�B�v
	DeleteGraph(goTextImage);		 // �摜�u�S�[�v

	DeleteGraph(pauseImage);		 // �摜 �|�[�Y���
	//DeleteGraph(resetTextImage);	 // �摜�uRESET�v

	DeleteSoundMem(titleBackSound); // ���uCHANGE:[C]KEY�v
	DeleteSoundMem(tetraModeSound); // �� [C]�e�g�����[�h�ύX��
	DeleteSoundMem(blockModeSound); // �� [C]�u���b�N���[�h�ύX��
	DeleteSoundMem(startSound);		// �� �Q�[���J�n
	DeleteSoundMem(pauseSound);		// �� [Tab]�|�[�Y
	//DeleteSoundMem(resetSound);		// �� [0]���Z�b�g
}



void PlayScene::Update()
{
	//�p�b�h�p�֐�(���t���[���Ăяo��)
	GetJoypadXInputState(DX_INPUT_PAD1, &input);

	//[T]�^�C�g���֖߂�i�B���@�\�j
	if (CheckHitKey(KEY_INPUT_T))
	{
		// �T�E���h���I������܂ő҂� 
		PlaySoundMem(titleBackSound, DX_PLAYTYPE_NORMAL);
		SceneManager::ChangeScene("TITLE");
	}

	//�Q�[���J�n
	if (KeyUtility::CheckTrigger(KEY_INPUT_2));
	{
		//PlaySoundMem(startSound, DX_PLAYTYPE_BACK);
		pm->IsGameStart = true;
	}


	if (!pm->IsGameStart)
	{
		return;
	}
	//[0]���X�^�[�g
	if (KeyUtility::CheckTrigger(KEY_INPUT_0))
	{
		//IsReset = true;
		//PlaySoundMem(resetSound, DX_PLAYTYPE_BACK); // SE�Đ�
		//�P�t���[������"RESTART�V�[��"�ɍs���A"PLAY�V�[��"�ɖ߂��Ă���
		SceneManager::ChangeScene("RESTART");
	}
	//[Tab]�|�[�Y&����w���v
	if (!pm->IsGamePause) // �|�[�Y������Ȃ�
	{
		if ((KeyUtility::CheckTrigger(KEY_INPUT_TAB)) || (input.Buttons[XINPUT_BUTTON_START]))
		{
			// �{�^�����������񂾎��������͂����
			if (!isButtonDown)
			{
				PlaySoundMem(pauseSound, DX_PLAYTYPE_BACK);
				pm->IsGamePause = true; // �Q�[�����f
			}
			isButtonDown = true;
		}
		else
		{
			isButtonDown = false;
		}
		if (pm->IsGamePause)
		{
			return;
		}
	}
	 else // �|�[�Y��
	{
		// [Tab] �^ [START]�܂���[A]
		if ( (KeyUtility::CheckTrigger(KEY_INPUT_TAB)) || (input.Buttons[XINPUT_BUTTON_START]) || (input.Buttons[XINPUT_BUTTON_A]))
		{
			// �{�^�����������񂾎��������͂����
			if (!isButtonDown)
			{
				//PlaySoundMem(pauseSound, DX_PLAYTYPE_BACK); // �Ⴄ��?
				pm->IsGamePause = false; // �Q�[���ĊJ
			}
			isButtonDown = true;
		}
		else
		{
			isButtonDown = false;
		}
		if (pm->IsGamePause)
		{
			return;
		}
	}

	//[1]�Z���\���؂�ւ�
	if (KeyUtility::CheckTrigger(KEY_INPUT_1))
	{
		s->cellBG = !s->cellBG;
	}
	//[C]�v���C���[�h�؂�ւ�
	if ((KeyUtility::CheckTrigger(KEY_INPUT_C)) || (input.Buttons[XINPUT_BUTTON_Y]))
	{
		// �{�^�����������񂾎��������͂����
		if (!isButtonDown)
		{
			pm->changeMode();
		}
		isButtonDown = true;
	}
	else
	{
		isButtonDown = false;
	}

	if (pm->playMode == 0) // �e�g�����[�h
	{
		//PlaySoundMem(tetraModeSound, DX_PLAYTYPE_BACK);
		playModeTextImage = tetraModeTextImage;
		playModeBGImage = tetraModeBGImage;
	}
	else 				   // �u���b�N���[�h
	{
		//PlaySoundMem(blockModeSound, DX_PLAYTYPE_BACK);
		playModeTextImage = blockModeTextImage;
		playModeBGImage = blockModeBGImage;
	}
	
	
	if (!p->finished && !p->goaled)
	{
		//����(height)
		if ((s != nullptr) && (s->p != nullptr))
		{
			height = s->p->playerHeight / 30;
		}
		//�ō����B�_(bestHeight)
		if(height > bestHeight)
		{
			bestHeight = height;
		}
		//�^�C�}�[
		playTime += Time::DeltaTime();
		//playTime�̃J���X�g(9999)
		if (playTime >= 9999)
		{
			playTime = 9999;
		}
	}

	//�w�i�̕\���؂�ւ�
	if ( (height >= changeBGheight * 0) && (height < changeBGheight * 1) )
	{
		gameBGImage = hBGImageI;
	}
	if ((height >= changeBGheight * 1) && (height < changeBGheight * 2))
	{
		gameBGImage = hBGImageII;
	}
	if ((height >= changeBGheight * 2) && (height < changeBGheight * 3))
	{
		gameBGImage = hBGImageIII;
	}
	//GOAL��FINISH�Ń��U���g���m��
	if (p->goaled && g == nullptr)
	{
		g = FindGameObject<GoalText>();
		//������50�Œ�
		// �X�R�A
		g->resultScore = p->gotCoin;
		// �v���C���ԁi�N���A���ԁj
		g->resultTime = playTime;

		// �x�X�g�^�C���m�F 
		CheckBestTime();
		// �x�X�g�X�R�A�m�F 
		CheckBestScore();
		return;
	}
	if (p->finished && f == nullptr)
	{
		f = Instantiate<FinishText>();
		// �ō����B�_
		f->resultHeight = bestHeight;
		// �X�R�A
		f->resultScore = p->gotCoin;
		// �v���C����
		f->resultTime = playTime;
		return;
	}

}

void PlayScene::Draw()
{
	// �v���C�G���A�O�̂̔w�i
	DrawGraph(0, 0, gameBGImage, TRUE); // ���A�̔w�i

	// �v���C���[�h�w�i
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	DrawGraph(30 * 8, 0, playModeBGImage, TRUE); // TETRA/BLOCK
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawGraph(0, 0, stageTextImage, TRUE);    // �Œ�\���̕���

	//�u���f�B�c�v���u�S�[�I�v
	DrawGraph(350, 250, ladyGoTextImage, TRUE); //�u���f�B�c�v�u�S�[�I�v
	

	SetFontSize(25);
	//����(playerHeight)

	DrawFormatString(1170, 420, GetColor(255, 255, 255), "%.0f/50", fabs(height));
	
	//�X�R�A(Coin?)
	DrawFormatString(1160, 470, GetColor(255, 255, 255), "%d", p->gotCoin);

	//�^�C��(playTime)
	DrawFormatString(1135, 525, GetColor(255, 255, 255), "%4.2f", playTime);
	
	SetFontSize(20);
	//�x�X�g�X�R�A(bestScore)
	DrawFormatString(1155, 605, GetColor(255, 255, 255), "%0d", bestTime->GetBestScore() );
	//�x�X�g�^�C��(bestTime)
	DrawFormatString(1135, 635, GetColor(255, 255, 255), "%4.2f", bestTime->GetBestTime() );

	//�v���C���[�h(TETRA/BLOCK)
	DrawGraph(5, 530, playModeTextImage, TRUE);   // playModeTextImage�ɓ����摜��؂�ւ���

	//�uRESET!�v�\��
	//if (IsReset) 
	{
		//DrawGraph(30 * 8.5, 200, resetTextImage, TRUE);
	}


	//�|�[�Y��ʁ@(�\�����o�O)
	if (pm->IsGamePause)
	{
		// ��ʂ��Â�����
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200); //���߂���
		DrawBox(0, 0, 1280, 720, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //���߂��Ȃ�
		// �|�[�Y���
		DrawGraph(0, 0, pauseImage, TRUE);
	}

	SetFontSize(100);
	//DrawFormatString(300, 300, GetColor(255, 255, 255), "%0.0f", startCountDown);
	DrawString(300, 300, "�e�X�g���A[2]�ŃQ�[���J�n", GetColor(255, 255, 0), TRUE);
}

// �x�X�g�X�R�A���X�V
void PlayScene::CheckBestScore()
{
	if (p->gotCoin > bestTime->GetBestScore())
	{
		bestTime->SetBestScore(p->gotCoin);
		g->IsNewBestScore = true;
	}
}

void PlayScene::CheckBestTime()
{
	// �x�X�g�^�C�����X�V���� 
	if (playTime < bestTime->GetBestTime())
	{
		bestTime->SetBestTime(playTime);
		g->IsNewBestTime = true;
	}
}

