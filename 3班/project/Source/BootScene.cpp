#include "BootScene.h"
#include "../Library/SceneManager.h"
#include "BestTime.h"

BootScene::BootScene()
{
	BestTime* b = Instantiate<BestTime>();
	b->DontDestroyOnLoad();
}

BootScene::~BootScene()
{
}

void BootScene::Update()
{
	SceneManager::ChangeScene("TITLE"); // 起動が終わったらTitleを表示
}

void BootScene::Draw()
{
}
