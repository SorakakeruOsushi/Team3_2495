#pragma once
#include "../Library/SceneBase.h"

class PlayScene : public SceneBase
{
public:
	PlayScene();
	~PlayScene();
	void Update() override;
	void Draw() override;

	//�v���C���[�摜�\���e�X�g�p
	int pngImage;
	int jpgImage;
};