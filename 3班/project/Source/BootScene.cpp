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
	SceneManager::ChangeScene("TITLE"); // ‹N“®‚ªI‚í‚Á‚½‚çTitle‚ğ•\¦
}

void BootScene::Draw()
{
}
