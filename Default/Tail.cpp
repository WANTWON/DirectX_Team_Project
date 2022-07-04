#include "stdafx.h"
#include "Tail.h"


CTail::CTail()
	:m_fAngle(0)
{
	ZeroMemory(&m_rc, sizeof(RECT));
}


CTail::~CTail()
{
}


void CTail::Initialize(void)
{
	m_tInfo.vPos = { 400.f, 300.f, 0.f };
	m_tInfo.vLook = { 0.f, -1.f, 0.f };
	m_fSpeed = 10.f;

}

int CTail::Update(void)
{

	Update_Rect();
	
	return OBJ_NOEVENT;
}

void CTail::Late_Update(void)
{
	Update_Rect();
}

void CTail::Render(HDC hDC)
{

	Ellipse(hDC,
		m_rc.left,
		m_rc.top,
		m_rc.right,
		m_rc.bottom);
}

void CTail::Release(void)
{
}

void CTail::Update_Rect()
{
	for (int i = 0; i < 2; ++i)
	{
		m_rc.left = int(m_tInfo.vPos.x - 7.f);
		m_rc.top = int(m_tInfo.vPos.y - 7.f);
		m_rc.right = int(m_tInfo.vPos.x + 7.f);
		m_rc.bottom = int(m_tInfo.vPos.y + 7.f);
	}
}

