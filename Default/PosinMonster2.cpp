#include "stdafx.h"
#include "PosinMonster2.h"
#include "Bullet2.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "CollisionMgr.h"
#include "Item2.h"
#include "NormalItem2.h"
#include "Player2.h"
CPosinMonster2::CPosinMonster2()
{
}


CPosinMonster2::~CPosinMonster2()
{
}


void CPosinMonster2::Initialize(void)
{
	m_bDead = false;
	m_fSpeed = 5.f;
	m_tInfo.vLook = { 1.f, 0.f, 0.f };
	m_vGunPosin = { m_tInfo.vPos.x, m_tInfo.vPos.y - 50, 0.f };

	m_originGunPoint = m_vGunPosin;
	m_vInitPoint = m_tInfo.vPos;
	m_dBulletTime = GetTickCount();
	m_tInfo.vSIze.x = 50.f;
	m_tInfo.vSIze.y = 50.f;

	m_iHp = 3;
	m_iAttack = 1;
}

int CPosinMonster2::Update(void)
{
	Collision_Check();

	if (m_iHp <= 0)
		m_bDead = true;

	if (m_bDead)
	{

		dynamic_cast<CPlayer2*>(CObjMgr::Get_Instance()->Get_Player())->Set_iScore();
		CObj*	pItem = new CNormalItem2;
		pItem->Set_Pos(m_tInfo.vPos.x, m_tInfo.vPos.y);
		pItem->Initialize();
		CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, pItem);
		
		return OBJ_DEAD;
	}

	m_tInfo.vDir = m_pPlayer->Get_Info().vPos - m_tInfo.vPos;

	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

	D3DXVECTOR3 vecGunLook = { 0.f, -1.f, 0.f };

	float fDot = D3DXVec3Dot(&m_tInfo.vDir, &vecGunLook);

	float m_fPosinAngle = acosf(fDot);

	if (m_tInfo.vDir.x * vecGunLook.y - m_tInfo.vDir.y * vecGunLook.x > 0)
		m_fPosinAngle = 2.f * D3DX_PI - m_fPosinAngle;

	D3DXMATRIX	matScale, matRotate, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);

	D3DXMatrixRotationZ(&matRotate, m_fPosinAngle);

	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matRotate * matTrans;

	m_vGunPosin = m_originGunPoint;

	m_vGunPosin -= m_vInitPoint;

	D3DXVec3TransformCoord(&m_vGunPosin, &m_vGunPosin, &m_tInfo.matWorld);

	if (m_dBulletTime + 3000 < GetTickCount())
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, Create_Bullet());

		m_dBulletTime = GetTickCount();
	}

	Monster_Move();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CPosinMonster2::Late_Update(void)
{
}

void CPosinMonster2::Render(HDC hDC)
{

	bool bPlayerDead = dynamic_cast<CPlayer2*>(CObjMgr::Get_Instance()->Get_Player())->Get_PlayerDead();

	if (!bPlayerDead)
	{
		Ellipse(hDC,
			m_tRect.left,
			m_tRect.top,
			m_tRect.right,
			m_tRect.bottom);

		MoveToEx(hDC, m_tInfo.vPos.x, m_tInfo.vPos.y, nullptr);
		LineTo(hDC, m_vGunPosin.x, m_vGunPosin.y);
	}
}

void CPosinMonster2::Release(void)
{
}

CObj * CPosinMonster2::Create_Bullet()
{
	CObj*		pBullet = new CBullet2;

	pBullet->Set_Pos(m_vGunPosin.x, m_vGunPosin.y);
	dynamic_cast<CBullet2*>(pBullet)->Set_Dir(m_tInfo.vDir);
	dynamic_cast<CBullet2*>(pBullet)->Set_Angle(-m_fPosinAngle - 4.8);
	dynamic_cast<CBullet2*>(pBullet)->Set_BulletType(OBJ_MONSTER);

	pBullet->Initialize();

	return pBullet;
}


void CPosinMonster2::Monster_Move()
{
	m_tInfo.vPos.x -= 1.f;
}

void CPosinMonster2::Collision_Check()
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
