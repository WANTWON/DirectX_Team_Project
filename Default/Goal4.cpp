#include "stdafx.h"
#include "Goal4.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"


CGoal4::CGoal4() : m_bCount(false)
{
}


CGoal4::~CGoal4()
{
}

void CGoal4::Initialize(void)
{
	m_tInfo.vSIze = { 40.f, 40.f, 0.f };
	m_tInfo.vPos = { 400.f, 500.f, 0.f };

	D3DXMatrixIdentity(&m_tInfo.matWorld);
}

int CGoal4::Update(void)
{
	if (!m_bCount)
	{
		m_pPoint[0] = { m_tInfo.vPos.x - m_tInfo.vSIze.x*0.5f, m_tInfo.vPos.y - m_tInfo.vSIze.y*0.5f, 0.f };
		m_pPoint[1] = { m_tInfo.vPos.x + m_tInfo.vSIze.x*0.5f, m_tInfo.vPos.y - m_tInfo.vSIze.y*0.5f, 0.f };
		m_pPoint[2] = { m_tInfo.vPos.x + m_tInfo.vSIze.x*0.5f, m_tInfo.vPos.y + m_tInfo.vSIze.y*0.5f, 0.f };
		m_pPoint[3] = { m_tInfo.vPos.x - m_tInfo.vSIze.x*0.5f, m_tInfo.vPos.y + m_tInfo.vSIze.y*0.5f, 0.f };

		for (int i = 0; i < 4; ++i)
		{
			m_pOriginPoint[i] = m_pPoint[i];
		}

		m_bCount = true;
	}
	return 0;
}

void CGoal4::Late_Update(void)
{
	
}

void CGoal4::Render(HDC hDC)
{
	MoveToEx(hDC, m_pPoint[0].x, m_pPoint[0].y, nullptr);
	
	for (int i = 0; i < 4; ++i)
	{
		LineTo(hDC, m_pPoint[i].x, m_pPoint[i].y);
	}
	LineTo(hDC, m_pPoint[0].x, m_pPoint[0].y);

	TCHAR szGoal[32] = L"";
	swprintf_s(szGoal, L"Goal");
	TextOut(hDC, m_tInfo.vPos.x - m_tInfo.vSIze.x*0.3f, m_tInfo.vPos.y, szGoal, lstrlen(szGoal));
}

void CGoal4::Release(void)
{
}
