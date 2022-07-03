#include "stdafx.h"
#include "ShieldItem2.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"
#include "Bullet2.h"
#include "Player2.h"

CShieldItem2::CShieldItem2()
{

}


CShieldItem2::~CShieldItem2()
{

}

void CShieldItem2::Initialize(void)
{
	m_iHp = 2;

	m_vPoint[0] = { m_tInfo.vPos.x - 10, m_tInfo.vPos.y - 10, m_tInfo.vPos.z };
	m_vPoint[1] = { m_tInfo.vPos.x + 10, m_tInfo.vPos.y - 10, m_tInfo.vPos.z };
	m_vPoint[2] = { m_tInfo.vPos.x + 10, m_tInfo.vPos.y + 10, m_tInfo.vPos.z };
	m_vPoint[3] = { m_tInfo.vPos.x - 10, m_tInfo.vPos.y + 10, m_tInfo.vPos.z };
	
	for (int i = 0; i < 4; ++i)
	{
		m_vOriginPoint[i] = m_vPoint[i];
	}

	m_fAngle = 0.f;
	m_vInitPoint = m_tInfo.vPos;	
	m_tInfo.vSIze.x = 20;
	m_tInfo.vSIze.y = 20;

	m_eItemType = ITEM_SHIELD;

	m_fAngle2 = 0.f;
	m_fDistance = 80.f;
}

int CShieldItem2::Update(void)
{
	Collision_Check();

	if (m_iHp <= 0)
		m_bDead = true;

	if (m_bDead)
		return OBJ_DEAD;

	CObj* pPlayer = CObjMgr::Get_Instance()->Get_Player();

	float playerX = pPlayer->Get_Info().vPos.x;
	float playerY = pPlayer->Get_Info().vPos.y;

	m_tInfo.vPos = pPlayer->Get_Info().vPos;

	m_fAngle += 0.1f;
	m_fAngle2 += 3.f;

	m_tInfo.vPos.x += m_fDistance * cosf(m_fAngle2 * D3DX_PI / 180);
	m_tInfo.vPos.y -= m_fDistance * sinf(m_fAngle2 * D3DX_PI / 180);

	D3DXMATRIX matRotateZ, matTrans;

	D3DXMatrixRotationZ(&matRotateZ, m_fAngle);

	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	matWorld = matRotateZ * matTrans;

	for (int i = 0; i < 4; i++)
	{
		m_vPoint[i] = m_vOriginPoint[i];
		m_vPoint[i] -= {m_vInitPoint.x, m_vInitPoint.y, m_vInitPoint.z};

		D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &matWorld);
	}
	return OBJ_NOEVENT;
}

void CShieldItem2::Late_Update(void)
{
}

void CShieldItem2::Render(HDC hDC)
{

	bool bPlayerDead = dynamic_cast<CPlayer2*>(CObjMgr::Get_Instance()->Get_Player())->Get_PlayerDead();

	if (!bPlayerDead)
	{
		MoveToEx(hDC, m_vPoint[0].x, m_vPoint[0].y, nullptr);

		for (int i = 0; i < 4; ++i)
		{
			LineTo(hDC, m_vPoint[i].x, m_vPoint[i].y);
		}
		LineTo(hDC, m_vPoint[0].x, m_vPoint[0].y);
	}

}

void CShieldItem2::Collision_Check()
{
	list<CObj*>* Bulletlist = CObjMgr::Get_Instance()->Get_IDlist(OBJ_BULLET);

	for (auto& iter = Bulletlist->begin(); iter != Bulletlist->end(); iter++)
	{
		if (CCollisionMgr::ChecK_Sphere(this, (*iter)))
		{
			OBJID bulletID = dynamic_cast<CBullet2*>(*iter)->Get_BulletType();
			if (bulletID == OBJ_MONSTER)
			{
				dynamic_cast<CBullet2*>(*iter)->Set_Dead();
				m_iHp--;
			}
		}
	}
}

void CShieldItem2::Release(void)
{

}