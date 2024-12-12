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
	XINPUT_STATE input; //PAD操作用変数

public:
	TitleScene();
	~TitleScene();
	void Update() override;
	void Draw() override;

	int titleImage;			// 画像 タイトル画面
	int titleLogoImage;		// 画像 タイトルロゴ
	int titleBGImage;		// 画像 タイトル背景
	//int pushKeyTextImage;   // 画像「PUSH ANY KEY」の文字画像

	float DrawKeyTimer;		// タイマー 
	bool IsDraw;				// 描画
};
