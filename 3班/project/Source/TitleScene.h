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

	XINPUT_STATE input; //PAD操作用変数

	int titleImage;			// 画像タイトル画面
	int pushKeyTextImage;   // 画像「PUSH ANY KEY」の文字画像
	float DrawKeyTimer;				  // タイマー 
};
