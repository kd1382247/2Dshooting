#pragma once

//前方宣言
class C_Player;
class C_GameUI;

class C_PlayStage
{
public:

	C_PlayStage() { Init(); }
	~C_PlayStage(){}

	void Draw();
	void Update();
	

private:
	
	void Init();
	void Release();

	std::shared_ptr<C_Player> m_player;
	std::shared_ptr<C_GameUI> m_gameUi;

	
};