#pragma once

//前方宣言
class C_Player;
class C_GameUI;
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
	
	C_Player *m_player=  nullptr;
	C_GameUI *m_gameUi=  nullptr;
};