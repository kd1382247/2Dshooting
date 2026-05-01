#pragma once

class C_Player;
class C_Bullet;
class C_Enemy;
class C_HitEffect;


class C_Collision
{
public:

	C_Collision(){}
	~C_Collision(){}

	void checkBulletEnemy();
	void checkPlayerEnemy();

	void SetInstance(std::shared_ptr<C_Player>a_player,
		             std::shared_ptr<C_Bullet>a_bulle,
		             std::shared_ptr<C_Enemy>a_enemy,
					 std::shared_ptr<C_HitEffect>a_hitEffect)
	{
		m_player = a_player;
		m_bullet = a_bulle;
		m_enemy = a_enemy;
		m_hitEffect = a_hitEffect;
	}
	

private:

	std::shared_ptr<C_Player>m_player=nullptr;
	std::shared_ptr<C_Bullet>m_bullet=nullptr;
	std::shared_ptr<C_Enemy>m_enemy=nullptr;
	std::shared_ptr<C_HitEffect>m_hitEffect=nullptr;

};