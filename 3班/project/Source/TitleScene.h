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

	int titleImage;			// �摜�^�C�g�����
	int pushKeyTextImage;   // �摜�uPUSH ANY KEY�v�̕����摜
	float DrawKeyTimer;				  // �^�C�}�[ 
};
