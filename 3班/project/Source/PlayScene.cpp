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
	nextTextImage = LoadGraph("data/image/XA1/xNEXT.png");   // �摜�uNEXT�v
		assert(nextTextImage > 0);
	modeChangeTextImage = LoadGraph("data/image/XA1/xChangeCKey.png"); // �摜�uChangeC�v
		assert(modeChangeTextImage > 0);

	modeChangeTextImage = LoadGraph("data/image/XA1/xChangeCKey.png"); // �摜�uChangeC�v
		assert(modeChangeTextImage > 0);

	ladyTextImage = LoadGraph("data/image/XA1/x���f�BA1.png"); //�摜�u���f�B�c�v
		assert(ladyTextImage > 0);
	goTextImage = LoadGraph("data/image/XA1/x�S�[A1.png");	 //�摜�u�S�[�I�v
		assert(goTextImage > 0);
	// �����Ă�����?
	playModeTextImage = LoadGraph("data/image/XA1/xTETRA.png");	 // �v���C���[�h�̃f�t�H���g�́uTETRA�v
		assert(modeChangeTextImage > 0);
	playModeBGImage = LoadGraph("data/image/X/XmodeBGtetra.png");// �v���C���[�h�̃f�t�H���g�́uTETRA�v
		assert(modeChangeTextImage > 0);

	// �摜 �w�i1,2,3
	hBGImageI = LoadGraph("data/image/Back1.png");
		assert(hBGImageI > 0);
	hBGImageII = LoadGraph("data/image/Back2.png");
		assert(hBGImageII > 0);
	hBGImageIII = LoadGraph("data/image/Back3.png");
		assert(hBGImageIII > 0);
	// �����ǂݍ���
	titleBackVoice = LoadSoundMem("data/sound/���ʉ����{/voice/�u����������v.mp3");   // ���� [T]�^�C�g���ɖ߂�
		assert(titleBackVoice > 0);
	changeModeVoice = LoadSoundMem("data/sound/���ʉ����{/voice/�u�͂��́`����v.mp3");// ���� [C]�v���C���[�h�ύX
		assert(changeModeVoice > 0);

	g = nullptr;
	f = nullptr;

	playTime = 0.0f;		//�v���C����

	height = 0.0f;			//�����̍���(10)������
	bestHeight = 0.0f;

	changeBGheight = 50 /3;
	gameBGImage = hBGImageI; // �f�t�H���g�̔w�i�摜
}

PlayScene::~PlayScene()
{
	DeleteGraph(hBGImageI);			 // �摜 �v���C�V�[�� �w�i1
	DeleteGraph(hBGImageII);		 // �摜 �v���C�V�[�� �w�i2
	DeleteGraph(hBGImageIII);		 // �摜 �v���C�V�[�� �w�i3

	DeleteGraph(playModeTextImage);  // �摜�uTETRA�v���uBLOCK�v
	DeleteGraph(playModeTextImage);  // �摜  �v���C�G���A �v���C���[�h�w�i
	DeleteGraph(ladyTextImage);  // �摜�u���f�B�v
	DeleteGraph(goTextImage);  // �摜�u�S�[�v

	DeleteGraph(nextTextImage);		 // �摜�uNEXT�v
	DeleteGraph(modeChangeTextImage);// �摜�uCHANGE:[C]KEY�v

	DeleteSoundMem(titleBackVoice);  //�����uCHANGE:[C]KEY�v
	DeleteSoundMem(changeModeVoice); //�����uCHANGE:[C]KEY�v
}

