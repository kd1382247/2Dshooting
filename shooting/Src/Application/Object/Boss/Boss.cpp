#include "Boss.h"

#include"../Player/Player.h"
#include"../../Effect/Explosion/Explosion.h"

void C_Boss::Draw()
{
	DrawBoss();
	DrawSpikeEnemy();
	DrawGearEnemy();

	// 歯車型の敵用の爆破エフェクト
	for (int i = 0; i < gearEnemyNum; i++)
	{
		m_gEnemyExplosion[i]->Draw();
	}

	// トゲ型用の爆破エフェクト
	for (int i = 0; i < spikeEnemyNum; i++)
	{
		m_sEnemyExplosion[i]->Draw();
	}
}

void C_Boss::Update()
{

	AliveStateSpikeEnemy();
	MoveSpikeEnemy();


	AliveStateGearEnemy();
	MoveGearEnemy();

	// 歯車型の敵用の爆破エフェクト
	for (int i = 0; i < gearEnemyNum; i++)
	{
		m_gEnemyExplosion[i]->Update();
	}

	// トゲ型用の爆破エフェクト
	for (int i = 0; i < spikeEnemyNum; i++)
	{
		m_sEnemyExplosion[i]->Update();
	}


	MoveBoss();
	Action();

}

void C_Boss::Init()
{

	m_player = std::shared_ptr<C_Player>();

	
	for (int i = 0; i < gearEnemyNum; i++)
	{
		m_gEnemyExplosion[i] = std::make_shared<C_Explosion>();
	}

	// トゲ型用の爆破エフェクト
	for (int i = 0; i < spikeEnemyNum; i++)
	{
		m_sEnemyExplosion[i]=std::make_shared<C_Explosion>();
	}

	InitBoss();
	InitSpikeEnemy();
	InitGearEnemy();

}

void C_Boss::Release()
{
	m_bossTex.Release();
}

void C_Boss::DrawBoss()
{
	SHADER.m_spriteShader.SetMatrix(s_boss.m_mat);
	SHADER.m_spriteShader.DrawTex(&m_bossTex, Math::Rectangle((int)m_bossAnimCnt * 192, 0, 192, 192), 1.0f);
}


void C_Boss::MoveBoss()
{
	m_bossAnimCnt += 0.1;
	if (m_bossAnimCnt > 6)
	{
		m_bossAnimCnt = 0;
	}


	if (m_bossMoveFlg)
	{

		m_bossMoveCnt++;
		if(m_bossMoveCnt<60*8)
		{
			if (s_boss.m_pos.y > screenTop - m_bossRadius || s_boss.m_pos.y < screenBottom + m_bossRadius)
			{
				s_boss.m_move.y *= -1;
			}
			if (s_boss.m_pos.x<200 + m_bossRadius || s_boss.m_pos.x>screenRight - m_bossRadius)
			{
				s_boss.m_move.x *= -1;
			}
		}
		if (m_bossMoveCnt > 60 * 8)
		{

			if(s_boss.m_pos!=m_bossInitPos)
			{
				Math::Vector2 pos = m_bossInitPos - s_boss.m_pos;

				pos.Normalize();

				s_boss.m_move = pos;

				if (m_bossMoveCnt > 60 * 11)
				{
					s_boss.m_pos = m_bossInitPos;
				}

				if (s_boss.m_pos == m_bossInitPos)
				{
					SpawnGearEnemy();
					SpawnSpikeEnemy();
					m_bossMoveFlg = false;
					m_bossMoveCnt = 0;
					s_boss.m_move = { 0,0 };
				}
			}
			
		}
	}


	s_boss.m_pos += s_boss.m_move;

	s_boss.m_mat = Math::Matrix::CreateTranslation(s_boss.m_pos.x, s_boss.m_pos.y, 0);
}



void C_Boss::InitBoss()
{
	m_bossTex.Load("Textures/Boss/Eyeball.png");
	s_boss.m_pos = m_bossInitPos;
	m_bossHp = 40;
	s_boss.m_aliveFlg = true;
}

