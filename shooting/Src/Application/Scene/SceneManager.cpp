#include "SceneManager.h"

void C_SceneManager::Draw()
{
	m_currentScene->Draw();
}

void C_SceneManager::PreUpdate()
{
	if (m_currentSceneType != m_nextSceneType)
	{
		ChangeScene(m_nextSceneType);
	}
}

void C_SceneManager::Update()
{
	m_currentScene->Update();
}

void C_SceneManager::Init()
{
	ChangeScene(m_currentSceneType);
}

void C_SceneManager::Release()
{

}
