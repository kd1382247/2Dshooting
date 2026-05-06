#include "ShotEnemy.h"

#include"../../../Effect/Exhaust/Exhaust.h"
#include"../../../Effect/Explosion/Explosion.h"
#include"EnemyBullet.h"

void C_ShotEnemy::Draw()
{

	// 敵
	for (int i = 0; i < shotEnemyNum; i++)
	{
		if (s_shotEnemy[i].m_aliveFlg)
		{
			SHADER.m_spriteShader.SetMatrix(s_shotEnemy[i].m_mat);
			SHADER.m_spriteShader.DrawTex(&m_shotEnemyTex, Math::Rectangle( (int)s_shotEnemy[i].m_nowElement*96, 0, 96, 96), 1.0f);
		}
	}

	// 排気エフェクト
	for (int i = 0; i < shotEnemyNum; i++)
	{
		m_exhaust[i]->Draw(s_shotEnemy[i].m_aliveFlg);
	}

	// 爆破エフェクト
	for (int i = 0; i < shotEnemyNum; i++)
	{
		m_explosion[i]->Draw();
	}

}

void C_ShotEnemy::Update()
{
	AliveState();
	Move();
	Action();


	// 排気エフェクト
	for (int i = 0; i < shotEnemyNum; i++)
	{
		m_exhaust[i]->Update(s_shotEnemy[i].m_aliveFlg, s_shotEnemy[i].m_pos, m_exhaustAngle, m_exhaustDistance);
	}

	// 爆破エフェクト
	for (int i = 0; i < shotEnemyNum; i++)
	{
		m_explosion[i]->Update();
	}
}

void C_ShotEnemy::Spawn()
{
	
	for (int i = 0; i < shotEnemyNum; i++)
	{
		if (!s_shotEnemy[i].m_aliveFlg)
		{
			s_shotEnemy[i].m_aliveFlg = true;
			s_shotEnemy[i].m_move = { m_moveSpeedX,0 };
			s_shotEnemy[i].m_angle = 90.0f;
			m_hp[i] = 5;
			int random = rand() % 461 - 200;
			s_shotEnemy[i].m_pos.y = random;
			m_shotFlg[i] = false;
			m_shotWait[i] = 0.0f;
			m_coolTime[i] = 0.0f;
			m_shotCnt[i] = 0;
		}
	}

	//　座標をCSVファイルから読み込む
	FILE* fp;

	if (fopen_s(&fp, "Data/Enemy/RushEnemyPos.csv", "r") == 0)
	{
		char dummy[255];
		for (int i = 0; i < shotEnemyNum; i++)
		{
			if (fgets(dummy, 255, fp) != nullptr)//1行読み込み
			{
				Math::Vector2 pos;
				fscanf_s(fp, ",%f,%f", &pos.x, &pos.y);//頭に , で読み飛ばし
				s_shotEnemy[i].m_pos.x = pos.x;
			}
		}

		fclose(fp);
	}
}

void C_ShotEnemy::Init()
{

	m_shotEnemyTex.Load("Textures/Enemy/shotEnemy.png");

	m_enemyBullet = std::make_shared<C_EnemyBullet>();

	Spawn();

	for (int i = 0; i < shotEnemyNum; i++)
	{
		m_exhaust[i] = std::make_shared<C_Exhaust>();
	}

	m_radius = 30;

	for (int i = 0; i < shotEnemyNum; i++)
	{
		m_explosion[i] = std::make_shared<C_Explosion>();
	}
}

void C_ShotEnemy::Release()
{
	m_shotEnemyTex.Release();
}

void C_ShotEnemy::Move()
{
	
	for (int i = 0; i < shotEnemyNum; i++)
	{
		if (s_shotEnemy[i].m_aliveFlg)
		{
			if (s_shotEnemy[i].m_pos.x < 640)
			{
				m_shotFlg[i] = true;
				m_shotWait[i]--;
				if (m_shotWait[i] < 0)
				{
					m_shotWait[i] = 0;
				}
			
			}
		}
	}

	// 行列作成＋座標更新
	for (int i = 0; i < shotEnemyNum; i++)
	{
		if (s_shotEnemy[i].m_aliveFlg)
		{
			s_shotEnemy[i].m_pos += s_shotEnemy[i].m_move;

			s_shotEnemy[i].m_rotationMat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(s_shotEnemy[i].m_angle));
			s_shotEnemy[i].m_transMat = Math::Matrix::CreateTranslation(s_shotEnemy[i].m_pos.x, s_shotEnemy[i].m_pos.y, 0);
			s_shotEnemy[i].m_mat = s_shotEnemy[i].m_rotationMat * s_shotEnemy[i].m_transMat;
		}
	}

}

void C_ShotEnemy::AliveState()
{
	// 敵が左端まで行ったら
	for (int i = 0; i < shotEnemyNum; i++)
	{
		if (s_shotEnemy[i].m_aliveFlg)
		{
			if (s_shotEnemy[i].m_pos.x < screenLeft - m_radius - m_exhaustDistance)
			{
				s_shotEnemy[i].m_aliveFlg = false;
			}
		}
	}

	// HPが0になったら
	for (int i = 0; i < shotEnemyNum; i++)
	{
		if (s_shotEnemy[i].m_aliveFlg)
		{
			if (m_hp[i] <= 0)
			{
				s_shotEnemy[i].m_aliveFlg = false;
				m_explosion[i]->Spawn(s_shotEnemy[i].m_pos);
			}
		}
	}
}

void C_ShotEnemy::Action()
{
	for (int i = 0; i < shotEnemyNum; i++)
	{
		if (s_shotEnemy[i].m_aliveFlg)
		{
			if (m_shotFlg[i])
			{
				m_coolTime[i]++;
				if(m_coolTime[i]>60*3)
				{
					if (m_shotWait[i] == 0)
					{
						m_enemyBullet->Spawn(s_shotEnemy[i].m_pos, s_shotEnemy[i].m_nowElement);
						m_shotWait[i] = 20;
						m_shotCnt[i]++;
						if (m_shotCnt[i] >= 3)
						{
							m_shotCnt[i] = 0;
							m_coolTime[i] = 0.0f;
						}
					}
				}
			}
		}
	}
}