void C_Boss::Action()
{
	if (!m_ElementChangeFlg && !m_rotationAttackFlg && !m_homingAttackFlg)
	{
		m_bossActionCnt++;
		if (m_bossActionCnt > 60 * 5)
		{

			int ramdom = rand() % 2;


			if (ramdom == 0)
			{
				m_homingAttackFlg = true;
			}
			if (ramdom == 1)
			{
				m_rotationAttackFlg = true;
			}
			m_bossActionCnt = 0;
		}
	}

}

void C_Boss::SetBossMove()
{
	int random = rand() % 3;

	s_boss.m_move = { 4,2 };
	m_bossMoveCnt = 0;
	m_bossMoveFlg = true;

	m_gEnemyFalseCnt = 0;
}


void C_Boss::DrawSpikeEnemy()
{
	for (int i = 0; i < spikeEnemyNum; i++)
	{
		if (s_spikeEnemy[i].m_aliveFlg)
		{
			SHADER.m_spriteShader.SetMatrix(s_spikeEnemy[i].m_mat);
			SHADER.m_spriteShader.DrawTex(&m_spikeEnemyTex, Math::Rectangle((int)m_sEnemyAnimCnt[i] * 96, 0, 96, 96), 1.0f);
		}
	}
}


void C_Boss::MoveSpikeEnemy()
{
	// アニメーション
	for (int i = 0; i < spikeEnemyNum; i++)
	{
		if (s_spikeEnemy[i].m_aliveFlg)
		{
			m_sEnemyAnimCnt[i] -= 0.3;
			if (m_sEnemyAnimCnt[i] <=0)
			{
				m_sEnemyAnimCnt[i] = 4;
			}
		}
	}

	if(!m_rotationAttackFlg&&!m_homingAttackFlg)
	{
		// 回転
		for (int i = 0; i < spikeEnemyNum; i++)
		{
			if (s_spikeEnemy[i].m_aliveFlg)
			{
				s_spikeEnemy[i].m_move.x = cosf(DirectX::XMConvertToRadians(m_sEnemyDeg[i])) * 200;
				s_spikeEnemy[i].m_move.y = sinf(DirectX::XMConvertToRadians(m_sEnemyDeg[i])) * 200;

				m_sEnemyDeg[i] += 0.5;
				if (m_sEnemyDeg[i] > 360)
				{
					m_sEnemyDeg[i] = 0;
				}
			}
		}
	}
	else
	{

		m_sEnemyMoveWait--;
		if (m_sEnemyMoveWait <= 0)
		{
			m_sEnemyMoveWait = 0;
		}

		if(m_sEnemyMoveWait==0)
		{
			for (int i = 0; i < spikeEnemyNum; i++)
			{
				if (s_spikeEnemy[i].m_aliveFlg)
				{
					if (!m_sEnemyMoveFlg[i])
					{
						m_sEnemyMoveFlg[i] = true;
						m_sEnemyMoveWait = 20;
						break;
					}
				}
			}
		}
		// 回転攻撃
		if(m_rotationAttackFlg)
		{
			for (int i = 0; i < spikeEnemyNum; i++)
			{
				if (s_spikeEnemy[i].m_aliveFlg && m_sEnemyMoveFlg[i])
				{
					s_spikeEnemy[i].m_move.x = cosf(DirectX::XMConvertToRadians(m_sEnemyDeg[i])) * 50;
					s_spikeEnemy[i].m_move.y = sinf(DirectX::XMConvertToRadians(m_sEnemyDeg[i])) * 50;

					m_sEnemyDeg[i] += 8;
					if (m_sEnemyDeg[i] > 360)
					{
						m_sEnemyDeg[i] = 0;
					}
				}
			}
		}

		// ホーミング攻撃
		if(m_homingAttackFlg)
		{
			for (int i = 0; i < spikeEnemyNum; i++)
			{
				if (s_spikeEnemy[i].m_aliveFlg)
				{
					if (m_sEnemyMoveFlg[i] && m_homingCnt[i] < 60 * 1.5)
					{
						Math::Vector2 pos = m_player->GetPos() - s_spikeEnemy[i].m_pos;

						pos.Normalize();
						s_spikeEnemy[i].m_move = pos * 5;
						m_homingCnt[i]++;
					}
				}
			}
		}

	}


	// 行列作成+座標更新
	for (int i = 0; i < spikeEnemyNum; i++)
	{
		if (s_spikeEnemy[i].m_aliveFlg)
		{
		
			if (!m_sEnemyMoveFlg[i])
			{
				s_spikeEnemy[i].m_pos = s_boss.m_pos + s_spikeEnemy[i].m_move;
				m_sEnemyAttackPos[i] = s_spikeEnemy[i].m_pos;
			}
			// moveFlgがtrueかつ回転攻撃だったら
			if (m_sEnemyMoveFlg[i]&&m_rotationAttackFlg)
			{
				s_spikeEnemy[i].m_pos = m_sEnemyAttackPos[i] + s_spikeEnemy[i].m_move;
				m_sEnemyAttackPos[i] += m_sEnemyAttackMove[i];
			}
			// moveFlgがtrueかつ回転攻撃だったら
			if (m_sEnemyMoveFlg[i] && m_homingAttackFlg)
			{
				s_spikeEnemy[i].m_pos += s_spikeEnemy[i].m_move;
			}

			s_spikeEnemy[i].m_mat = Math::Matrix::CreateTranslation(s_spikeEnemy[i].m_pos.x, s_spikeEnemy[i].m_pos.y, 0);
			
			m_sEnemyAttackMat[i] = Math::Matrix::CreateTranslation(m_sEnemyAttackPos[i].x, m_sEnemyAttackPos[i].y, 0);
		}
	}

}

