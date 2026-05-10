#pragma once

#include"Scene/TitleScene/TitleScene.h"
#include"Scene/GameScene/GameScene.h"

class C_SceneManager
{
public:

	enum SceneType
	{
		Title,
		Game,
		Restart
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
		case Restart:
			// リスタートする場合ゲームシーンを生成し、現在と次のシーンタイプを同じにする
			m_currentScene = std::make_shared<C_GameScene>();
			a_sceneType = Game;
			e_nextSceneType = Game;
			break;
		}
		e_currentSceneType = a_sceneType;
	}

	void SetNextSceneType(SceneType a_nextScene)
	{
		e_nextSceneType = a_nextScene;
	}

	void PreUpdate();
	void Update();
	void Draw();
	

private:

	void Init();
	void Release();

	

	std::shared_ptr<C_BaseScene>m_currentScene;

	SceneType e_currentSceneType=SceneType::Title;
	SceneType e_nextSceneType=e_currentSceneType;

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