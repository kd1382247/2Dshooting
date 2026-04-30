#pragma once


class C_BaseObject
{
public:

	C_BaseObject() {}
	virtual ~C_BaseObject()=0{}

	virtual void Draw()=0;
	virtual void Update()=0;
	virtual void Init()=0;


protected:

	virtual void Release();

	enum Element
	{
		Fire,
		Grass,
		Water
	};

	struct S_Object
	{
		Math::Vector2 m_pos;
		Math::Vector2 m_move;
		Math::Matrix  m_rotationMat;
		Math::Matrix  m_transMat;
		Math::Matrix  m_mat;
		float         m_angle;
		bool          m_aliveFlg;
		float         m_radius;
		Element       m_nowElement;
	};

	
};
