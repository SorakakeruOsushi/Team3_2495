#include "RestartScene.h"
#include "Screen.h"
#include <cassert>

RestartScene::RestartScene()
{
	//uRESET!v
	//resetTextImage = LoadGraph("data/image/XA1/xRESET.png"); 
	//	assert(resetTextImage > 0);
}
RestartScene::~RestartScene()
{
	//DeleteGraph(resetTextImage);
}
void RestartScene::Update()
{
	// PlayScene‚Ö
	SceneManager::ChangeScene("PLAY");
}

void RestartScene::Draw()
{
	// [RESET!]•\Ž¦
	//DrawGraph(30 * 8.5, 200, resetTextImage, TRUE);
}
