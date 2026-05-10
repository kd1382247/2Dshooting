#pragma once
#include"../BaseObject.h"


class C_Bullet;
class C_Exhaust;
class C_ChangeEffect;

class C_GameScene;


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

public:

	C_Player() { Init(); }
	~C_Player()override { Release(); }

	void Draw()    override;
	void Update()  override;
	
	
	void SetInstance(std::shared_ptr<C_Bullet>a_bullet) { m_bullet = a_bullet; }
	Element GetNowElement() { return s_player.m_nowElement; }
	Math::Vector2 GetPos() { return s_player.m_pos; }
	void SetAliveFlg(bool a_flg) { s_player.m_aliveFlg = a_flg; }

	float GetRadius() { return m_radius; }
	bool  GetAliveFlg() { return s_player.m_aliveFlg; }

	bool GetHitCoolTimeFlg() { return  m_hitCoolTimeFlg; }
	void SetHitCoolTimeFlg(bool a_flg) { m_hitCoolTimeFlg = a_flg; }


	// HP関連のゲッター
	float GetMaxHp() { return m_maxHp; }
	float GetCurrentHp() { return m_hp; }

	// クールタイムのゲッター
	float GetMaxElChangeCoolTime() { return m_maxElChangeCoolTime; }
	float GetCurrentElChangeCoolTime() { return m_elChangeCoolTime; }




	void SetOwner(C_GameScene* a_owner) { m_owner = a_owner; }


	void Damage(float a_damage)
	{ 
		m_hp -= a_damage;
		if (m_hp <= 0)m_hp = 0;
	}


private:


	float m_hoge = {};

	std::shared_ptr<C_Bullet>m_bullet=nullptr;

	std::shared_ptr<C_Exhaust>m_exhaust=nullptr;
	const float               m_exhaustAngle = 270.0f;

	std::shared_ptr<C_ChangeEffect>m_changeEffect=nullptr;
	
	C_GameScene* m_owner=nullptr;

	//解放処理
	void Init()    override;
	void Release() override;

	// プレイヤーの動き
	void Move();

	void ElementChangeCoolTime();

	void HitCoolTime();



	//弾発射関数
	void Shoot();

	//プレイヤーの関数
	void ElementChange();


	KdTexture     m_playerTex;
	S_Object      s_player;
	
	PlayerMotion  e_playerMotion;
	
	const int m_playerWidht=55;
	const int m_playerHight=35;

	float         m_rightMoveCnt;
	float         m_leftMoveCnt;
	bool          m_rightMoveFlg;
	bool          m_leftMoveFlg;

	const float   m_moveSpeed=5.0f;

	// 体力
	const float   m_maxHp = 100;
	float         m_hp = 100;
	// クールタイム
	const float   m_maxElChangeCoolTime = 300;
	float         m_elChangeCoolTime=300;

	bool          m_keyFlg;

	bool m_hitCoolTimeFlg = {};
	int  m_hitCoolTime = {};

	// ダメージを受けた際の点滅
	float m_alpha;
	float m_flashCnt;

	float         m_frame = 0;
	float         m_time=0;
	float         m_timeCnt=0;
};