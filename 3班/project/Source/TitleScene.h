#pragma once
#include "../Library/SceneBase.h"
#include "../Library/Utility.h" 

/// <summary>
/// タイトルシーン
/// 
/// タイトルを表示して、キーを押したらプレイシーンに移行する。
/// </summary>
class TitleScene : public SceneBase
{
public:
	TitleScene();
	~TitleScene();
	void Update() override;
	void Draw() override;

	int titleImage;

	XINPUT_STATE input; //PAD操作用変数
};
