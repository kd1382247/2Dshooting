#include "main.h"
#include "Scene.h"
#include"SceneManager.h"

void Scene::Draw2D()
{
	C_SceneManager::GetInstance().Draw();
}

void Scene::Update()
{
	C_SceneManager::GetInstance().PreUpdate();
	C_SceneManager::GetInstance().Update();
}

void Scene::Init()
{

}

void Scene::Release()
{
	
}

void Scene::ImGuiUpdate()
{
	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_Once);

	// デバッグウィンドウ
	if (ImGui::Begin("Debug Window"))
	{
		ImGui::Text("time : %f",m_time );
	}
	ImGui::End();
}
