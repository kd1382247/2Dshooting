#include "Boss.h"

#include"../Player/Player.h"
#include"../../Effect/Explosion/Explosion.h"
#include"../../Effect/ChangeEffect/ChangeEffect.h"
#include"../../UI/Result/Result.h"
#include"../../UI/Score/Score.h"


void C_Boss::Draw()
{
	DrawBossExplosion();

	if (!s_boss.m_aliveFlg)return;

	DrawBoss();
	
	DrawShield();
	m_changeEffect->Draw();


	DrawSpikeEnemy();
	DrawSEnemyWarning();
	
	DrawGearEnemy();
	DrawGEnemyWarning();

	

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

	UpdateBossExplosion();

	if (!s_boss.m_aliveFlg)return;


	AliveStateBoss();
	MoveBoss();

	UpdateShield();
	m_changeEffect->Update(s_boss.m_pos, 1.5);
	Action();


	AliveStateSpikeEnemy();
	UpdateSEnemyWarning();
	MoveSpikeEnemy();

	
	AliveStateGearEnemy();
	UpdateGEnemyWarning();
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
}

void C_Boss::Init()
{

	m_changeEffect = std::make_shared<C_ChangeEffect>();


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
	InitBossExplosion();
	InitShield();
	InitSpikeEnemy();
	InitGearEnemy();

	m_warningTex.Load("Textures/Boss/warning.png");

}

void C_Boss::Release()
{
	m_bossTex.Release();
	m_bossExplosionTex.Release();
	m_shieldTex.Release();
	m_spikeEnemyTex.Release();
	m_gearEnemyTex.Release();
	m_warningTex.Release();

}

void C_Boss::DrawBoss()
{
	if(s_boss.m_aliveFlg)
	{
		SHADER.m_spriteShader.SetMatrix(s_boss.m_mat);
		SHADER.m_spriteShader.DrawTex(&m_bossTex, Math::Rectangle((int)m_bossAnimCnt * 192, (int)s_boss.m_nowElement * 192, 192, 192), 1.0f);
	}
}

