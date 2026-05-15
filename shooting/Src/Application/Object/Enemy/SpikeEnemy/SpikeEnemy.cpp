#include "SpikeEnemy.h"

#include"../../../Effect/Explosion/Explosion.h"
#include"../../../UI/Score/Score.h"
#include"../../Player/Player.h"

void C_SpikeEnemy::Draw()
{

	if (!m_spawnFlg)return;

	for (int i = 0; i < spikeEnemyNum; i++)
	{
		if (s_spikeEnemy[i].m_aliveFlg)
		{
			SHADER.m_spriteShader.SetMatrix(s_spikeEnemy[i].m_mat);
			SHADER.m_spriteShader.DrawTex(&m_spikeEnemyTex, Math::Rectangle((int)m_animCnt[i]*96, s_spikeEnemy[i].m_nowElement*96, 96, 96), 1.0f);
		}
	}

	for (int i = 0; i < spikeEnemyNum; i++)
	{
		m_explosion[i]->Draw();
	}
}

void C_SpikeEnemy::Update()
{
	if (!m_spawnFlg)return;

	AliveState();
	Move();
	Animation();
	for (int i = 0; i < spikeEnemyNum; i++)
	{
		m_explosion[i]->Update();
	}
}

void C_SpikeEnemy::Spawn()
{

	m_randomElement = rand() % 3;

	// 回転する敵
	for (int i = 0, j = 0; i < spikeEnemyNum; i++)
	{

		// 回転角度
		m_deg[i] = m_degTable[j];
		// 行動タイプ
		m_enemyMoveType[i] = m_moveTypeTable[j];

		if (j >= 5)
		{
			j = 0;
			m_randomElement = rand() % 3;
		}
		j++;

		s_spikeEnemy[i].m_aliveFlg = true;
		s_spikeEnemy[i].m_pos = Math::Vector2::Zero;
		s_spikeEnemy[i].m_move = Math::Vector2::Zero;

		;
		s_spikeEnemy[i].m_nowElement = e_elementTable[m_randomElement];

		m_hp[i] = m_maxHp;
	}

	m_aliveFalseCnt = 0;
	m_aliveFalseFlg = false;
	m_spawnFlg = true;

	for (int i = 0; i < centerNum; i++)
	{
		s_center[i].m_move = { m_movePowX,0 };
		s_center[i].m_aliveFlg = true;
	}
	// 座標読込
	FILE* fp;

	if (fopen_s(&fp, "Data/Enemy/SpikeEnemyPos.csv", "r") == 0)
	{
		char dummy[255];
		for (int i = 0; i < centerNum; i++)
		{
			if (fgets(dummy, 255, fp) != nullptr)//1行読み込み
			{
				Math::Vector2 pos;
				fscanf_s(fp, ",%f,%f", &pos.x, &pos.y);//頭に , で読み飛ばし
				s_center[i].m_pos = pos;
			}
		}

		fclose(fp);
	}

	m_radius = 32.0f;

}

float C_SpikeEnemy::GetScore(MatchupType a_matchupType)
{
	if (a_matchupType == WEAK)
	{
		return spikeEnemyScore * 2;
	}
	if (a_matchupType == NORMAL)
	{
		return spikeEnemyScore;
	}
	if (a_matchupType == RESIST)
	{
		return spikeEnemyScore / 2;
	}
}

void C_SpikeEnemy::Init()
{
	for (int i = 0; i < spikeEnemyNum; i++)
	{
		m_explosion[i] = std::make_shared<C_Explosion>();
	}
	m_spikeEnemyTex.Load("Textures/Enemy/spikeEnemy.png");
}

void C_SpikeEnemy::Release()
{
	m_spikeEnemyTex.Release();
}

void C_SpikeEnemy::Move()
{

	// 回転
	for (int i = 0; i < spikeEnemyNum; i++)
	{
		if (s_spikeEnemy[i].m_aliveFlg)
		{
			s_spikeEnemy[i].m_move.x = cosf(DirectX::XMConvertToRadians(m_deg[i])) * 100;
			s_spikeEnemy[i].m_move.y = sinf(DirectX::XMConvertToRadians(m_deg[i])) * 100;

			m_deg[i] += 1;
			if (m_deg[i] > 360)
			{
				m_deg[i] = 0;
			}
		}
	}

	// 移動
	for (int i = 0, j = 0; i < spikeEnemyNum; i++)
	{
		if (s_spikeEnemy[i].m_aliveFlg)
		{
			if (m_enemyMoveType[i] == Rotation)
			{
				// 回転する敵は、特定の座標を中心に回転する
				s_spikeEnemy[i].m_pos = s_center[j].m_pos + s_spikeEnemy[i].m_move;
			}
			else if (m_enemyMoveType[i] = Idle)
			{
				// 回転しない敵は、特定の座標と同じ位置で移動
				s_spikeEnemy[i].m_pos = s_center[j].m_pos;
			}

			s_spikeEnemy[i].m_mat = Math::Matrix::CreateTranslation(s_spikeEnemy[i].m_pos.x, s_spikeEnemy[i].m_pos.y, 0);
		}
		// 5体ごとに中心座標を切り替える
		m_number++;
		if (m_number >= 5)
		{
			m_number = 0;
			j++;
			if (j >= 5)
			{
				j = 0;
			}
		}
	}

	// 敵の中心の座標
	for (int i = 0; i < centerNum; i++)
	{
		if (s_center[i].m_aliveFlg)
		{
			s_center[i].m_pos += s_center[i].m_move;

			s_center[i].m_mat = Math::Matrix::CreateTranslation(s_center[i].m_pos.x, s_center[i].m_pos.y, 0);
		}
	}
}

void C_SpikeEnemy::Animation()
{
	for (int i = 0; i < spikeEnemyNum; i++)
	{
		if (s_spikeEnemy[i].m_aliveFlg)
		{
			m_animCnt[i] += 0.2;
			if (m_animCnt[i] > 4)
			{
				m_animCnt[i] = 0;
			}
		}
	}
}

void C_SpikeEnemy::AliveState()
{

	// 画面端に行った場合
	for (int i = 0; i < spikeEnemyNum; i++)
	{
		if (s_spikeEnemy[i].m_aliveFlg)
		{
			if (s_spikeEnemy[i].m_pos.x < screenLeft - m_radius)
			{
				s_spikeEnemy[i].m_aliveFlg = false;
				m_aliveFalseCnt++;
			}
		}
	}

	// 体力が0になった場合
	for (int i = 0; i < spikeEnemyNum; i++)
	{
		if (s_spikeEnemy[i].m_aliveFlg)
		{
			if (m_hp[i] <= 0)
			{
				s_spikeEnemy[i].m_aliveFlg = false;
				m_explosion[i]->Spawn(s_spikeEnemy[i].m_pos);
				m_aliveFalseCnt++;

				m_score->ScoreCntUp(GetScore(e_matchupType[i]));
				m_score->KillsCntUp(e_matchupType[i]);
				m_player->CoolTimeCntUp();
			}
		}
	}

	if( m_aliveFalseCnt >= spikeEnemyNum)
	{
		m_aliveFalseFlg = true;

		for (int i = 0; i < centerNum; i++)
		{
			if (s_center[i].m_aliveFlg)
			{
				s_center[i].m_aliveFlg = false;
			}
		}
	}

}
