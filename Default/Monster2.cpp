#include "stdafx.h"
#include "Monster2.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"
#include "Bullet2.h"
#include "Player2.h"

CMonster2::CMonster2()
{
}


CMonster2::~CMonster2()
{
}

void CMonster2::Initialize(void)
{
	m_bDead = false;
	m_fSpeed = 10.f;
	m_dBulletTime = GetTickCount();
	m_tInfo.vSIze.x = 30.f;
	m_tInfo.vSIze.y = 30.f;
	m_iHp = 1;
	m_iAttack = 1;
}

int CMonster2::Update(void)
{
	Collision_Check();

	if (m_iHp <= 0)
		m_bDead = true;

	if (m_bDead)
	{
		dynamic_cast<CPlayer2*>(CObjMgr::Get_Instance()->Get_Player())->Set_iScore();
		return 1;
	}

	Monster_Move();

	m_tInfo.vDir = m_pPlayer->Get_Info().vPos - m_tInfo.vPos;

	float		fLength = sqrtf(m_tInfo.vDir.x * m_tInfo.vDir.x + m_tInfo.vDir.y * m_tInfo.vDir.y);

	m_tInfo.vDir.x /= fLength;
	m_tInfo.vDir.y /= fLength;
	m_tInfo.vDir.z = 0.f;

	if (m_dBulletTime + 3000 < GetTickCount())
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, Create_Bullet(DIR_LT));

		m_dBulletTime = GetTickCount();
	}

	return 0;
}

void CMonster2::Late_Update(void)
{
	Update_Rect();
}

void CMonster2::Render(HDC hDC)
{

	bool bPlayerDead = dynamic_cast<CPlayer2*>(CObjMgr::Get_Instance()->Get_Player())->Get_PlayerDead();


	if (!bPlayerDead)
	{
		Rectangle(hDC,
			m_tRect.left,
			m_tRect.top,
			m_tRect.right,
			m_tRect.bottom);
	}

}

void CMonster2::Release(void)
{
}

void CMonster2::Monster_Move()
{
	m_tInfo.vPos.x -= 2.f;
}

CObj * CMonster2::Create_Bullet(DIRECTION eDir)
{
	return nullptr;
}

void CMonster2::Collision_Check()
{
	list<CObj*>* Bulletlist = CObjMgr::Get_Instance()->Get_IDlist(OBJ_BULLET);

	for (auto& iter = Bulletlist->begin(); iter != Bulletlist->end(); iter++)
	{
		if (CCollisionMgr::ChecK_Sphere(this, (*iter)))
		{
			OBJID bulletID = dynamic_cast<CBullet2*>(*iter)->Get_BulletType();
			if (bulletID == OBJ_PLAYER)
			{
				dynamic_cast<CBullet2*>(*iter)->Set_Dead();
				--m_iHp;
			}
		}
	}
}

