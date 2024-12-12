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
	XINPUT_STATE input; //PAD����p�ϐ�

public:
	TitleScene();
	~TitleScene();
	void Update() override;
	void Draw() override;

	int titleImage;			// �摜 �^�C�g�����
	int titleLogoImage;		// �摜 �^�C�g�����S
	int titleBGImage;		// �摜 �^�C�g���w�i
	//int pushKeyTextImage;   // �摜�uPUSH ANY KEY�v�̕����摜

	float DrawKeyTimer;		// �^�C�}�[ 
	bool IsDraw;				// �`��
};
