#pragma once
#include"../Base/BaseObject.h"


class C_Bullet;


class C_Player:public C_BaseObject
{

public:
	enum PlayerMotion
	{
		MinLeftMove = 1,
		MaxLeftMove = 0,
		Idle = 2,
		MinRightMove = 3,
		MaxRightMove = 4,
	};


	struct S_Exhaust
	{
		Math::Vector2 m_pos;
		Math::Matrix  m_mat;
		Math::Matrix  m_transMat;
		Math::Matrix  m_rotationMat;
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
	~C_Player()override { Release(); }

	void Draw()    override;
	void Update()  override;
	
	
	void SetInstance(std::shared_ptr<C_Bullet>a_bullet) { m_bullet = a_bullet; }

	float GetAnimCnt() { return s_exhaust.m_animCnt; }
	int GetNowElement() { return (int)s_player.m_nowElement; }

	Math::Vector2 GetPos() { return s_player.m_pos; }


	// HP関連のゲッター
	float GetMaxHp() { return m_maxHp; }
	float GetCurrentHp() { return m_hp; }

	// クールタイムのゲッター
	float GetMaxCoolTime() { return m_maxCoolTime; }
	float GetCurrentCoolTime() { return m_coolTime; }
private:

	std::shared_ptr<C_Bullet>m_bullet;
	

	//解放処理
	void Init()    override;
	void Release() override;

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
	S_Object      s_player;
	
	KdTexture     m_exhaustTex;
	S_Exhaust     s_exhaust;

	KdTexture       m_changeEffectTex;
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