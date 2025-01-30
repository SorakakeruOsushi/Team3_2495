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
	stageTextImage = LoadGraph("data/image/font/PlayFont.png"); // �摜 [�Œ�\���������P���̉摜�ɂ܂Ƃ߂�]
		assert(stageTextImage > 0);
	resetTextImage = LoadGraph("data/image/font/Reset.png");	 // �摜�uRESET[0]KEY�v
		assert(resetTextImage > 0);
	coinSPoneImage = LoadGraph("data/image/coinSPone.png");	     // �摜SP�R�C������
		assert(coinSPoneImage > 0);

	readyTextImage = LoadGraph("data/image/font/READY.png");   //�摜�u���f�B�c�v
		assert(readyTextImage > 0);
	goTextImage = LoadGraph("data/image/font/GO.png");		   //�摜�u�S�[�I�v
		assert(goTextImage > 0);
	readyGoTextImage = readyTextImage;		// LadyGo�̃f�t�H���g�́uLady�v
	
	tetraModeTextImage = LoadGraph("data/image/font/TETRA.png"); // �摜�uTETRA�v
		assert(tetraModeTextImage > 0);
	blockModeTextImage = LoadGraph("data/image/font/Block.png"); // �摜�uBLOCK�v
		assert(blockModeTextImage > 0);
	playModeTextImage = tetraModeTextImage;	// �v���C���[�h�̃f�t�H���g�́uTETRA�v

	blockModeBGImage = LoadGraph("data/image/BBBG.png"); // �摜 BLOCK���[�h�̃v���C�G���A�w�i�摜
		assert(blockModeBGImage > 0);
	playModeBGImage = NULL;	// �v���C���[�h�̃f�t�H���g�́uTETRA�v

	gameBGImage = LoadGraph("data/image/�w�i/LongBack.jpeg");    // �摜 �w�i
		assert(gameBGImage > 0);
	cellMaxImage = LoadGraph("data/image/�w�i/cell.png");		 // �摜 �}�X�ڑ傫��
		assert(cellMaxImage > 0);
	
	// �����ǂݍ���
	titleBackSound = LoadSoundMem("data/sound/GameSE/�X�^�[�g�{�^���S.mp3"); // �� [T]�^�C�g���ɖ߂�
		assert(titleBackSound > 0);
	startSound = LoadSoundMem("data/sound/GameSE/�z�C�b�X���E�P��02.mp3");   // �� �Q�[���J�n
		assert(startSound > 0);
	resetSound = LoadSoundMem("data/sound/GameSE/���Z�b�g��.mp3");			 // �� [0]���Z�b�g
		assert(resetSound > 0);
	modeChangeSound = LoadSoundMem("data/sound/GameSE/�{�^���P.mp3");		 // �� [C]���[�h�ύX
		assert(modeChangeSound > 0);

	g = nullptr;
	f = nullptr;

	playTime = 0.0f;		// �v���C����

	startCountDown = 3.0f;

	height = 0.0f;			// �����̍���(10)������
	bestHeight = 0.0f;		// ���S���̃��U���g�ŕ\��
	score = 0.0f;

	coinSPoneDraw = false;
}

