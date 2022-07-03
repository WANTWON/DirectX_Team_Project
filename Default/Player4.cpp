#include "stdafx.h"
#include "Player4.h"
#include "KeyMgr.h"
#include "AbstractFactory.h"
#include "Bullet4.h"
#include "ObjMgr.h"
#include "Obj.h"
#include "SceneMgr.h"
#include "CollisionMgr.h"


CPlayer4::CPlayer4(): m_bClear(false)
{
}


CPlayer4::~CPlayer4()
{
	Release();
}

void CPlayer4::Initialize(void)
{


	m_tInfo.vSIze = { 50.f, 50.f, 0.f };
	m_tInfo.vPos = { 400.f, 500.f, 0.f };
	m_tInfo.vLook = { 0.f, -1.f, 0.f };
	
	m_fSpeed = 5.f;

	m_vPoint[0] = { m_tInfo.vPos.x - m_tInfo.vSIze.x*0.5f, m_tInfo.vPos.y - m_tInfo.vSIze.y*0.5f, 0.f };
	m_vPoint[1] = { m_tInfo.vPos.x + m_tInfo.vSIze.x*0.5f, m_tInfo.vPos.y - m_tInfo.vSIze.y*0.5f, 0.f };
	m_vPoint[2] = { m_tInfo.vPos.x + m_tInfo.vSIze.x*0.5f, m_tInfo.vPos.y + m_tInfo.vSIze.y*0.5f, 0.f };
	m_vPoint[3] = { m_tInfo.vPos.x - m_tInfo.vSIze.x*0.5f, m_tInfo.vPos.y + m_tInfo.vSIze.y*0.5f, 0.f };

	for (int i = 0; i < 4; ++i)
	{
		m_pOriginPoint[i] = m_vPoint[i];
	}

	m_pPosin = { m_tInfo.vPos.x , m_tInfo.vPos.y - 50 , 0.f };
	m_pOriginPosin = m_pPosin;

	D3DXMatrixIdentity(&m_tInfo.matWorld); 
}

int CPlayer4::Update(void)
{
	
	Key_Input();

	if (m_bDead)
		return OBJ_DEAD;

	D3DXMATRIX matScale, matRotZ, matTrans;
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale*matRotZ*matTrans;

	for (int i = 0; i < 4; ++i)
	{
		m_vPoint[i] = m_pOriginPoint[i];
		m_vPoint[i] -= {400, 500, 0};

		D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
	}
	

	D3DXVECTOR3 vTemp = m_pOriginPosin;
	vTemp -= {400, 500, 0.f};

	m_pPosin.x = cosf(m_fPosinAngle)*vTemp.x - sinf(m_fPosinAngle)*vTemp.y;
	m_pPosin.y = sinf(m_fPosinAngle)*vTemp.x + cosf(m_fPosinAngle)*vTemp.y;
	m_pPosin += m_tInfo.vPos;


	return OBJ_NOEVENT;
}

void CPlayer4::Late_Update(void)
{
	CCollisionMgr::Collision_Rect_Ex(*(CObjMgr::Get_Instance()->Get_IDlist(OBJ_PLAYER)), *(CObjMgr::Get_Instance()->Get_IDlist(OBJ_MONSTER)));
}

void CPlayer4::Render(HDC hDC)
{
	TCHAR szScore[32] = L"";
	swprintf_s(szScore, L"Score :  %d", m_iScore);
	TCHAR szClear[32] = L"";
	swprintf_s(szClear, L"√÷¡æ Score :  %d", m_iScore);

	MoveToEx(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y, nullptr);

	for (int i = 0; i < 4; ++i)
	{
		LineTo(hDC, (int)m_vPoint[i].x, (int)m_vPoint[i].y);

		if (i < 2)
			Ellipse(hDC, (int)m_vPoint[i].x -5, (int)m_vPoint[i].y - 5,(int)m_vPoint[i].x + 5, (int)m_vPoint[i].y + 5);
	}
	LineTo(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y);



	MoveToEx(hDC, (int)m_pPosin.x, (int)m_pPosin.y, nullptr);
	LineTo(hDC, (int)m_tInfo.vPos.x, (int)m_tInfo.vPos.y);

	if (!m_bDead)
		TextOut(hDC, 20, 20, szScore, lstrlen(szScore));
	if (m_bClear)
		TextOut(hDC, 350, 200, szClear, lstrlen(szClear));
}

void CPlayer4::Release(void)
{
}

void CPlayer4::Key_Input(void)
{
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
	{
		m_fAngle -= D3DXToRadian(3);
		m_fPosinAngle -= D3DXToRadian(3);
	}
		
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
		m_fAngle += D3DXToRadian(3);
		m_fPosinAngle += D3DXToRadian(3);
	}
		


	if (CKeyMgr::Get_Instance()->Key_Pressing('A'))
		m_fPosinAngle -= D3DXToRadian(3);
	else if (CKeyMgr::Get_Instance()->Key_Pressing('D'))
		m_fPosinAngle += D3DXToRadian(3);


	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
	{

		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld); 
		m_tInfo.vPos += m_tInfo.vDir* m_fSpeed;
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
	{
		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld); 
		m_tInfo.vPos -= m_tInfo.vDir* m_fSpeed;
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		CObj* pObj = CAbstractFactory<CBullet4>::Create(m_pPosin.x, m_pPosin.y);
		static_cast<CBullet4*>(pObj)->Set_Player(this);
		static_cast<CBullet4*>(pObj)->Set_Pos(m_pPosin);
		static_cast<CBullet4*>(pObj)->Set_Angle(m_fPosinAngle);
		CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, pObj);
	}

}