void C_Boss::InitSpikeEnemy()
{
	m_spikeEnemyTex.Load("Textures/Boss/spikeEnemy.png");
	for (int i = 0; i < spikeEnemyNum; i++)
	{
		if (!s_spikeEnemy[i].m_aliveFlg)
		{
			// 回転角度
			m_sEnemyDeg[i] = m_sEnemyDegTable[i];

			s_spikeEnemy[i].m_aliveFlg = true;
			s_spikeEnemy[i].m_pos = Math::Vector2::Zero;
			s_spikeEnemy[i].m_move = Math::Vector2::Zero;
			m_sEnemyHp[i] = m_sEnemyMaxHp;

			m_sEnemyAttackMove[i] = { m_AttackMoveSpeedX,0 };
		}
	}
	m_sEnemyFalseCnt = 0;

	m_homingAttackFlg = false;
	m_rotationAttackFlg = false;
}

void C_Boss::AliveStateSpikeEnemy()
{
	for (int i = 0; i < spikeEnemyNum; i++)
	{
		if (s_spikeEnemy[i].m_aliveFlg)
		{
			if (s_spikeEnemy[i].m_pos.x < screenLeft - 60 || s_spikeEnemy[i].m_pos.x>screenRight + 60 || s_spikeEnemy[i].m_pos.y > screenTop + 60 || s_spikeEnemy[i].m_pos.y < screenBottom - 60)
			{
				s_spikeEnemy[i].m_aliveFlg = false;
				m_sEnemyFalseCnt++;
			}
		}
	}

	// HPが0になったら
	for (int i = 0; i < spikeEnemyNum; i++)
	{
		if (s_spikeEnemy[i].m_aliveFlg)
		{
			if (m_sEnemyHp[i] <= 0)
			{
				s_spikeEnemy[i].m_aliveFlg = false;
				m_sEnemyFalseCnt++;

				m_sEnemyExplosion[i]->Spawn(s_spikeEnemy[i].m_pos);
			}
		}
	}


	if (m_sEnemyFalseCnt >= spikeEnemyNum && !m_bossMoveFlg)
	{
		m_sEnemySpawnCnt++;
		if (m_sEnemySpawnCnt > 60 * 5)
		{
			SpawnSpikeEnemy();
			m_sEnemySpawnCnt = 0;
		}

	}

}

void C_Boss::SpawnSpikeEnemy()
{

	for (int i = 0; i < spikeEnemyNum; i++)
	{
		if (!s_spikeEnemy[i].m_aliveFlg)
		{
			// 回転角度
			m_sEnemyDeg[i] = m_sEnemyDegTable[i];

			s_spikeEnemy[i].m_aliveFlg = true;
			s_spikeEnemy[i].m_pos = Math::Vector2::Zero;
			s_spikeEnemy[i].m_move = Math::Vector2::Zero;
			m_sEnemyMoveFlg[i] = false;
			m_homingCnt[i] = 0;
			m_sEnemyHp[i] = m_sEnemyMaxHp;


			m_sEnemyAttackMove[i] = { -2,0 };
		}
	}

	m_homingAttackFlg = false;
	m_rotationAttackFlg = false;
	m_sEnemyFalseCnt = 0;


}


