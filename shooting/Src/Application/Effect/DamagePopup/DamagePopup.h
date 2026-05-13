#pragma once

#include"../../Data/MatchupType/MatchupType.h"

class C_DamagePopup
{

public:




	C_DamagePopup() { Init(); }
	~C_DamagePopup() { Release(); }

	void Draw();
	void Update();

	void Spawn(Math::Vector2 a_pos,MatchupType a_matchupType);

private:

	void Init();
	void Release();

	KdTexture       m_weakTex;
	
	KdTexture       m_resistTex;
	
	KdTexture       m_normalTex;
	
	MatchupType     e_matchupType;
	Math::Vector2   m_pos = {};
	Math::Matrix    m_mat = {};
	float           m_displayCnt = {};
	bool            m_aliveFlg = {};
	float           m_alpha = {};

	

};