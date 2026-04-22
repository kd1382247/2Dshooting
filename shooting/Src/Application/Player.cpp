#include "Player.h"

C_Player::C_Player()
{
	Init();
}

C_Player::~C_Player()
{
	Release();
}

void C_Player::Draw()
{
	if (s_player.m_alive)
	{
		SHADER.m_spriteShader.SetMatrix(s_player.m_mat);
		SHADER.m_spriteShader.DrawTex(&m_playerTex, Math::Rectangle(e_playerMotion * 96, e_nowElement*96, 96, 96), 1.0f);
	}

	SHADER.m_spriteShader.SetMatrix(s_exhaust.m_mat);
	SHADER.m_spriteShader.DrawTex(&m_exhaustTex, Math::Rectangle((int)s_exhaust.m_animCnt*96, 0, 96, 96), 1.0f);

	if(s_changeEffect.m_alive)
	{
		SHADER.m_spriteShader.SetMatrix(s_changeEffect.m_mat);
		SHADER.m_spriteShader.DrawTex(&m_changeEffectTex, Math::Rectangle((int)s_changeEffect.m_animCnt * 384, 0, 384, 384), 1.0f);
	}
}

void C_Player::Update()
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
			if (m_leftMoveCnt < 60 * 0.3f)e_playerMotion = LeftMove1;
			if (m_leftMoveCnt > 60 * 0.3f)e_playerMotion = LeftMove2;
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
			if (m_rightMoveCnt < 60 * 0.3f)e_playerMotion = RightMove1;
			if (m_rightMoveCnt > 60 * 0.3f)e_playerMotion = RightMove2;
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



	if (GetAsyncKeyState('1') & 0x8000)
	{
		if (!m_keyFlg)
		{
			e_nowElement = Fire;
			m_keyFlg = true;
			if(!s_changeEffect.m_alive)
			{
				s_changeEffect.m_alive = true;
			}
		}

	}
	else if (GetAsyncKeyState('2') & 0x8000)
	{

		if (!m_keyFlg)
		{
			e_nowElement = Grass;
			m_keyFlg = true;

			if (!s_changeEffect.m_alive)
			{
				s_changeEffect.m_alive = true;
			}
		}
	}
	else if (GetAsyncKeyState('3') & 0x8000)
	{
		if (!m_keyFlg)
		{
			e_nowElement = Water;
			m_keyFlg = true;

			if (!s_changeEffect.m_alive)
			{
				s_changeEffect.m_alive = true;
			}
		}
	}
	else m_keyFlg = false;

	s_player.m_pos += s_player.m_move;

	s_exhaust.m_pos.x = s_player.m_pos.x - 38.0f;
	s_exhaust.m_pos.y = s_player.m_pos.y ;

	s_player.m_transMat = Math::Matrix::CreateTranslation(s_player.m_pos.x, s_player.m_pos.y, 0);
	s_player.m_scaleMat = Math::Matrix::CreateScale(s_player.m_scale.x, s_player.m_scale.y, 0);
	s_player.m_rotationMat = Math::Matrix::CreateRotationZ(ToRadians(s_player.m_angle));
	s_player.m_mat = s_player.m_scaleMat *s_player.m_rotationMat* s_player.m_transMat;



	 
	s_exhaust.m_transMat= Math::Matrix::CreateTranslation(s_exhaust.m_pos.x, s_exhaust.m_pos.y, 0);
	s_exhaust.m_rotationMat = Math::Matrix::CreateRotationZ(ToRadians(s_exhaust.m_angle));

	s_exhaust.m_mat = s_exhaust.m_rotationMat * s_exhaust.m_transMat;

	s_exhaust.m_animCnt += 0.3f;
	if (s_exhaust.m_animCnt > 5.0f)
	{
		s_exhaust.m_animCnt = 0.0f;
	}


	if (s_changeEffect.m_alive)
	{
		s_changeEffect.m_animCnt+=0.2;
		if (s_changeEffect.m_animCnt > 7.0f)
		{
			s_changeEffect.m_alive = false;
			s_changeEffect.m_animCnt = 0.0f;
		}
	}
	s_changeEffect.m_pos = s_player.m_pos;

	s_changeEffect.m_mat = Math::Matrix::CreateTranslation(s_changeEffect.m_pos.x, s_changeEffect.m_pos.y, 0);

}

void C_Player::Init()
{
	m_playerTex.Load("player.png");

	s_player.m_alive = true;
	s_player.m_hitFlg = false;
	s_player.m_scale = { 1.0f,1.0f };
	s_player.m_angle = 270.0f;
	s_player.m_pos = { 0.0f,0.0f };
	s_player.m_move = { 0.0f,0.0f };
	s_player.m_hp = 0.0f;
	s_player.m_animCnt = 0.0f;

	m_exhaustTex.Load("exhaust.png");
	s_exhaust.m_alive = true;
	s_exhaust.m_animCnt = 0.0f;
	s_exhaust.m_pos = { 0.0f,0.0f };
	s_exhaust.m_angle = 270.0f;

	e_playerMotion = Idle;

	m_rightMoveCnt = 0.0f;
	m_leftMoveCnt = 0.0f;
	m_rightMoveFlg = false;
	m_leftMoveFlg = false;

	m_changeEffectTex.Load("Texture/changeEffect2.png");
	s_changeEffect.m_pos = { 0.0f,0.0f };
	s_changeEffect.m_alive = false;
	s_changeEffect.m_animCnt = 0.0f;


	m_keyFlg = false;
	e_nowElement = Fire;
}

void C_Player::Release()
{
	m_playerTex.Release();
	m_exhaustTex.Release();
	m_changeEffectTex.Release();
}
