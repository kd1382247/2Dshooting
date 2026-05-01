#include "TitleScene.h"

#include"../../SceneManager.h"
#include"Title.h"

void C_TitleScene::Draw()
{
	m_title->Draw();
}

void C_TitleScene::Update()
{

	

	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		C_SceneManager::GetInstance().SetNextSceneType(C_SceneManager::SceneType::Game);
	}


	m_title->Update();
}

void C_TitleScene::Init()
{
	m_title = std::make_shared<C_Title>();
}
