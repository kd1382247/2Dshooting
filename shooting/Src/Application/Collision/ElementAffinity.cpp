#include "ElementAffinity.h"

PopupType C_ElementAffinity::GetPopupType(Element a_bullet, Element a_enemy)
{

	// 同じ属性判定
	if (a_bullet == a_enemy)
	{
		return NORMAL;
	}

	// 有利属性判定
	if (a_bullet == Fire && a_enemy == Grass||  
		a_bullet==Grass&&a_enemy==Water||
		a_bullet==Water&&a_enemy==Fire)
	{
		return WEAK;
	}
	// 不利属性判定
	if (a_bullet == Fire && a_enemy == Water||
		a_bullet==Grass&&a_enemy==Fire||
		a_bullet==Water&&a_enemy==Grass)
	{
		return RESIST;
	}
}

float C_ElementAffinity::CalculateElementDamage(Element a_player, Element a_enemy,  float a_attackPow)
{

	float damage = a_attackPow;
	// 同じ属性判定
	if (a_player == a_enemy)
	{
		return damage;
	}

	// 有利属性判定
	if (a_player == Fire && a_enemy == Grass ||
		a_player == Grass && a_enemy == Water ||
		a_player == Water && a_enemy == Fire)
	{
	 return damage * 2;
	}
	// 不利属性判定
	if (a_player == Fire && a_enemy == Water ||
		a_player == Grass && a_enemy == Fire ||
		a_player == Water && a_enemy == Grass)
	{
		return damage /2;
	}
}

