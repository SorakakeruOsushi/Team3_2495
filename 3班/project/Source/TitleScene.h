#pragma once
#include "../Library/SceneBase.h"
#include "../Library/Utility.h"

/// <summary>
/// �^�C�g���V�[��
/// 
/// �^�C�g����\�����āA�L�[����������v���C�V�[���Ɉڍs����B
/// </summary>
class TitleScene : public SceneBase
{
public:
	TitleScene();
	~TitleScene();
	void Update() override;
	void Draw() override;

	XINPUT_STATE input; //PAD����p�ϐ�

	int titleImage;			//�^�C�g�����
	int pushKeyTextImage;   //�uPUSH ANY KEY�v

	const float DRAW_KEY_WAIT = 1.0f; // [PUSH SPACE KEY]�\���Ԋu(1.0sec) 
	const int MAX_ALPHA = 255;   // �ő�A���t�@�l

	int alpha;    // [PUSH SPACE KEY]�̃A���t�@�l 
	int ofset;    // ���Z����A���t�@�l 
	float DrawKeyTimer;  // �^�C�}�[ 
};
