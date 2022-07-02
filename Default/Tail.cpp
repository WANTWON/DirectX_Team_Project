#include "stdafx.h"
#include "Tail.h"


CTail::CTail()
	:m_fAngle(0)
{
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


	
	return OBJ_NOEVENT;
}

void CTail::Late_Update(void)
{
}

void CTail::Render(HDC hDC)
{


	Ellipse(hDC,
		int(m_tInfo.vPos.x - 14.5f),
		int(m_tInfo.vPos.y - 14.5f),
		int(m_tInfo.vPos.x + 14.5f),
		int(m_tInfo.vPos.y + 14.5f));
}

void CTail::Release(void)
{
}

