#include "stdafx.h"
#include "Monster4.h"


CMonster4::CMonster4() : m_bDead(false)
{
	
}


CMonster4::~CMonster4()
{
	Release();
}

void CMonster4::Initialize(void)
{
	m_tInfo.vSIze = { 50.f, 50.f , 0.f };
	m_tInfo.vPos = { 400.f, 300.f, 0.f };
	m_pOriginPos = m_tInfo.vPos;
	m_pPoint[0] = { m_tInfo.vPos.x - m_tInfo.vSIze.x*0.5f, m_tInfo.vPos.y - m_tInfo.vSIze.y*0.5f, 0.f };
	m_pPoint[1] = { m_tInfo.vPos.x + m_tInfo.vSIze.x*0.5f, m_tInfo.vPos.y - m_tInfo.vSIze.y*0.5f, 0.f };
	m_pPoint[2] = { m_tInfo.vPos.x + m_tInfo.vSIze.x*0.5f, m_tInfo.vPos.y + m_tInfo.vSIze.y*0.5f, 0.f };
	m_pPoint[3] = { m_tInfo.vPos.x - m_tInfo.vSIze.x*0.5f, m_tInfo.vPos.y + m_tInfo.vSIze.y*0.5f, 0.f };

	for (int i = 0; i < 4; ++i)
	{
		m_pOriginPoint[i] = m_pPoint[i];
	}
}

int CMonster4::Update(void)
{

	if (m_bDead)
		return OBJ_DEAD;
	D3DXMATRIX matRotZ, matTrans;

	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	m_tInfo.matWorld = matRotZ*matTrans;

	for (int i = 0; i < 4; ++i)
	{
		m_pPoint[i] = m_pOriginPoint[i];
		m_pPoint[i] -= m_pOriginPos;

		D3DXVec3TransformCoord(&m_pPoint[i], &m_pPoint[i], &m_tInfo.matWorld);
	}
}

void CMonster4::Late_Update(void)
{
}

void CMonster4::Render(HDC hDC)
{

	MoveToEx(hDC, m_pPoint[0].x, m_pPoint[0].y, nullptr);

	for (int i = 0; i < 4; ++i)
	{
		LineTo(hDC, m_pPoint[i].x, m_pPoint[i].y);

		if (i < 2)
			Ellipse(hDC, m_pPoint[i].x - 5, m_pPoint[i].y - 5, m_pPoint[i].x + 5, m_pPoint[i].y + 5);
	}
	LineTo(hDC, m_pPoint[0].x, m_pPoint[0].y);

}

void CMonster4::Release(void)
{
}
