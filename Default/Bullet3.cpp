#include "stdafx.h"
#include "Bullet3.h"


CBullet3::CBullet3()
{
}


CBullet3::~CBullet3()
{
}

void CBullet3::Initialize(void)
{




	m_fSpeed = 10.f;

}

int CBullet3::Update(void)
{

	if (m_bDead)
		return OBJ_DEAD;

	if (m_bFront)
	{
		m_pFrameKey = L"ShootingStar_Right";
	}
	if (m_bFront == false)
	{
		m_pFrameKey = L"ShootingStar_Left";
	}

	if (m_bFront)
		m_tInfo.vPos.x += m_fSpeed;
	
	else
		m_tInfo.vPos.x -= m_fSpeed;
	return OBJ_NOEVENT;
}


void CBullet3::Late_Update(void)
{

	if (m_dwTime + 2000 < GetTickCount())
		m_bDead = true;
}

void CBullet3::Render(HDC hDC)
{


	Ellipse(hDC,
		int(m_tInfo.vPos.x - 50.f),
		int(m_tInfo.vPos.y - 50.f),
		int(m_tInfo.vPos.x + 50.f),
		int(m_tInfo.vPos.y + 50.f));
}

void CBullet3::Release(void)
{
}