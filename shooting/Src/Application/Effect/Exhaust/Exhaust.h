#pragma once


class C_Exhaust
{
public:

	C_Exhaust() { Init(); }
	~C_Exhaust() { Release(); }

	void Draw(bool a_flg);
	void Update(bool a_flg,Math::Vector2 a_pos,float a_angle,float a_distance);

private:

	void Init();
	void Release();

	

	Math::Vector2 m_pos;
	Math::Matrix  m_transMat;
	Math::Matrix  m_rotationMat;
	Math::Matrix  m_mat;
	float         m_animCnt;
	KdTexture     m_tex;

};