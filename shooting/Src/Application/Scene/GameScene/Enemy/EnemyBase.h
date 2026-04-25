#pragma once
#include"../Player/Element.h"

class C_EnemyBase
{
public:

	C_EnemyBase(){}
	virtual~C_EnemyBase(){}

	virtual void Draw() = 0;
	virtual void Update() = 0;
	virtual void Init() = 0;
	virtual void Release() = 0;

protected:

	struct S_Enemy
	{
		Math::Vector2 m_pos;
		Math::Vector2 m_move;
		Math::Matrix  m_rotationMat;
		Math::Matrix  m_transMat;
		Math::Matrix  m_mat;
		bool          m_aliveFlg;
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

	KdTexture m_enemyTex;
	KdTexture m_exhaustTex;

};