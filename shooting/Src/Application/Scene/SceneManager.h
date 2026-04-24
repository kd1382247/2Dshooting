#pragma once

#include"TitleScene/TitleScene.h"
#include"GameScene/GameScene.h"

class C_SceneManager
{
public:

	static C_SceneManager& GetInstance()
	{
		static C_SceneManager instance;
		return instance;
	}

	C_BaseScene* currentState = nullptr;

	void ChangeState(C_BaseScene* a_newState)
	{
		delete currentState;
		currentState = a_newState;
		currentState->Init();
	}

	void Update()
	{
		currentState->Update();
	}

	void Draw()
	{
		currentState->Draw();
	}

	void Release()
	{
		if(currentState!=nullptr)
		{
			delete currentState;
		}
	}
private:

	C_SceneManager() {}

};

#define SCENEMANAGER C_SceneManager::GetInstance()