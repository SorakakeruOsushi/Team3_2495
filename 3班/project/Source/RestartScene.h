#pragma once
#include "../Library/SceneBase.h"

class RestartScene : public SceneBase
{
public:
	RestartScene();
	~RestartScene();
	void Update() override;
	void Draw() override;

	//int jumpSE; // SE リセット音

	int resetTextImage; // 画像「RESET!」の文字画像
};