void C_Boss::DrawGearEnemy()
{
	for (int i = 0; i < gearEnemyNum; i++)
	{
		if (s_gearEnemy[i].m_aliveFlg)
		{
			SHADER.m_spriteShader.SetMatrix(s_gearEnemy[i].m_mat);
			SHADER.m_spriteShader.DrawTex(&m_gearEnemyTex, Math::Rectangle((int)m_gEnemyAnimCnt[i] * 96, 0, 96, 96), 1.0f);
		}
	}
}

void C_Boss::MoveGearEnemy()
{
	// アニメーション
	for (int i = 0; i < gearEnemyNum; i++)
	{
		if (s_gearEnemy[i].m_aliveFlg)
		{
			m_gEnemyAnimCnt[i] += 0.3;
			if (m_gEnemyAnimCnt[i] > 9)
			{
				m_gEnemyAnimCnt[i] = 0;
			}
		}
	}


	// 回転
	for (int i = 0; i < gearEnemyNum; i++)
	{
		if (s_gearEnemy[i].m_aliveFlg)
		{
			s_gearEnemy[i].m_move.x = cosf(DirectX::XMConvertToRadians(m_gEnemyDeg[i])) * 100;
			s_gearEnemy[i].m_move.y = sinf(DirectX::XMConvertToRadians(m_gEnemyDeg[i])) * 100;

			m_gEnemyDeg[i] -= 1;
			if (m_gEnemyDeg[i] <= -360)
			{
				m_gEnemyDeg[i] = 0;
			}
		}
	}

	

	for (int i = 0; i < gearEnemyNum; i++)
	{
		if (s_gearEnemy[i].m_aliveFlg)
		{

			s_gearEnemy[i].m_pos = s_boss.m_pos + s_gearEnemy[i].m_move;

			s_gearEnemy[i].m_mat = Math::Matrix::CreateTranslation(s_gearEnemy[i].m_pos.x, s_gearEnemy[i].m_pos.y, 0);
		}
	}
}



void C_Boss::InitGearEnemy()
{
	m_gearEnemyTex.Load("Textures/Boss/gearEnemy.png");
	for (int i = 0; i < gearEnemyNum; i++)
	{
		if (!s_gearEnemy[i].m_aliveFlg)
		{
			// 回転角度
			m_gEnemyDeg[i] = m_gEnemyDegTable[i];

			s_gearEnemy[i].m_aliveFlg = true;
			s_gearEnemy[i].m_pos = Math::Vector2::Zero;
			s_gearEnemy[i].m_move = Math::Vector2::Zero;
			m_homingCnt[i] = 0;
			m_gEnemyHp[i] = m_gEnemyMaxHp;
		}
	}

	m_gEnemyFalseCnt = 0;


}

void C_Boss::AliveStateGearEnemy()
{

	// HPが0になったら
	for (int i = 0; i < gearEnemyNum; i++)
	{
		if (s_gearEnemy[i].m_aliveFlg)
		{
			if (m_gEnemyHp[i] <= 0)
			{
				s_gearEnemy[i].m_aliveFlg = false;
				m_gEnemyFalseCnt++;

				m_gEnemyExplosion[i]->Spawn(s_gearEnemy[i].m_pos);
			}
		}
	}

	if (m_gEnemyFalseCnt >= gearEnemyNum)
	{
		SetBossMove();
	}
}

void C_Boss::SpawnGearEnemy()
{

	for (int i = 0; i < gearEnemyNum; i++)
	{
		if (!s_gearEnemy[i].m_aliveFlg)
		{
			// 回転角度
			m_gEnemyDeg[i] = m_gEnemyDegTable[i];

			s_gearEnemy[i].m_aliveFlg = true;
			s_gearEnemy[i].m_pos = Math::Vector2::Zero;
			s_gearEnemy[i].m_move = Math::Vector2::Zero;
			m_homingCnt[i] = 0;
			m_gEnemyHp[i] = m_gEnemyMaxHp;
		}
	}
	m_gEnemyFalseCnt = 0;
}
