#pragma once

class Scene
{
private:



public:

	// ‰Šúİ’è
	void Init();

	// ‰ğ•ú
	void Release();

	// XVˆ—
	void Update();

	// •`‰æˆ—
	void Draw2D();

	// GUIˆ—
	void ImGuiUpdate();

	void SetTime(float a_time) { m_time = a_time; }
	void SetHp(float a_hp) { m_hp = a_hp; }
	void SetDamage(float a_damage) { m_damage = a_damage; }


private:

	Scene() {}

	float m_time;
	float m_hp;
	float m_damage;

public:
	static Scene& GetInstance()
	{
		static Scene instance;
		return instance;
	}
};

#define SCENE Scene::GetInstance()
