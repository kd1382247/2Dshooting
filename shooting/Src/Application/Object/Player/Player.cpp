#include "Player.h"

#include"../Bullet/Bullet.h"
#include"../../Effect/Exhaust/Exhaust.h"
#include"../../Effect/ChangeEffect/ChangeEffect.h"
#include"../../Scene.h"


void C_Player::Draw()
{
	if (s_player.m_aliveFlg)
	{
		SHADER.m_spriteShader.SetMatrix(s_player.m_mat);
		SHADER.m_spriteShader.DrawTex(&m_playerTex, Math::Rectangle((int)e_playerMotion * 96, (int)s_player.m_nowElement * 96, 96, 96), 1.0f);
	}
	
	m_exhaust->Draw(s_player.m_aliveFlg);
	m_changeEffect->Draw();
}

void C_Player::Update()
{
	if (s_player.m_aliveFlg)
	{
		Move();

		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			Shoot();
		}

		CoolTime();

		m_timeCnt++;
		if (m_timeCnt > 60 * 1)
		{
			m_time++;
			m_timeCnt = 0.0f;
			SCENE.SetTime(m_time);
		}

		ElementChange();

		m_changeEffect->Update(s_player.m_pos);

		m_exhaust->Update(s_player.m_aliveFlg,s_player.m_pos, m_exhaustAngle,-38);

		
		m_frame++;

	}
}

void C_Player::Init()
{

	m_exhaust = std::make_shared<C_Exhaust>();
	m_changeEffect = std::make_shared<C_ChangeEffect>();


	m_playerTex.Load("Textures/Player/player.png");

	s_player.m_aliveFlg = true;
	s_player.m_angle = 270.0f;
	s_player.m_pos = { 0.0f,0.0f };
	s_player.m_move = { 0.0f,0.0f };

	e_playerMotion = Idle;

	m_rightMoveCnt = 0.0f;
	m_leftMoveCnt = 0.0f;
	m_rightMoveFlg = false;
	m_leftMoveFlg = false;

	s_player.m_nowElement = Element::Fire;
	m_keyFlg = false;

	m_radius = 25.0f;
}

void C_Player::Release()
{
	m_playerTex.Release();
	
}

void C_Player::Move()
{
	s_player.m_move = { 0.0f,0.0f };

	//プレイヤーの移動
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		if (!m_rightMoveFlg)
		{
			s_player.m_move.y = m_moveSpeed;
			m_leftMoveFlg = true;
			m_leftMoveCnt++;
			if (m_leftMoveCnt < 60 * 0.3f)e_playerMotion = MinLeftMove;
			if (m_leftMoveCnt > 60 * 0.3f)e_playerMotion = MaxLeftMove;
		}
	}
	else
	{
		m_leftMoveCnt = 0.0f;
		m_leftMoveFlg = false;
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		if (!m_leftMoveFlg)
		{
			s_player.m_move.y = m_moveSpeed * -1;
			m_rightMoveFlg = true;
			m_rightMoveCnt++;
			if (m_rightMoveCnt < 60 * 0.3f)e_playerMotion = MinRightMove;
			if (m_rightMoveCnt > 60 * 0.3f)e_playerMotion = MaxRightMove;
		}
	}
	else
	{
		m_rightMoveCnt = 0.0f;
		m_rightMoveFlg = false;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		s_player.m_move.x = m_moveSpeed;
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		s_player.m_move.x = m_moveSpeed * -1;
	}
	//左右に動いていなければ待機モーション
	if (!m_leftMoveFlg && !m_rightMoveCnt)e_playerMotion = Idle;


	// 上下左右の壁判定
	// 右
	if (s_player.m_pos.x > screenRight - m_playerWidht)s_player.m_pos.x = screenRight - m_playerWidht;
	// 左
	if (s_player.m_pos.x < screenLeft+ m_playerWidht)s_player.m_pos.x = screenLeft+ m_playerWidht;
	// 上
	if (s_player.m_pos.y > screenTop-m_playerHight)s_player.m_pos.y = screenTop- m_playerHight;
	// 下
	if (s_player.m_pos.y < screenBottom+ m_playerHight)s_player.m_pos.y = screenBottom+ m_playerHight;


	s_player.m_pos += s_player.m_move;


	s_player.m_transMat = Math::Matrix::CreateTranslation(s_player.m_pos.x, s_player.m_pos.y, 0);
	s_player.m_rotationMat = Math::Matrix::CreateRotationZ(ToRadians(s_player.m_angle));
	s_player.m_mat = s_player.m_rotationMat * s_player.m_transMat;

}

void C_Player::CoolTime()
{

	if (m_frame > 60 * 0.01)
	{
		m_frame = 0.0f;
		if (m_coolTime < m_maxCoolTime)
		{
			m_coolTime++;
		}
	}
}

void C_Player::Shoot()
{
	m_bullet->Spawn(s_player.m_pos,s_player.m_nowElement);
}


void C_Player::ElementChange()
{

	if(m_coolTime==m_maxCoolTime)
	{
		if (GetAsyncKeyState('Q') & 0x8000)
		{
			if (!m_keyFlg)
			{
				if (!m_changeEffect->GetAliveFlg() && s_player.m_nowElement != Element::Fire)
				{
					m_changeEffect->SetAliveFlg(true);
					s_player.m_nowElement = Element::Fire;
					m_keyFlg = true;
					m_coolTime = 0.0f;
				}
			}

		}
		else if (GetAsyncKeyState('W') & 0x8000)
		{

			if (!m_keyFlg)
			{
				if (!m_changeEffect->GetAliveFlg() && s_player.m_nowElement != Grass)
				{
					m_changeEffect->SetAliveFlg(true);
					s_player.m_nowElement = Element::Grass;
					m_keyFlg = true;
					m_coolTime = 0.0f;
				}
			}
		}
		else if (GetAsyncKeyState('E') & 0x8000)
		{
			if (!m_keyFlg)
			{
				if (!m_changeEffect->GetAliveFlg() && s_player.m_nowElement != Water)
				{
					m_changeEffect->SetAliveFlg(true);
					s_player.m_nowElement = Element::Water;
					m_keyFlg = true;
					m_coolTime = 0.0f;
				}
			}
		}
		else m_keyFlg = false;
	}
}
