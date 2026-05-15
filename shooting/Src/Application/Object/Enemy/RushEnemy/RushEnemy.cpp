#include "RushEnemy.h"

#include"../../../Effect/Exhaust/Exhaust.h"
#include"../../../Effect/Explosion/Explosion.h"
#include"../../../UI/Score/Score.h"
#include"../../Player/Player.h"

void C_RushEnemy::Draw()
{
	// スポーンしていなかったら
	if (!m_spawnFlg)return;

	for (int i = 0; i < rushEnemyNum; i++)
	{
		if (s_rushEnemy[i].m_aliveFlg)
		{
			SHADER.m_spriteShader.SetMatrix(s_rushEnemy[i].m_mat);
			SHADER.m_spriteShader.DrawTex(&m_rushEnemyTex, Math::Rectangle((int)e_enemyMotion[i]*96, s_rushEnemy[i].m_nowElement*96, 96, 96), 1.0f);
		}
	}
	// 排気エフェクト
	for (int i = 0; i < rushEnemyNum; i++)
	{
		m_exhaust[i]->Draw(s_rushEnemy[i].m_aliveFlg,1.0f);
	}

	// 爆破エフェクト
	for (int i = 0; i < rushEnemyNum; i++)
	{
		m_explosion[i]->Draw();
	}
}

void C_RushEnemy::Update()
{
	// スポーンしていなかったら
	if (!m_spawnFlg)return;

	AliveState();
	Move();
	MovePattern();

	// 排気エフェクト
	for (int i = 0; i < rushEnemyNum; i++)
	{
		m_exhaust[i]->Update(s_rushEnemy[i].m_aliveFlg, s_rushEnemy[i].m_pos, m_exhaustAngle,38.0f);
	}

	// 爆破エフェクト
	for (int i = 0; i < rushEnemyNum; i++)
	{
		m_explosion[i]->Update();
	}

}

void C_RushEnemy::Spawn()
{
	m_randomElement = rand() % 3;

	for (int i = 0,j=0; i < rushEnemyNum; i++)
	{
			if (i % 2 == 0)
			{
				e_rlMove[i] = Right;
			}
			else
			{
				e_rlMove[i] = Left;
			}
			s_rushEnemy[i].m_aliveFlg = true;
			s_rushEnemy[i].m_angle = 90.0f;
			e_enemyMotion[i] = Idle;
			m_hp[i] = m_maxHp;

			if (j >= 2)
			{
				j = 0;
				m_randomElement = rand() % 3;
			}
			j++;
			s_rushEnemy[i].m_nowElement = e_elementTable[m_randomElement];
	}

	m_aliveFalseCnt = 0;
	m_aliveFalseFlg = false;
	m_spawnFlg = true;

	//　座標をCSVファイルから読み込む
	FILE* fp;

	if (fopen_s(&fp, "Data/Enemy/RushEnemyPos.csv", "r") == 0)
	{
		char dummy[255];
		for (int i = 0; i < rushEnemyNum; i++)
		{
			if (fgets(dummy, 255, fp) != nullptr)//1行読み込み
			{
				Math::Vector2 pos;
				fscanf_s(fp, ",%f,%f", &pos.x,&pos.y);//頭に , で読み飛ばし
				s_rushEnemy[i].m_pos = pos;
			}
		}

		fclose(fp);
	}
}

float C_RushEnemy::GetScore(MatchupType a_matchupType)
{
	if (a_matchupType == WEAK)
	{
		return rushEnemyScore * 2;
	}
	if (a_matchupType == NORMAL)
	{
		return rushEnemyScore;
	}
	if (a_matchupType == RESIST)
	{
		return rushEnemyScore / 2;
	}
}

void C_RushEnemy::Init()
{
	m_rushEnemyTex.Load("Textures/Enemy/rushEnemy.png");

	for(int i=0;i<rushEnemyNum;i++)
	{
		m_exhaust[i] = std::make_shared<C_Exhaust>();
	}

	m_radius = 35;

	for(int i=0;i<rushEnemyNum;i++)
	{
		m_explosion[i] = std::make_shared<C_Explosion>();
	}

}

void C_RushEnemy::Release()
{
	m_rushEnemyTex.Release();
}

