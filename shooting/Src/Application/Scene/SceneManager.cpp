#include "SceneManager.h"

void C_SceneManager::Draw()
{
	m_currentScene->Draw();
}

void C_SceneManager::PreUpdate()
{
	if (e_currentSceneType != e_nextSceneType)
	{
		ChangeScene(e_nextSceneType);
	}
}

void C_SceneManager::Update()
{
	m_currentScene->Update();
}

void C_SceneManager::Init()
{
	ChangeScene(e_currentSceneType);
}

void C_SceneManager::Release()
{

}
