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

	int titleImage;			//タイトル画面
	int pushKeyTextImage;   //「PUSH ANY KEY」

	const float DRAW_KEY_WAIT = 1.0f; // [PUSH SPACE KEY]表示間隔(1.0sec) 
	const int MAX_ALPHA = 255;   // 最大アルファ値

	int alpha;    // [PUSH SPACE KEY]のアルファ値 
	int ofset;    // 加算するアルファ値 
	float DrawKeyTimer;  // タイマー 
};
