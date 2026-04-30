#include "Enemy.h"


void C_Enemy::Draw()
{

	for (int i = 0; i < enemyNum; i++)
	{
		if(s_enemy[i].m_aliveFlg)
		{
			SHADER.m_spriteShader.SetMatrix(s_enemy[i].m_mat);
			SHADER.m_spriteShader.DrawTex(&m_enemyTex, Math::Rectangle((int)m_animCnt[i] * 96, (int)s_enemy[i].m_nowElement * 96, 96, 96), 1.0f);

		}
	}
}

void C_Enemy::Update()
{
	
	for (int i = 0; i < enemyNum; i++)
	{
		if (s_enemy[i].m_aliveFlg)
		{
			m_animCnt[i]+=0.3;
			if(m_animCnt[i]>9)
			{
				m_animCnt[i] = 0.0f;
			}
		}
	}

	for (int i = 0; i < enemyNum; i++)
	{
		if (s_enemy[i].m_aliveFlg)
		{
			s_enemy[i].m_pos += s_enemy[i].m_move;

			s_enemy[i].m_mat = Math::Matrix::CreateTranslation(s_enemy[i].m_pos.x, s_enemy[i].m_pos.y, 0);
		}
	}

}

void C_Enemy::Init()
{

	m_enemyTex.Load("Textures/Enemy/miniEnemy.png");
	//敵の初期化
	for (int i = 0; i < enemyNum; i++)
	{
		s_enemy[i].m_pos = { 0.0f,0.0f };
		s_enemy[i].m_move = { -1.0f,0.0f };
		s_enemy[i].m_angle = 0.0f;
		s_enemy[i].m_aliveFlg = true;
		m_animCnt[i] = 0.0f;
		s_enemy[i].m_nowElement = Element::Fire;
	}

	FILE* fp;

	if (fopen_s(&fp, "Data/Enemy/miniEnemyPos.csv", "r") == 0)
	{
		char dummy[255];
		for (int i = 0; i < enemyNum; i++)
		{
			if (fgets(dummy, 255, fp) != nullptr)//1行読み込み
			{
				Math::Vector2 pos;
				fscanf_s(fp, ",%f,%f", &pos.x, &pos.y);//頭に , で読み飛ばし
				s_enemy[i].m_pos=pos;
			}
		}

		fclose(fp);
	}

}

void C_Enemy::Release()
{
	m_enemyTex.Release();
}
