#include "RestartScene.h"
#include "Screen.h"
#include <cassert>

RestartScene::RestartScene()
{
	//「RESET!」
	//resetTextImage = LoadGraph("data/image/XA1/xRESET.png"); 
	//	assert(resetTextImage > 0);
}
RestartScene::~RestartScene()
{
	//DeleteGraph(resetTextImage);
}
void RestartScene::Update()
{
	// PlaySceneへ
	SceneManager::ChangeScene("PLAY");
}

void RestartScene::Draw()
{
	// [RESET!]表示
	//DrawGraph(30 * 8.5, 200, resetTextImage, TRUE);
}
