#pragma once
#include "Element.h"
class C_Bullet;


class C_Player
{

public:
	enum PlayerMotion
	{
		RightMove2 = 4,
		RightMove1 = 3,
		Idle = 2,
		LeftMove1 = 1,
		LeftMove2 = 0
	};


	struct S_Player
	{
		Math::Vector2 m_pos;
		Math::Vector2 m_move;
		Math::Matrix  m_transMat;
		Math::Matrix  m_rotationMat;
		Math::Matrix  m_mat;
		float         m_hp;
		bool          m_aliveFlg;
		bool          m_hitFlg;
		float         m_animCnt;
		float         m_angle;
		Element       m_nowElement;
	};

	struct S_Exhaust
	{
		Math::Vector2 m_pos;
		Math::Matrix  m_mat;
		Math::Matrix  m_transMat;
		Math::Matrix  m_rotationMat;
		bool          m_alive;
		float         m_animCnt;
		float         m_angle;
	};

	struct S_ChangeEffect
	{
		Math::Vector2 m_pos;
		Math::Matrix  m_mat;
		float         m_animCnt;
		float         m_alive;
	};

public:

	C_Player() { Init(); }
	~C_Player() { Release(); }

	void Draw();
	void Update();
	
	
	float GetAnimCnt() { return s_exhaust.m_animCnt; }
	int GetNowElement() { return (int)s_player.m_nowElement; }

	// HP関連のゲッター
	float GetMaxHp() { return m_maxHp; }
	float GetCurrentHp() { return m_hp; }

	// クールタイムのゲッター
	float GetMaxCoolTime() { return m_maxCoolTime; }
	float GetCurrentCoolTime() { return m_coolTime; }
private:

	std::shared_ptr<C_Bullet>m_bullet;

	//解放処理
	void Init();
	void Release();

	//弾発射関数
	void Shoot();

	//プレイヤーの関数
	void DrawPlayer();
	void UpdatePlayer();
	void InitPlayer();

	void ElementChange();

	//排気エフェクト
	void DrawExhaust();
	void UpdateExhaust();
	void InitExhaust();

	//属性切り替えエフェクト
	void DrawChangeEffect();
	void UpdateChangeEffect();
	void InitChangeEffect();


	KdTexture     m_playerTex;
	S_Player      s_player;
	

	KdTexture     m_exhaustTex;
	S_Exhaust       s_exhaust;

	KdTexture     m_changeEffectTex;
	S_ChangeEffect  s_changeEffect;

	PlayerMotion  e_playerMotion;
	
	float         m_rightMoveCnt;
	float         m_leftMoveCnt;
	bool          m_rightMoveFlg;
	bool          m_leftMoveFlg;
	const int     m_moveSpeed=5;

	const float   m_maxHp = 100;
	float         m_hp = 100;

	const float   m_maxCoolTime = 600;
	float         m_coolTime=600;

	bool          m_keyFlg;

	float         m_frame = 0;

	float         m_time=0;
	float         m_timeCnt=0;
};