#pragma once
#include"../Base/BaseObject.h"

class C_Enemy:public C_BaseObject
{
public:

	C_Enemy() { Init(); }
	~C_Enemy()override { Release(); }

	void Draw()override;
	void Update()override;
	

	
private:

	void Init()override;
	void Release()override;

	static const int enemyNum = 18;

	S_Object   s_enemy[enemyNum];
	float      m_animCnt[enemyNum];

	KdTexture  m_enemyTex;
	
};