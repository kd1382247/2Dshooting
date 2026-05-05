#include "GearEnemy.h"

#include "../../../Effect/Explosion/Explosion.h"

void C_GearEnemy::Draw()
{

	for (int i = 0; i < gearEnemyNum; i++)
	{
		if(s_gearEnemy[i].m_aliveFlg)
		{
			SHADER.m_spriteShader.SetMatrix(s_gearEnemy[i].m_mat);
			SHADER.m_spriteShader.DrawTex(&m_gearEnemyTex, Math::Rectangle((int)m_animCnt[i] * 96, (int)s_gearEnemy[i].m_nowElement * 96, 96, 96), 1.0f);
		}
	}

	for (int i = 0; i < gearEnemyNum; i++)
	{
		m_explosion[i]->Draw();
	}
}

void C_GearEnemy::Update()
{
	
	AliveState();

	Animation();
	
	Move();

	for (int i = 0; i < gearEnemyNum; i++)
	{
		m_explosion[i]->Update();
	}
}

void C_GearEnemy::Spawn()
{
	//敵の初期化
	for (int i = 0; i < gearEnemyNum; i++)
	{
		s_gearEnemy[i].m_move = { -1.0f,0.0f };
		s_gearEnemy[i].m_aliveFlg = true;
		s_gearEnemy[i].m_nowElement = Element::Fire;
		m_hp[i] = 5;
	}

	m_radius = 32.0f;

	FILE* fp;

	if (fopen_s(&fp, "Data/Enemy/GearEnemyPos.csv", "r") == 0)
	{
		char dummy[255];
		for (int i = 0; i < gearEnemyNum; i++)
		{
			if (fgets(dummy, 255, fp) != nullptr)//1行読み込み
			{
				Math::Vector2 pos;
				fscanf_s(fp, ",%f,%f", &pos.x, &pos.y);//頭に , で読み飛ばし
				s_gearEnemy[i].m_pos = pos;
			}
		}

		fclose(fp);
	}
}

void C_GearEnemy::Init()
{

	for (int i = 0; i < gearEnemyNum; i++)
	{
		m_explosion[i] = std::make_shared<C_Explosion>();
	}

	m_gearEnemyTex.Load("Textures/Enemy/gearEnemy.png");


	Spawn();

}

void C_GearEnemy::Release()
{
	m_gearEnemyTex.Release();
}

void C_GearEnemy::Move()
{
	for (int i = 0; i < gearEnemyNum; i++)
	{
		if (s_gearEnemy[i].m_aliveFlg)
		{

			s_gearEnemy[i].m_pos += s_gearEnemy[i].m_move;

			s_gearEnemy[i].m_mat = Math::Matrix::CreateTranslation(s_gearEnemy[i].m_pos.x, s_gearEnemy[i].m_pos.y, 0);
		}
	}
}

void C_GearEnemy::Animation()
{
	for(int i=0;i<gearEnemyNum;i++)
	{
		m_animCnt[i] += 0.3;
		if (m_animCnt[i] > 9)
		{
			m_animCnt[i] = 0.0f;
		}
	}
}

void C_GearEnemy::AliveState()
{

	for (int i = 0; i < gearEnemyNum; i++)
	{
		if (s_gearEnemy[i].m_aliveFlg)
		{
			if (m_hp[i] <= 0)
			{
				s_gearEnemy[i].m_aliveFlg = false;
				m_explosion[i]->Spawn(s_gearEnemy[i].m_pos);
			}
		}
	}

}
