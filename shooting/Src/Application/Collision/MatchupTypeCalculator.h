#pragma once

#include"../Data/Element/Element.h"
#include"../Data/MatchupType/MatchupType.h"

class C_ElementAffinity
{

public:

	C_ElementAffinity(){}
	~C_ElementAffinity(){}


	MatchupType GetMatchupType(Element a_bullet,Element a_enemy);
	
	float  CalculateElementDamageToEnemy(Element a_player, Element a_enemy, float a_attackPow);
	float  CalculateElementDamageToPlayer(Element a_player, Element a_enemy, float a_attackPow);

private:


};