void C_Boss::MoveBoss()
{
	if (m_bossMoveFlg)
	{
		
			m_bossMoveCnt++;
		
		if (m_bossMoveCnt < 60 * 8.5)
		{
			if (s_boss.m_pos.y > screenTop - m_bossRadius || s_boss.m_pos.y < screenBottom + m_bossRadius)
			{
				s_boss.m_move.y *= -1;
			}
			if (s_boss.m_pos.x<200 + m_bossRadius || s_boss.m_pos.x>screenRight - m_bossRadius-15)
			{
				s_boss.m_move.x *= -1;
			}
		}
		if (m_bossMoveCnt > 60 * 8.8)
		{
			// シールドを展開
			s_shield.m_aliveFlg = true;

			if (s_boss.m_pos != m_bossInitPos)
			{
				Math::Vector2 pos = m_bossInitPos - s_boss.m_pos;

				pos.Normalize();

				s_boss.m_move = pos;

				
				if (m_bossMoveCnt > 60 * 10)
				{
					s_boss.m_pos = m_bossInitPos;
				}

				if (s_boss.m_pos == m_bossInitPos)
				{
					ElementChange();

					SpawnGEWarning();
					SpawnSEWarning();

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

void C_Boss::SpawnBoss()
{
	// ボス
	s_boss.m_pos = m_bossInitPos;
	m_bossHp = m_bossMaxHp;
	s_boss.m_aliveFlg = true;

	int random = rand() % 3;
	if (random == 0)s_boss.m_nowElement = Fire;
	if (random == 1)s_boss.m_nowElement = Grass;
	if (random == 2)s_boss.m_nowElement = Water;
	// シールド
	s_shield.m_aliveFlg = true;
	s_shield.m_animCnt = { 0,0 };
	s_shield.m_pos = { 0,0 };
	s_shield.m_shieldReleaseFlg = false;


	SpawnGEWarning();
	SpawnSEWarning();
}

void C_Boss::InitBoss()
{
	m_bossTex.Load("Textures/Boss/Eyeball.png");
}

void C_Boss::Action()
{
	if (!m_rotationAttackFlg && !m_homingAttackFlg)
	{
		if (m_initGESpawnFlg && m_initSESpawnFlg)
		{
			m_bossActionCnt++;
		}
		if (m_bossActionCnt > 60 * 5)
		{

			//int random = rand() % 2;


			if (m_bossAttackPattern == 0)
			{
				m_homingAttackFlg = true;
				m_bossAttackPattern = 1;
			}
			if (m_bossAttackPattern == 1&&!m_homingAttackFlg)
			{
				m_rotationAttackFlg = true;
				m_bossAttackPattern = 0;
			}
			m_bossActionCnt = 0;
		}
	}

}

void C_Boss::AliveStateBoss()
{
	if (m_bossHp <= 0&&s_boss.m_aliveFlg)
	{
		s_boss.m_aliveFlg = false;

		// ゲームクリアフラグをtrueにする
		m_result->SetClearFlg(true);
		
 		m_score->ScoreCntUp(GetScore(e_bossMatchupType));

		m_bossExpPos = s_boss.m_pos;
		m_bossExpAliveFlg = true;
	}

}

float C_Boss::GetScore(MatchupType a_matchupType)
{
	if (a_matchupType == WEAK)
	{
		return bossScore * 2;
	}
	if (a_matchupType == NORMAL)
	{
		return bossScore;
	}
	if (a_matchupType == RESIST)
	{
		return bossScore / 2;
	}
}


void C_Boss::SetBossMove()
{
	int random = rand() % 3;

	s_boss.m_move = { 4,2 };
	m_bossMoveCnt = 0;
	m_bossMoveFlg = true;
}

void C_Boss::ElementChange()
{
	int random = rand() % 2;
	Element nowElement = s_boss.m_nowElement;

		if (nowElement==Fire)
		{
			if (random == 0)s_boss.m_nowElement = Grass;
			if (random == 1)s_boss.m_nowElement = Water;
		}
		if (nowElement == Grass)
		{
			if (random == 0)s_boss.m_nowElement = Fire;
			if (random == 1)s_boss.m_nowElement = Water;
		}
		if (nowElement == Water)
		{
			if (random == 0)s_boss.m_nowElement = Fire;
			if (random == 1)s_boss.m_nowElement = Grass;
		}

		m_changeEffect->SetAliveFlg(true);
}

void C_Boss::DrawBossExplosion()
{
	if (m_bossExpAliveFlg)
	{
		SHADER.m_spriteShader.SetMatrix(m_bossExpMat);
		SHADER.m_spriteShader.DrawTex(&m_bossExplosionTex, Math::Rectangle((int)m_bossExpAnimCnt*144, 0, 144, 144), m_bossExpAlpha);
	}
}

void C_Boss::UpdateBossExplosion()
{
	if (m_bossExpAliveFlg)
	{
		m_bossExpAlpha = 1.0f;
		m_bossExpAnimCnt+=0.1;
		if (m_bossExpAnimCnt > 8)
		{
			m_bossAnimCnt = 0;
			m_bossExpAliveFlg = false;
		}

		m_bossExpMat = Math::Matrix::CreateTranslation(m_bossExpPos.x, m_bossExpPos. y, 0);
	}
}

void C_Boss::InitBossExplosion()
{
	m_bossExplosionTex.Load("Textures/Boss/explosion.png");
}

void C_Boss::DrawShield()
{
	if (!s_shield.m_aliveFlg)return;

	SHADER.m_spriteShader.SetMatrix(s_shield.m_mat);
	SHADER.m_spriteShader.DrawTex(&m_shieldTex, Math::Rectangle((int)s_shield.m_animCnt.x*130, (int)s_shield.m_animCnt.y*130, 130, 130), 0.6f);
}

void C_Boss::UpdateShield()
{
	if (!s_shield.m_aliveFlg)return;


	s_shield.m_animCnt.x += 0.2;

	if(!s_shield.m_shieldReleaseFlg)
	{
		if (s_shield.m_animCnt.x > 10)
		{
			s_shield.m_animCnt.y = 1;
		}
		if (s_shield.m_animCnt.x > 20)
		{
			s_shield.m_animCnt.x = 10;
		}
	}
	if (s_shield.m_shieldReleaseFlg)
	{
		if (s_shield.m_animCnt.x > 3)
		{
			s_shield.m_animCnt = { 0,0 };
			s_shield.m_aliveFlg = false;
			s_shield.m_shieldReleaseFlg = false;
		}

	}

	s_shield.m_pos.x = s_boss.m_pos.x;
	s_shield.m_pos.y = s_boss.m_pos.y + 10;



	s_shield.m_mat = Math::Matrix::CreateTranslation(s_shield.m_pos.x, s_shield.m_pos.y, 0);
}

void C_Boss::InitShield()
{
	m_shieldTex.Load("Textures/Boss/shield.png");
}


void C_Boss::DrawSpikeEnemy()
{
	for (int i = 0; i < spikeEnemyNum; i++)
	{
		if (s_spikeEnemy[i].m_aliveFlg)
		{
			SHADER.m_spriteShader.SetMatrix(s_spikeEnemy[i].m_mat);
			SHADER.m_spriteShader.DrawTex(&m_spikeEnemyTex, Math::Rectangle((int)m_sEnemyAnimCnt[i] * 96, (int)s_spikeEnemy[i].m_nowElement * 96, 96, 96), 1.0f);
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

						if (m_homingAttackFlg)
						{
							m_homingFlg[i] = true;
						}
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
						if(m_homingFlg[i])
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
	}

	// 行列作成+座標更新
	for (int i = 0; i < spikeEnemyNum; i++)
	{
		if (s_spikeEnemy[i].m_aliveFlg)
		{
		
			if (!m_sEnemyMoveFlg[i])
			{
				s_spikeEnemy[i].m_pos = m_bossInitPos + s_spikeEnemy[i].m_move;
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
	m_spikeEnemyTex.Load("Textures/Enemy/spikeEnemy.png");
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
				m_player->CoolTimeCntUp();
			}
		}
	}
	// トゲ型の敵が全ての生存フラグがfalseだったら
	if (m_sEnemyFalseCnt >= spikeEnemyNum && !m_bossMoveFlg)
	{
		m_sEnemySpawnCnt++;
		if (m_sEnemySpawnCnt > 60 * 3)
		{
			SpawnSEWarning();
			m_sEnemySpawnCnt = 0;
		}
	}

	// もしボスが動き出したら
	if (m_bossMoveFlg)
	{
		for (int i = 0; i < spikeEnemyNum; i++)
		{
			if (s_spikeEnemy[i].m_aliveFlg)
			{
				s_spikeEnemy[i].m_aliveFlg = false;
				m_sEnemyExplosion[i]->Spawn(s_spikeEnemy[i].m_pos);
			}
		}
		m_sEnemySpawnCnt=0;
		m_sEnemyFalseCnt = 0;
	}

}

void C_Boss::SpawnSpikeEnemy()
{
	m_sERandomElement = rand() % 3;

	for (int i = 0,j=0; i < spikeEnemyNum; i++)
	{
		// 回転角度
		m_sEnemyDeg[i] = m_sEnemyDegTable[i];

		s_spikeEnemy[i].m_aliveFlg = true;
		s_spikeEnemy[i].m_pos = Math::Vector2::Zero;
		s_spikeEnemy[i].m_move = Math::Vector2::Zero;
		m_sEnemyMoveFlg[i] = false;
		m_homingCnt[i] = 0;
		m_homingFlg[i] = false;
		m_sEnemyHp[i] = m_sEnemyMaxHp;

		if (m_bossHp > 800)
		{
			s_spikeEnemy[i].m_nowElement = s_boss.m_nowElement;
		}
		else
		{
			if (j >= 3)
			{
				j = 0;
				m_sERandomElement = rand() % 3;
			}
			s_spikeEnemy[i].m_nowElement = e_elementTable[m_sERandomElement];
			j++;
		}


		m_sEnemyAttackMove[i] = { m_AttackMoveSpeedX,0 };

	}

	m_homingAttackFlg = false;
	m_rotationAttackFlg = false;
	m_sEnemyFalseCnt = 0;
	m_initSESpawnFlg = true;
}

void C_Boss::DrawSEnemyWarning()
{
	if (!m_sEWarningFlg)return;
	for (int i = 0; i < spikeEnemyNum; i++)
	{
		if (s_sEWarning[i].m_aliveFlg)
		{
			SHADER.m_spriteShader.SetMatrix(s_sEWarning[i].m_mat);
			SHADER.m_spriteShader.DrawTex(&m_warningTex, Math::Rectangle(0, 0, 65, 65), m_sEAlpha);
		}
	}
}

void C_Boss::UpdateSEnemyWarning()
{
	if (!m_sEWarningFlg)return;


	if (m_sEFlashCnt == 60 * 0.2)
	{
		m_sEAlpha = 0.4f;
	}
	else if (m_sEFlashCnt == 60 * 0.4)
	{
		m_sEAlpha = 1.0f;
		m_sEFlashCnt = 0;
	}

	m_sEFlashCnt++;


	if (m_sEWarningCnt > 60 * 2)
	{
		AliveStateSEWarning();
		m_sEWarningCnt = 0;
	}

	m_sEWarningCnt++;


	for (int i = 0; i < spikeEnemyNum; i++)
	{
		if (s_sEWarning[i].m_aliveFlg)
		{
			s_sEWarning[i].m_move.x = cosf(DirectX::XMConvertToRadians(m_sEWarningDeg[i])) * 200;
			s_sEWarning[i].m_move.y = sinf(DirectX::XMConvertToRadians(m_sEWarningDeg[i])) * 200;
		}
	}

	for (int i = 0; i < spikeEnemyNum; i++)
	{
		if (s_sEWarning[i].m_aliveFlg)
		{
			s_sEWarning[i].m_pos = m_bossInitPos + s_sEWarning[i].m_move;

			s_sEWarning[i].m_mat = Math::Matrix::CreateTranslation(s_sEWarning[i].m_pos.x, s_sEWarning[i].m_pos.y, 0);
		}
	}

}
void C_Boss::AliveStateSEWarning()
{
	for (int i = 0; i < spikeEnemyNum; i++)
	{
		if (s_sEWarning[i].m_aliveFlg)
		{
			s_sEWarning[i].m_aliveFlg = false;
		}
	}

	m_sEWarningFlg = false;

	SpawnSpikeEnemy();
}

void C_Boss::SpawnSEWarning()
{
	for (int i = 0; i < spikeEnemyNum; i++)
	{
		// 回転角度
		m_sEWarningDeg[i] = m_sEnemyDegTable[i];

		s_sEWarning[i].m_aliveFlg = true;
		s_sEWarning[i].m_pos = Math::Vector2::Zero;
		s_sEWarning[i].m_move = Math::Vector2::Zero;

	}

	m_sEAlpha = 1.0f;
	m_sEFlashCnt = 0;
	m_sEWarningFlg = true;
	m_sEWarningCnt = 0;
}

void C_Boss::DrawGearEnemy()
{
	for (int i = 0; i < gearEnemyNum; i++)
	{
		if (s_gearEnemy[i].m_aliveFlg)
		{
			SHADER.m_spriteShader.SetMatrix(s_gearEnemy[i].m_mat);
			SHADER.m_spriteShader.DrawTex(&m_gearEnemyTex, Math::Rectangle((int)m_gEnemyAnimCnt[i] * 96, (int)s_gearEnemy[i].m_nowElement*96, 96, 96), 1.0f);
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

			s_gearEnemy[i].m_pos = m_bossInitPos + s_gearEnemy[i].m_move;

			s_gearEnemy[i].m_mat = Math::Matrix::CreateTranslation(s_gearEnemy[i].m_pos.x, s_gearEnemy[i].m_pos.y, 0);
		}
	}
}

void C_Boss::InitGearEnemy()
{
	m_gearEnemyTex.Load("Textures/Enemy/gearEnemy.png");
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
				m_player->CoolTimeCntUp();
			}
		}
	}
	// 歯車型の敵が全ての生存フラグがfalseだったら
	if (m_gEnemyFalseCnt >= gearEnemyNum)
	{
		SetBossMove();
		m_gEnemyFalseCnt = 0;

		m_sEWarningFlg = false;
		for (int i = 0; i < spikeEnemyNum; i++)
		{
			if (s_sEWarning[i].m_aliveFlg)
			{
				s_sEWarning[i].m_aliveFlg = false;
			}
		}
		// シールド解除
		s_shield.m_shieldReleaseFlg = true;
		s_shield.m_animCnt = { 0,2 };
	}
}

void C_Boss::SpawnGearEnemy()
{
	m_gERandomElement = rand() % 3;

	for (int i = 0,j=0; i < gearEnemyNum; i++)
	{
		// 回転角度
		m_gEnemyDeg[i] = m_gEnemyDegTable[i];

		s_gearEnemy[i].m_aliveFlg = true;
		s_gearEnemy[i].m_pos = Math::Vector2::Zero;
		s_gearEnemy[i].m_move = Math::Vector2::Zero;

		if(m_bossHp>800)
		{
			s_gearEnemy[i].m_nowElement = s_boss.m_nowElement;
		}
		else
		{
			if (j >= 2)
			{
				j = 0;
				m_gERandomElement = rand() % 3;
			}
			s_gearEnemy[i].m_nowElement = e_elementTable[m_gERandomElement];
			j++;
		}

		m_gEnemyHp[i] = m_gEnemyMaxHp;

	}
	m_gEnemyFalseCnt = 0;

	m_initGESpawnFlg = true;
}

void C_Boss::DrawGEnemyWarning()
{
	for (int i = 0; i < gearEnemyNum; i++)
	{
		if (s_gEWarning[i].m_aliveFlg)
		{
			SHADER.m_spriteShader.SetMatrix(s_gEWarning[i].m_mat);
			SHADER.m_spriteShader.DrawTex(&m_warningTex, Math::Rectangle(0, 0, 65, 65), m_gEAlpha);
		}
	}
}

void C_Boss::UpdateGEnemyWarning()
{

	if (!m_gEWarningFlg)return;

	if (m_gEWarningCnt > 60 * 2)
	{
		AliveStateGEWarning();
		m_gEWarningCnt = 0;
	}

	m_gEWarningCnt++;


	if (m_gEFlashCnt == 60 * 0.2)
	{
		m_gEAlpha = 0.4f;
	}
	else if (m_gEFlashCnt == 60 * 0.4)
	{
		m_gEAlpha = 1.0f;
		m_gEFlashCnt = 0;
	}

	m_gEFlashCnt++;


	for (int i = 0; i < gearEnemyNum; i++)
	{
		if (s_gEWarning[i].m_aliveFlg)
		{
			s_gEWarning[i].m_move.x = cosf(DirectX::XMConvertToRadians(m_gEWarningDeg[i])) * 100;
			s_gEWarning[i].m_move.y = sinf(DirectX::XMConvertToRadians(m_gEWarningDeg[i])) * 100;
		}
	}

	for (int i = 0; i < gearEnemyNum; i++)
	{
		if (s_gEWarning[i].m_aliveFlg)
		{

			s_gEWarning[i].m_pos = m_bossInitPos + s_gEWarning[i].m_move;

			s_gEWarning[i].m_mat = Math::Matrix::CreateTranslation(s_gEWarning[i].m_pos.x, s_gEWarning[i].m_pos.y, 0);
		}
	}

}


void C_Boss::AliveStateGEWarning()
{
	for (int i = 0; i < gearEnemyNum; i++)
	{
		if (s_gEWarning[i].m_aliveFlg)
		{
			s_gEWarning[i].m_aliveFlg = false;
		}
	}

	m_gEWarningFlg = false;
	
	SpawnGearEnemy();
}

void C_Boss::SpawnGEWarning()
{
	for (int i = 0; i < gearEnemyNum; i++)
	{
		// 回転角度
		m_gEWarningDeg[i] = m_gEnemyDegTable[i];
		s_gEWarning[i].m_aliveFlg = true;
		s_gEWarning[i].m_pos = Math::Vector2::Zero;
		s_gEWarning[i].m_move = Math::Vector2::Zero;
	}

	m_gEAlpha = 1.0f;
	m_gEFlashCnt = 0;
	m_gEWarningFlg = true;
	m_gEWarningCnt = 0;
}
