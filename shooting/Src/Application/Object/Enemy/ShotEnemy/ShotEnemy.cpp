#include "ShotEnemy.h"

#include"../../../Effect/Exhaust/Exhaust.h"
#include"../../../Effect/Explosion/Explosion.h"

void C_ShotEnemy::Draw()
{

	// 敵
	for (int i = 0; i < shotEnemyNum; i++)
	{
		if (s_shotEnemy[i].m_aliveFlg)
		{
			SHADER.m_spriteShader.SetMatrix(s_shotEnemy[i].m_mat);
			SHADER.m_spriteShader.DrawTex(&m_shotEnemyTex, Math::Rectangle( 0, 0, 96, 96), 1.0f);
		}
	}

	// 弾
	for (int i = 0; i < enemyBulletNum; i++)
	{
		if (s_enemyBullet[i].m_aliveFlg)
		{
			SHADER.m_spriteShader.SetMatrix(s_enemyBullet[i].m_mat);
			SHADER.m_spriteShader.DrawTex(&m_enemyBulletTex, Math::Rectangle(0, 0, 96, 96), 1.0f);
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
	MoveEnemy();
	MoveBullet();

	// 排気エフェクト
	for (int i = 0; i < shotEnemyNum; i++)
	{
		m_exhaust[i]->Update(s_shotEnemy[i].m_aliveFlg, s_shotEnemy[i].m_pos, m_exhaustAngle, 38.0f);
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

void C_ShotEnemy::MoveEnemy()
{
	



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
			if (s_shotEnemy[i].m_pos.x < screenLeft - m_radius - 20)
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

void C_ShotEnemy::Shot(Math::Vector2 a_pos,Element a_nowElement)
{
	for (int i = 0; i < enemyBulletNum; i++)
	{
		if (!s_enemyBullet[i].m_aliveFlg)
		{
			s_enemyBullet[i].m_aliveFlg = true;
			s_enemyBullet[i].m_pos = a_pos;
			s_enemyBullet[i].m_nowElement = a_nowElement;
			s_enemyBullet[i].m_move = { m_bulletMoveSpeed,0 };
		}
	}

}

void C_ShotEnemy::MoveBullet()
{
	for (int i = 0; i < enemyBulletNum; i++)
	{
		if (s_enemyBullet[i].m_aliveFlg)
		{
			s_enemyBullet[i].m_pos += s_enemyBullet[i].m_move;

			s_enemyBullet[i].m_mat = Math::Matrix::CreateTranslation(s_enemyBullet[i].m_pos.x, s_enemyBullet[i].m_pos.y, 0);
		}
	}
	
}



