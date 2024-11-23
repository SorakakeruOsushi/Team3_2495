#include <DxLib.h>
#include "../Library/sceneManager.h"
#include "PlayScene.h"
#include "Player.h"
#include "Block.h"
#include "Stage.h"
#include "time.h"


PlayScene::PlayScene()
{
	Stage* s = Instantiate<Stage>();

	//Instantiate<Player>();
	Instantiate<Block>();

	playTime = 0;
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	// タイトルへ戻る（隠し機能）
	if (CheckHitKey(KEY_INPUT_T)) 
	{
		SceneManager::ChangeScene("TITLE");
	}

	//タイマー(ゲーム進行中のみ加算)
	//if(gamePlay)
	{
		playTime += Time::DeltaTime();
	}
	//playTimeのカンスト(9999)
	if (playTime >= 9999)
	{
		playTime = 9999;
	}

}

void PlayScene::Draw()
{
	DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));

	SetFontSize(40);
	DrawString(900, 100, "N E X T", GetColor(255, 255, 255));

	//(x,y,色,文字列,変わる文字列)   「%d」を置き換える
	//「%6d」 ：６桁用意する　（if文でカンストさせればオーバーしない）
	//「%06d」：６桁用意する　空白を０で埋める
	//「%06d%%」：「ｎ％」表示出来る

	SetFontSize(25);
	//高さ(p->playerHeight)
	DrawFormatString(900, 400, GetColor(255, 255, 255), "SCORE:%04d", 810);
	
	//タイマー(playTime)
	DrawFormatString(900, 500, GetColor(255, 255, 255), "TIME(s):%04d", playTime);

	//現在のモードを表示(仮)
	DrawString(900, 600, "MODE：PLAYER", GetColor(255, 255, 255));

	SetFontSize(15);
	//モード変更
	DrawString(900, 650, "CHANGE：push [C] key", GetColor(255, 255, 255));
}
