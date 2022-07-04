#include "stdafx.h"
#include "Item.h"

CItem::CItem()
	:m_fAngle(0),m_bDead(false), m_dTime(GetTickCount())
{
	ZeroMemory(&m_rc, sizeof(RECT));
}


CItem::~CItem()
{
}


void CItem::Initialize(void)
{
	m_tInfo.vPos = { 400.f, 300.f, 0.f };
	m_tInfo.vLook = { 0.f, -1.f, 0.f };
	m_fSpeed = 10.f;

}

int CItem::Update(void)
{
	if(m_bDead)
		return OBJ_DEAD;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CItem::Late_Update(void)
{
	if (m_dTime + 7000 < GetTickCount())
	{
		m_bDead = true;
		m_dTime = GetTickCount();
	}
	Update_Rect();
}

void CItem::Render(HDC hDC)
{

	Ellipse(hDC,
		m_rc.left,
		m_rc.top,
		m_rc.right,
		m_rc.bottom);
}

void CItem::Release(void)
{
}

void CItem::Update_Rect()
{
	for (int i = 0; i < 2; ++i)
	{
		m_rc.left = int(m_tInfo.vPos.x - 7.f);
		m_rc.top = int(m_tInfo.vPos.y - 7.f);
		m_rc.right = int(m_tInfo.vPos.x + 7.f);
		m_rc.bottom = int(m_tInfo.vPos.y + 7.f);
	}
}

