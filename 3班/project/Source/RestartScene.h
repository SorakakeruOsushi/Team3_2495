#pragma once
#include "../Library/SceneBase.h"

class RestartScene : public SceneBase
{
public:
	RestartScene();
	~RestartScene();
	void Update() override;
	void Draw() override;

	//int resetTextImage; // �摜�uRESET!�v
};