void C_RushEnemy::Move()
{

	for (int i = 0; i < rushEnemyNum; i++)
	{
		if (s_rushEnemy[i].m_aliveFlg)
		{

			s_rushEnemy[i].m_move.y = 0;

			// 左に動くとき
			if (s_move[i].m_leftMoveFlg)
			{

				s_rushEnemy[i].m_move.y = m_moveSpeedY * -1;

				s_move[i].m_leftMoveCnt++;
				if (s_move[i].m_leftMoveCnt < 60 * 0.3f)e_enemyMotion[i] = MinLeftMove;
				if (s_move[i].m_leftMoveCnt > 60 * 0.3f)e_enemyMotion[i] = MaxLeftMove;
			}
			else
			{
				s_move[i].m_leftMoveCnt = 0.0f;
			}

			// 右に動くとき
			if (s_move[i].m_rightMoveFlg)
			{
				s_rushEnemy[i].m_move.y = m_moveSpeedY;

				s_move[i].m_rightMoveCnt++;
				if (s_move[i].m_rightMoveCnt < 60 * 0.3f)e_enemyMotion[i] = MinRightMove;
				if (s_move[i].m_rightMoveCnt > 60 * 0.3f)e_enemyMotion[i] = MaxRightMove;
			}
			else
			{
				s_move[i].m_rightMoveCnt = 0.0f;
			}

			s_rushEnemy[i].m_move.x = m_moveSpeedX * -1;

			//左右に動いていなければ待機モーション
			if (!s_move[i].m_leftMoveFlg && !s_move[i].m_rightMoveCnt)e_enemyMotion[i] = Idle;

		}
	}

	// 壁判定
	for (int i = 0; i < rushEnemyNum; i++)
	{
		if (s_rushEnemy[i].m_aliveFlg)
		{
			// 上判定
			if (s_rushEnemy[i].m_pos.y > screenTop - m_radius)
			{
				s_rushEnemy[i].m_pos.y = screenTop - m_radius;
			}

			// 下判定
			if (s_rushEnemy[i].m_pos.y < screenBottom+ m_radius)
			{
				s_rushEnemy[i].m_pos.y = screenBottom + m_radius;
			}
		}
	}

	// 行列作成＋座標更新
	for (int i = 0; i < rushEnemyNum; i++)
	{
		if (s_rushEnemy[i].m_aliveFlg)
		{
			s_rushEnemy[i].m_pos += s_rushEnemy[i].m_move;

			s_rushEnemy[i].m_rotationMat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(s_rushEnemy[i].m_angle));
			s_rushEnemy[i].m_transMat = Math::Matrix::CreateTranslation(s_rushEnemy[i].m_pos.x, s_rushEnemy[i].m_pos.y, 0);
			s_rushEnemy[i].m_mat = s_rushEnemy[i].m_rotationMat * s_rushEnemy[i].m_transMat;
		}
	}
}

void C_RushEnemy::AliveState()
{

	// 敵が左端まで行ったら
	for (int i = 0; i < rushEnemyNum; i++)
	{
		if (s_rushEnemy[i].m_aliveFlg)
		{
			if (s_rushEnemy[i].m_pos.x < screenLeft - m_radius-20)
			{
				s_rushEnemy[i].m_aliveFlg = false;
				m_aliveFalseCnt++;
			}
		}
	}

	// HPが0になったら
	for (int i = 0; i < rushEnemyNum; i++)
	{
		if (s_rushEnemy[i].m_aliveFlg)
		{
			if (m_hp[i] <= 0)
			{
				s_rushEnemy[i].m_aliveFlg = false;
				m_explosion[i]->Spawn(s_rushEnemy[i].m_pos);
				m_aliveFalseCnt++;

				m_score->ScoreCntUp(GetScore(e_matchupType[i]));
				m_score->KillsCntUp(e_matchupType[i]);
				m_player->CoolTimeCntUp();
			}
		}
	}

	if (m_aliveFalseCnt >=rushEnemyNum)
	{
		m_aliveFalseFlg = true;
	}

}

void C_RushEnemy::MovePattern()
{

	for(int i=0;i<rushEnemyNum;i++)
	{
		m_moveCnt[i]++;

		
		if(e_rlMove[i]==Right)
		{
			// 左へ動く
			if (m_moveCnt[i] < 60 * 1.5f)
			{
				s_move[i].m_leftMoveFlg = true;
			}
			else
			{
				s_move[i].m_leftMoveFlg = false;
			}
			// 右へ動く
			if (m_moveCnt[i] > 60 * 1.5f)
			{
				s_move[i].m_rightMoveFlg = true;
			}
			else
			{
				s_move[i].m_rightMoveFlg = false;
			}
		}
		if (e_rlMove[i]==Left)
		{
			// 右へ動く
			if (m_moveCnt[i] < 60 * 1.5f)
			{
				s_move[i].m_rightMoveFlg = true;
			}
			else
			{
				s_move[i].m_rightMoveFlg = false;
			}
			// 左へ動く
			if (m_moveCnt[i] > 60 * 1.5f)
			{
				s_move[i].m_leftMoveFlg = true;
			}
			else
			{
				s_move[i].m_leftMoveFlg = false;
			}
		}
		if (m_moveCnt[i] > 60 * 3)
		{
			m_moveCnt[i] = 0;
		}

	}
}

