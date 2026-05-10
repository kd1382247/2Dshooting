#pragma once

#include"../Data/Element/Element.h"
#include"../Data/DamageIndicator/DamageIndicator.h"

class C_ElementAffinity
{

public:

	C_ElementAffinity(){}
	~C_ElementAffinity(){}


	PopupType GetPopupType(Element a_bullet,Element a_enemy);
	
	float     CalculateElementDamage(Element a_player, Element a_enemy, float a_attackPow);

private:


};