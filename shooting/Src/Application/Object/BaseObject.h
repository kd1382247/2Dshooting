#pragma once


class C_BaseObject
{
public:

	C_BaseObject() {}
	virtual ~C_BaseObject()=0{}

	virtual void Draw()=0;
	virtual void Update()=0;
	virtual void Init()=0;

	
	enum Element
	{
		Fire,
		Grass,
		Water
	};

protected:

	virtual void Release();

	//画面端用の定数
	static const int screenLeft = -640;  //左端
	static const int screenRight = 640;  //右端
	static const int screenTop = 360;    //上端
	static const int screenBottom = -240;//下端

	struct S_Object
	{
		Math::Vector2 m_pos;
		Math::Vector2 m_move;
		Math::Matrix  m_rotationMat;
		Math::Matrix  m_transMat;
		Math::Matrix  m_mat;
		float         m_angle;
		bool          m_aliveFlg;
		Element       m_nowElement;
	};

	float         m_radius = {};
};
