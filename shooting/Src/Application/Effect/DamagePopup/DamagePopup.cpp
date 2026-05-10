#include "DamagePopup.h"

void C_DamagePopup::Draw()
{

	if(m_aliveFlg)
	{
		if (e_popupType == WEAK)
		{
			SHADER.m_spriteShader.SetMatrix(m_mat);
			SHADER.m_spriteShader.DrawTex(&m_weakTex, Math::Rectangle(0, 0, 86, 16), 0.8f);
		}

		if (e_popupType == RESIST)
		{
			SHADER.m_spriteShader.SetMatrix(m_mat);
			SHADER.m_spriteShader.DrawTex(&m_resistTex, Math::Rectangle(0, 0, 106, 16), 0.8f);
		}

		if (e_popupType == NORMAL)
		{
			SHADER.m_spriteShader.SetMatrix(m_mat);
			SHADER.m_spriteShader.DrawTex(&m_normalTex, Math::Rectangle(0, 0, 92, 16), 0.8f);
		}
	}
}

void C_DamagePopup::Update()
{

	if(m_aliveFlg)
	{
		m_displayCnt++;
		if (m_displayCnt > 60 * 0.4)
		{
			m_aliveFlg = false;
		}

		m_pos.y += 0.4;

		m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	}
}

void C_DamagePopup::Spawn(Math::Vector2 a_pos,PopupType a_popupType)
{
	e_popupType = a_popupType;
	m_pos.x = a_pos.x;
	m_pos.y = a_pos.y+10;
	m_aliveFlg = true;
	m_displayCnt = 0;
}

void C_DamagePopup::Init()
{
	m_weakTex.Load("Textures/Player/weak.png");
	m_resistTex.Load("Textures/Player/resist.png");
	m_normalTex.Load("Textures/Player/normal.png");

}

void C_DamagePopup::Release()
{
	m_weakTex.Release();
	m_resistTex.Release();
	m_normalTex.Release();

}
