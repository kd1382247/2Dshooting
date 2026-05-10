#pragma once


class C_ChangeEffect
{

public:


	C_ChangeEffect() { Init(); }
	~C_ChangeEffect(){ Release();}
	
	
	void Draw();
	void Update(Math::Vector2 a_pos,float a_scale);

	bool GetAliveFlg() { return m_aliveFlg; }

	void SetAliveFlg(bool a_flg) { m_aliveFlg = a_flg; }

private:
	
	
	void Init();
	void Release();


	KdTexture     m_tex;
	Math::Vector2 m_pos;
	Math::Matrix  m_mat;
	Math::Matrix  m_scaleMat;
	Math::Matrix  m_transMat;
	float         m_animCnt;
	bool          m_aliveFlg;

};