PlayScene::~PlayScene()
{
	DeleteGraph(gameBGImage);		 // �摜 �v���C�V�[���w�i
	DeleteGraph(cellMaxImage);       // �摜 �Z���}�b�N�X

	DeleteGraph(stageTextImage);	 // �摜 [�Œ�\���������P���̉摜�ɂ܂Ƃ߂�]
	DeleteGraph(coinSPoneImage);	 // �摜 SP�R�C������

	DeleteGraph(tetraModeTextImage); // �摜�uTETRA�v
	DeleteGraph(blockModeTextImage); // �摜�uBLOCK�v
	DeleteGraph(blockModeBGImage);   // �摜 BLOCK���[�h�w�i
	DeleteGraph(readyTextImage);	 // �摜�u���f�B�v
	DeleteGraph(goTextImage);		 // �摜�u�S�[�v

	DeleteSoundMem(titleBackSound); // ���uCHANGE:[C]KEY�v
	DeleteSoundMem(startSound);		// �� �Q�[���J�n
	DeleteSoundMem(resetSound);		// �� [0]���Z�b�g
	DeleteSoundMem(modeChangeSound);// �� [C]���[�h�ύX��
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

	startCountDown -= Time::DeltaTime();
	
	//�Q�[���J�n
	if ((startCountDown <= 1.0f) && (startCountDown > 0.75f))
	{
		readyGoTextImage = NULL;
	}
	if ( (startCountDown <= 0.75f) && (startCountDown > 0.0f) )
	{
		readyGoTextImage = goTextImage;
	}
	if (startCountDown <= 0.0f && !pm->IsGameStart)
	{
		readyGoTextImage = NULL;
		PlaySoundMem(startSound, DX_PLAYTYPE_BACK);
		pm->IsGameStart = true;
	}


	if (!pm->IsGameStart)
	{
		return;
	}
	//[0]���X�^�[�g
	if (KeyUtility::CheckTrigger(KEY_INPUT_0))
	{
		PlaySoundMem(resetSound, DX_PLAYTYPE_NORMAL); // ���Z�b�gSE�Đ�
		//�P�t���[������"RESTART�V�[��"�ɍs���A"PLAY�V�[��"�ɖ߂��Ă���
		SceneManager::ChangeScene("RESTART");
	}

	//[C]�v���C���[�h�؂�ւ�
	if ((KeyUtility::CheckTrigger(KEY_INPUT_C)) || (input.Buttons[XINPUT_BUTTON_Y]))
	{
		// �{�^�����������񂾎��������͂����
		if (!isButtonDown)
		{
			PlaySoundMem(modeChangeSound, DX_PLAYTYPE_BACK);
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
		playModeTextImage = tetraModeTextImage;
		playModeBGImage = NULL;
	}
	else 				   // �u���b�N���[�h
	{
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

	//GOAL��FINISH�Ń��U���g���m��
	if (p->goaled && g == nullptr)
	{
		g = FindGameObject<GoalText>();
		//������50�Œ�
		// �X�R�A
		g->resultScore = score;
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
		f->resultScore = score;
		// �v���C����
		f->resultTime = playTime;
		return;
	}

	//�X�R�A�v�Z
	score = ((int)p->gotCoin * 1000.0f) + ((int)p->gotCoinSP * 5000.0f) - (playTime * 5.0f);
}

void PlayScene::Draw()
{
	// �Œ�w�i
	DrawGraph(0, -810 - s->scroll, gameBGImage, TRUE);

	// �v���C���[�h�w�i
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
	DrawGraph(30 * 8, 0, playModeBGImage, TRUE); // TETRA/BLOCK
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�}�X��
	if (pm->playMode == 1)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 20);
		DrawGraph(CHIP_SIZE * 8, /*-1440*/ - s->scroll, cellMaxImage, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	//�Œ�\�������摜
	DrawGraph(0, 0, stageTextImage, TRUE);    // �Œ�\���̕���

	//NEXT�̉�
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50); // ���߂���
	DrawBox(1115-30, 90, 1175+30+5, 220, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);// ���߂��Ȃ�

	//�Œ�\�������摜
	DrawGraph(0, 0, resetTextImage, TRUE);    //�uRESET[0]KEY�v

	//�u���f�B�c�v���u�S�[�I�v
	DrawGraph(0, 0, readyGoTextImage, TRUE); //�u���f�B�c�v�u�S�[�I�v
	
	SetFontSize(25);
	//����(playerHeight)//
	DrawFormatString(1145, 375, GetColor(255, 255, 255), "%4.0f/30", fabs(height));
	
	//�^�C��(playTime)
	DrawFormatString(1145, 423, GetColor(255, 255, 255), "%7.2f", playTime);

	//�R�C��(gotCoin)//
	DrawFormatString(1145, 472, GetColor(255, 255, 255), "%4.0d/20", p->gotCoin);

	//�����ȃR�C��
	for (int i = 0; i < 3; i++)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 80);
		DrawGraph(1170 + 25 * i, 472 + 25, coinSPoneImage, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	//�R�C��(gotCoinSPone)
	for (int i = 0; i < p->gotCoinSP; i++)
	{
		DrawGraph(1170 + 25*i, 472+25, coinSPoneImage, TRUE);
	}
	
	//�X�R�A//
	DrawFormatString(1145, 534, GetColor(255, 255, 255), "%7.0f", score);

	SetFontSize(20);
	//�x�X�g�X�R�A(bestScore)//
	DrawFormatString(1170, 595, GetColor(255, 255, 255), "%4.0f", bestTime->GetBestScore() );
	//�x�X�g�^�C��(bestTime)
	DrawFormatString(1170, 625, GetColor(255, 255, 255), "%4.2f", bestTime->GetBestTime() );

	//�v���C���[�h(TETRA/BLOCK)
	DrawGraph(0, 0, playModeTextImage, TRUE);   // playModeTextImage�ɓ����摜��؂�ւ���

}

// �x�X�g�X�R�A���X�V
void PlayScene::CheckBestScore()
{
	if (score > bestTime->GetBestScore())
	{
		bestTime->SetBestScore(score);
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

