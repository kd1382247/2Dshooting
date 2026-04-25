#include "Enemy.h"


void C_Enemy::Draw()
{

}

void C_Enemy::Update()
{

}

void C_Enemy::Init()
{

	m_enemyTex.Load("Textures/Enemy/enemy.png");
	//敵の初期化
	for (int i = 0; i < EnemyNum; i++)
	{
		s_enemy[i].m_pos = { 0.0f,0.0f };
		s_enemy[i].m_move = { 0.0f,0.0f };
		s_enemy[i].m_angle = 0.0f;
		s_enemy[i].m_aliveFlg = false;
		s_enemy[i].m_nowElement = Element::FIre;
	}

	m_exhaustTex.Load("Textures/Effect/exhaust.png");
	//敵の排気エフェクトの初期化
	for (int i = 0; i < EnemyNum; i++)
	{
		s_exhaust[i].m_pos = { 0.0f,0.0f };
		s_exhaust[i].m_animCnt = 0.0f;
		s_exhaust[i].m_angle = 90.0f;
		s_exhaust[i].m_alive = false;
		
	}
	
}

void C_Enemy::Release()
{

}