void PlayScene::Update()
{
	//�p�b�h�p�֐�(���t���[���Ăяo��)
	GetJoypadXInputState(DX_INPUT_PAD1, &input);

	//[T]�^�C�g���֖߂�i�B���@�\�j
	if (CheckHitKey(KEY_INPUT_T))
	{
		// �T�E���h���I������܂ő҂� 
		PlaySoundMem(titleBackVoice, DX_PLAYTYPE_NORMAL);
		SceneManager::ChangeScene("TITLE");
	}
	//[Tab]�|�[�Y&����w���v
	if (KeyUtility::CheckTrigger(KEY_INPUT_TAB))
	{
		// COMING SOON
	}
	//[0]���X�^�[�g
	if (KeyUtility::CheckTrigger(KEY_INPUT_0))
	{
		//�P�t���[������"RESTART�V�[��"�ɍs���A"PLAY�V�[��"�ɖ߂��Ă���
		SceneManager::ChangeScene("RESTART");
	}
	//[1]�Z���\���؂�ւ�
	if (KeyUtility::CheckTrigger(KEY_INPUT_1))
	{
		s->cellBG = !s->cellBG;
	}
	
	
	if (!p->finished && !p->goaled)
	{
		//�^�C�}�[
		playTime += Time::DeltaTime();
		//playTime�̃J���X�g(9999)
		if (playTime >= 9999)
		{
			playTime = 9999;
		}

		//����(height)
		if ((s != nullptr) && (s->p != nullptr))
		{
			height = s->p->playerHeight / 30;
		}
	}

	// �v���C���[�h�؂�ւ�
	if ( (KeyUtility::CheckTrigger(KEY_INPUT_C)) || (input.Buttons[XINPUT_BUTTON_Y]) )
	{
		// �{�^�����������񂾎��������͂����
		if (!isButtonDown) {
			PlaySoundMem(changeModeVoice, DX_PLAYTYPE_BACK);
			//PlayMode�N���X����֐����Ăяo��
			pm->changeMode();
		}

		isButtonDown = true;
	}
	else {
		isButtonDown = false;
	}

	if (pm->playMode == 0) // �e�g�����[�h
	{
		playModeTextImage = LoadGraph("data/image/XA1/xTETRA.png");
			assert(playModeTextImage > 0);
		playModeBGImage = LoadGraph("data/image/TetraSDBig.png");
			assert(playModeBGImage > 0);
	}
	else 				   // �u���b�N���[�h
	{
		playModeTextImage = LoadGraph("data/image/XA1/xBLOCK.png");
			assert(playModeTextImage > 0);
		playModeBGImage = LoadGraph("data/image/BlockA1Big.png");
			assert(playModeBGImage > 0);
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
	
	//GOAL��FINISH���Ăяo��
	if (p->goaled && g == nullptr)
	{
		g = FindGameObject<GoalText>();
		g->resultTime = playTime;
		g->resultHeight = bestHeight;
		// �x�X�g�^�C���m�F 
		CheckBestTime();
		// �m�F 
		CheckBestScore();
		return;
	}
	if (p->finished && f == nullptr)
	{
		f = Instantiate<FinishText>();
		f->resultTime = playTime;
		f->resultHeight = bestHeight;
		return;
	}

}

void PlayScene::Draw()
{
	/*
	// �w�i�摜�\��(�{���͘A��png��z��ł�肽��)
	DrawGraph(0, -(Screen::HEIGHT * 0) - s->scroll, hBGImageI, TRUE);   //������P�Ԗ�
	DrawGraph(0, -(Screen::HEIGHT * 1) - s->scroll, hBGImageII, TRUE);  //������Q�Ԗ�
	DrawGraph(0, -(Screen::HEIGHT * 2) - s->scroll, hBGImageIII, TRUE); //������R�Ԗ�
	*/
	// �v���C�G���A�O�̂̔w�i
	DrawGraph(0, 0, gameBGImage, TRUE); // ���A�̔w�i

	// �v���C���[�h�w�i
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	DrawGraph(30 * 8, 0, playModeBGImage, TRUE); // TETRA/BLOCK
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�u���f�B�c�v���u�S�[�I�v
	DrawGraph(350, 250, ladyTextImage, TRUE); //�u���f�B�c�v
	DrawGraph(430, 230, goTextImage, TRUE);   //�u�S�[�I�v

	//�uNEXT�v�\��
	DrawGraph(1025, 50, nextTextImage, TRUE);

	SetFontSize(25);
	//����(playerHeight)
	DrawFormatString(1030, 400, GetColor(255, 255, 255), "HEIGHT:%.0f/50", fabs(height));
	//�X�R�A(Coin?)
	DrawFormatString(1030, 500, GetColor(255, 255, 255), "SCORE:%d", p->gotCoin);
	//�^�C��(playTime)
	DrawFormatString(1030, 600, GetColor(255, 255, 255), "TIME:%4.2f", playTime);
	
	SetFontSize(20);
	//�x�X�g�X�R�A(bestScore)
	DrawFormatString(1030, 530, GetColor(255, 255, 255), "BEST SCORE:%d", bestTime->GetBestScore() );
	//�x�X�g�^�C��(bestTime)
	DrawFormatString(1030, 630, GetColor(255, 255, 255), "BEST TIME:%4.2f", bestTime->GetBestTime() );

	//�v���C���[�h(TETRA/BLOCK)
	DrawGraph(5, 530, playModeTextImage, TRUE);  // playModeTextImage�ɓ����摜��؂�ւ���
	//�uCHANGE�F[C] KEY�v�\��
	DrawGraph(5, 600, modeChangeTextImage, TRUE);// modeChangeTextImage�ɓ����摜��؂�ւ���
}

void PlayScene::CheckBestTime()
{
	// �x�X�g�^�C�����X�V���� 
	if (playTime < bestTime->GetBestTime())
	{
		bestTime->SetBestTime(playTime);
	}
}

// �x�X�g�X�R�A���X�V
void PlayScene::CheckBestScore()
{
	if (p->gotCoin > bestTime->GetBestScore())
	{
		bestTime->SetBestScore(p->gotCoin);
	}
}

