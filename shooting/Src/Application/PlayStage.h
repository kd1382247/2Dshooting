#pragma once
#include "Player.h"
#include "GameUI.h"

class C_PlayStage
{
public:

	C_PlayStage();
	~C_PlayStage();

	void Draw();
	void Update();
	void Init();

	void Release();

private:
	
	C_Player m_player;
	C_GameUI m_ui;
};