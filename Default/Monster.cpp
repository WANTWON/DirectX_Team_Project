#include "stdafx.h"
#include "Monster.h"
#include "ObjMgr.h"


CMonster::CMonster()
{
}


CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize(void)
{
	m_tInfo.vPos = { 100.f, 100.f, 0.f };
	m_fSpeed = 5.f;
	
}

int CMonster::Update(void)
{

	



	m_tInfo.vDir = m_pPlayer->Get_Info().vPos - m_tInfo.vPos;

	float		fLength = sqrtf(m_tInfo.vDir.x * m_tInfo.vDir.x + m_tInfo.vDir.y * m_tInfo.vDir.y);

	m_tInfo.vDir.x /= fLength;
	m_tInfo.vDir.y /= fLength;
	m_tInfo.vDir.z = 0.f;

	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;

	return OBJ_NOEVENT;
}

void CMonster::Late_Update(void)
{
}

void CMonster::Render(HDC hDC)
{
	Ellipse(hDC,
		int(m_tInfo.vPos.x - 50.f),
		int(m_tInfo.vPos.y - 50.f),
		int(m_tInfo.vPos.x + 50.f),
		int(m_tInfo.vPos.y + 50.f));
}

void CMonster::Release(void)
{
	
}
