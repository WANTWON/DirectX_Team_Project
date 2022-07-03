#include "stdafx.h"
#include "Monster4.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "Obj.h"
#include "Player4.h"
#include "SceneMgr.h"


CMonster4::CMonster4() : m_bMove(false), m_bCount(false)
{

}


CMonster4::~CMonster4()
{
	Release();
}

void CMonster4::Initialize(void)
{
	m_tInfo.vSIze = { 20.f, 20.f , 0.f };
	m_tInfo.vPos = { 400.f, 300.f, 0.f };
	m_pOriginPos = m_tInfo.vPos;
	m_vPoint[0] = { m_tInfo.vPos.x - m_tInfo.vSIze.x*0.25f, m_tInfo.vPos.y - m_tInfo.vSIze.y*0.5f, 0.f };
	m_vPoint[1] = { m_tInfo.vPos.x + m_tInfo.vSIze.x*0.25f, m_tInfo.vPos.y - m_tInfo.vSIze.y*0.5f, 0.f };
	m_vPoint[2] = { m_tInfo.vPos.x + m_tInfo.vSIze.x*0.5f, m_tInfo.vPos.y - m_tInfo.vSIze.y*0.25f, 0.f };
	m_vPoint[3] = { m_tInfo.vPos.x + m_tInfo.vSIze.x*0.5f, m_tInfo.vPos.y + m_tInfo.vSIze.y*0.25f, 0.f };
	m_vPoint[4] = { m_tInfo.vPos.x + m_tInfo.vSIze.x*0.25f, m_tInfo.vPos.y + m_tInfo.vSIze.y*0.5f, 0.f };
	m_vPoint[5] = { m_tInfo.vPos.x - m_tInfo.vSIze.x*0.25f, m_tInfo.vPos.y + m_tInfo.vSIze.y*0.5f, 0.f };
	m_vPoint[6] = { m_tInfo.vPos.x - m_tInfo.vSIze.x*0.5f, m_tInfo.vPos.y + m_tInfo.vSIze.y*0.25f, 0.f };
	m_vPoint[7] = { m_tInfo.vPos.x - m_tInfo.vSIze.x*0.5f, m_tInfo.vPos.y - m_tInfo.vSIze.y*0.25f, 0.f };

	for (int i = 0; i < 8; ++i)
	{
		m_pOriginPoint[i] = m_vPoint[i];
	}
}

int CMonster4::Update(void)
{
	if (m_bDead)
	{
		if (m_eState == RED)
			static_cast<CPlayer4*>(CObjMgr::Get_Instance()->Get_Player())->Set_Clear();
		return OBJ_DEAD;
	}
		
		
	D3DXMATRIX matRotZ, matTrans;

	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	m_tInfo.matWorld = matRotZ*matTrans;

	for (int i = 0; i < 8; ++i)
	{
		m_vPoint[i] = m_pOriginPoint[i];
		m_vPoint[i] -= m_pOriginPos;

		D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
	}
}

void CMonster4::Late_Update(void)
{
	//if (CCollisionMgr::Collision_Sphere(*(CObjMgr::Get_Instance()->Get_IDlist(OBJ_BULLET)), *(CObjMgr::Get_Instance()->Get_IDlist(OBJ_MONSTER))))
		//m_bDead = true;

	for (int i = 0; i < 8; ++i)
	{
		if (m_vPoint[i].x > WINCX || m_vPoint[i].x < 0)
		{
			if (m_bCount)
				break;
			m_fAngle *= -1;
			m_pDirVector.x *= -1;
			m_bCount = true;
		}
		else if (m_vPoint[i].y < 0 || m_vPoint[i].y > WINCY)
		{
			if (m_bCount)
				break;
			m_pDirVector.y *= -1;
			m_bCount = true;

		}
	}

	if(m_tInfo.vPos.x > 0 + m_tInfo.vSIze.x*0.5f && m_tInfo.vPos.x < WINCX - m_tInfo.vSIze.x*0.5f 
		&& m_tInfo.vPos.y >0 + m_tInfo.vSIze.y*0.5f && m_tInfo.vPos.y < WINCY - m_tInfo.vSIze.y*0.5f)
		m_bCount = false;

	if (CCollisionMgr::Collision_Sphere(*(CObjMgr::Get_Instance()->Get_IDlist(OBJ_BLOCK)), this))
	{
		m_bDead = true;
		dynamic_cast<CPlayer4*>((*CObjMgr::Get_Instance()->Get_IDlist(OBJ_PLAYER)).front())->Set_Score(100);
	}
		


	if (CCollisionMgr::Collision_Sphere_with_Monster4(*(CObjMgr::Get_Instance()->Get_IDlist(OBJ_MONSTER)), this))
	{
		m_bMove = true;
		m_fSpeed = 4.f;
		m_fMoveAngle = 3.f;
	}
	if (CCollisionMgr::Collision_Sphere_with_Bullet(*(CObjMgr::Get_Instance()->Get_IDlist(OBJ_BULLET)), this))
	{
		m_bMove = true;
		m_fSpeed = 4.f;
		m_fMoveAngle = 3.f;

	}
	if (CCollisionMgr::Collision_Point(dynamic_cast<CPlayer4*>((*CObjMgr::Get_Instance()->Get_IDlist(OBJ_PLAYER)).front())->Get_PosinPoint(), this))
	{
		m_bMove = true;

		if (static_cast<CPlayer4*>(CObjMgr::Get_Instance()->Get_Player())->Get_State() == CPlayer4::SHOOT)
		{
			m_fSpeed = 5.f;
			m_fMoveAngle = 5.f;
		}
		else
		{
			m_fSpeed = 2.f;
			m_fMoveAngle = 2.f;
		}
		

	}

	if (m_bMove)
	{
		m_fAngle += D3DXToRadian(m_fMoveAngle);
		m_tInfo.vPos += m_pDirVector*m_fSpeed;
		m_fSpeed -= 0.01f;
		m_fMoveAngle -= 0.01f;

		if (m_fSpeed <= 0)
			m_bMove = false;
	}
		
}

void CMonster4::Render(HDC hDC)
{

	if (m_eState == RED)
	{
		HPEN hNewPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		HGDIOBJ hOldPen = SelectObject(hDC, hNewPen);

		MoveToEx(hDC, m_vPoint[0].x, m_vPoint[0].y, nullptr);

		for (int i = 0; i < 8; ++i)
		{
			LineTo(hDC, m_vPoint[i].x, m_vPoint[i].y);

		}
		LineTo(hDC, m_vPoint[0].x, m_vPoint[0].y);

		SelectObject(hDC, hOldPen);
		DeleteObject(hNewPen);
	}
	else
	{
		

		MoveToEx(hDC, m_vPoint[0].x, m_vPoint[0].y, nullptr);

		for (int i = 0; i < 8; ++i)
		{
			LineTo(hDC, m_vPoint[i].x, m_vPoint[i].y);

		}
		LineTo(hDC, m_vPoint[0].x, m_vPoint[0].y);

	}
	

}

void CMonster4::Release(void)
{
}
