#pragma once
#include"EnemyBase.h"

class C_Enemy:public C_EnemyBase
{
public:

	C_Enemy(){}
	~C_Enemy(){}

	void Draw()override;
	void Update()override;
	


private:

	void Init()override;
	void Release()override;

	static const int EnemyNum = 50;

	S_Enemy   s_enemy[EnemyNum];
	S_Exhaust s_exhaust[EnemyNum];
	
	
};