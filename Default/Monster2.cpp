#include "stdafx.h"
#include "Monster2.h"
#include "ObjMgr.h"

CMonster2::CMonster2()
{
}


CMonster2::~CMonster2()
{
}

void CMonster2::Initialize(void)
{
	m_bDead = false;
	//m_tInfo.vPos = { 100.f, 100.f, 0.f };
	m_fSpeed = 5.f;
	m_dBulletTime = GetTickCount();
}

int CMonster2::Update(void)
{
	m_tInfo.vDir = m_pPlayer->Get_Info().vPos - m_tInfo.vPos;

	float		fLength = sqrtf(m_tInfo.vDir.x * m_tInfo.vDir.x + m_tInfo.vDir.y * m_tInfo.vDir.y);

	m_tInfo.vDir.x /= fLength;
	m_tInfo.vDir.y /= fLength;
	m_tInfo.vDir.z = 0.f;

	//m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	

	if (m_dBulletTime + 3000 < GetTickCount())
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, Create_Bullet(DIR_LT));

		m_dBulletTime = GetTickCount();
	}


	return 0;
}

void CMonster2::Late_Update(void)
{
}

void CMonster2::Render(HDC hDC)
{
	Ellipse(hDC,
		int(m_tInfo.vPos.x - 30.f),
		int(m_tInfo.vPos.y - 30.f),
		int(m_tInfo.vPos.x + 30.f),
		int(m_tInfo.vPos.y + 30.f));
}

void CMonster2::Release(void)
{
}


void CMonster2::Monster_Move()
{
	m_tInfo.vPos.x -= 1.f;
}

CObj * CMonster2::Create_Bullet(DIRECTION eDir)
{
	return nullptr;
}

