#include "GearEnemy.h"

#include "../../../Effect/Explosion/Explosion.h"
#include"../../../UI/Score/Score.h"
#include"../../Player/Player.h"

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
	m_randomElement = rand() % 3;

	//敵の初期化
	for (int i = 0, j = 0; i < gearEnemyNum; i++)
	{
		if (j >= 4)
		{
			j = 0;
			m_randomElement = rand() % 3;
		}
		j++;

		s_gearEnemy[i].m_move = { m_movePowX,0.0f };
		s_gearEnemy[i].m_aliveFlg = true;
		s_gearEnemy[i].m_nowElement = e_elementTable[m_randomElement];
		m_hp[i] = m_maxHp;
	}

	m_aliveFalseCnt = 0;
	m_aliveFalseFlg = false;

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

float C_GearEnemy::GetScore(MatchupType a_matchupType)
{
	if (a_matchupType == WEAK)
	{
		return gearEnemyScore * 2;
	}
	if (a_matchupType == NORMAL)
	{
		return gearEnemyScore;
	}
	if (a_matchupType == RESIST)
	{
		return gearEnemyScore / 2;
	}
}

void C_GearEnemy::Init()
{

	for (int i = 0; i < gearEnemyNum; i++)
	{
		m_explosion[i] = std::make_shared<C_Explosion>();
	}
	m_gearEnemyTex.Load("Textures/Enemy/gearEnemy.png");

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
				m_aliveFalseCnt++;

				m_score->ScoreCntUp(GetScore(e_matchupType[i]));
				m_player->CoolTimeCntUp();
				
			}
		}
	}

	for (int i = 0; i < gearEnemyNum; i++)
	{
		if (s_gearEnemy[i].m_aliveFlg)
		{
			if (s_gearEnemy[i].m_pos.x < screenLeft - m_radius)
			{
				s_gearEnemy[i].m_aliveFlg = false;
				m_aliveFalseCnt++;
			}
		}
	}

	if (m_aliveFalseCnt>=gearEnemyNum  )
	{
		m_aliveFalseFlg = true;
	}

}
