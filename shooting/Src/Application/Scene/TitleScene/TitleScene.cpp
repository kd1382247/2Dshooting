#include "TitleScene.h"

#include"../SceneManager.h"

void C_TitleScene::Draw()
{

}

void C_TitleScene::Update()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		C_SceneManager::GetInstance().SetNextSceneType(C_SceneManager::SceneType::Game);
	}
}

void C_TitleScene::Init()
{

}
