#pragma once

#include"TitleScene/TitleScene.h"
#include"GameScene/GameScene.h"

class C_SceneManager
{
public:

	enum SceneType
	{
		Title,
		Game
	};

	void ChangeScene(SceneType a_sceneType)
	{
		switch (a_sceneType)
		{
		case Title:
			m_currentScene = std::make_shared<C_TitleScene>();
			break;
		case Game:
			m_currentScene = std::make_shared<C_GameScene>();
			break;
		}
		m_currentSceneType = a_sceneType;
	}

	void SetNextSceneType(SceneType a_nextScene)
	{
		m_nextSceneType = a_nextScene;
	}

	void PreUpdate();
	void Update();
	void Draw();
	
private:

	void Init();
	void Release();

	std::shared_ptr<C_BaseScene>m_currentScene;

	SceneType m_currentSceneType=SceneType::Title;
	SceneType m_nextSceneType=m_currentSceneType;

//シングルトンパータン
private:

	C_SceneManager() { Init(); }
	~C_SceneManager() { Release(); }

public:
	static C_SceneManager& GetInstance()
	{
		static C_SceneManager instance;
		return instance;
	}

};