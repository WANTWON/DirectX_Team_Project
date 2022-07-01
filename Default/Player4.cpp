#include "stdafx.h"
#include "Player4.h"
#include "KeyMgr.h"


CPlayer4::CPlayer4()
{
}


CPlayer4::~CPlayer4()
{
	Release();
}

void CPlayer4::Initialize(void)
{
	m_tInfo.vSIze = { 50.f, 50.f, 0.f };
	m_tInfo.vPos = { 400.f, 300.f, 0.f };
	m_tInfo.vLook = { 0.f, -1.f, 0.f };
	
	m_fSpeed = 5.f;

	m_pPoint[0] = { m_tInfo.vPos.x - m_tInfo.vSIze.x*0.5f, m_tInfo.vPos.y - m_tInfo.vSIze.y*0.5f, 0.f };
	m_pPoint[1] = { m_tInfo.vPos.x + m_tInfo.vSIze.x*0.5f, m_tInfo.vPos.y - m_tInfo.vSIze.y*0.5f, 0.f };
	m_pPoint[2] = { m_tInfo.vPos.x + m_tInfo.vSIze.x*0.5f, m_tInfo.vPos.y + m_tInfo.vSIze.y*0.5f, 0.f };
	m_pPoint[3] = { m_tInfo.vPos.x - m_tInfo.vSIze.x*0.5f, m_tInfo.vPos.y + m_tInfo.vSIze.y*0.5f, 0.f };

	for (int i = 0; i < 4; ++i)
	{
		m_pOriginPoint[i] = m_pPoint[i];
	}


	D3DXMatrixIdentity(&m_tInfo.matWorld); //항등행렬로 만들기

}

int CPlayer4::Update(void)
{
	D3DXMATRIX matScale, matRotZ, matTrans;

	Key_Input();

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale*matRotZ*matTrans;

	for (int i = 0; i < 4; ++i)
	{
		m_pPoint[i] = m_pOriginPoint[i];
		m_pPoint[i] -= {400, 300, 0};

		D3DXVec3TransformCoord(&m_pPoint[i], &m_pPoint[i], &m_tInfo.matWorld);
	}
	
	

	return OBJ_NOEVENT;
}

void CPlayer4::Late_Update(void)
{
}

void CPlayer4::Render(HDC hDC)
{
	MoveToEx(hDC, m_pPoint[0].x, m_pPoint[0].y, nullptr);

	for (int i = 0; i < 4; ++i)
	{
		LineTo(hDC, m_pPoint[i].x, m_pPoint[i].y);

		if (i < 2)
			Ellipse(hDC, m_pPoint[i].x -5, m_pPoint[i].y - 5, m_pPoint[i].x + 5, m_pPoint[i].y + 5);
	}
	LineTo(hDC, m_pPoint[0].x, m_pPoint[0].y);

}

void CPlayer4::Release(void)
{
}

void CPlayer4::Key_Input(void)
{
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		m_fAngle -= D3DXToRadian(3);
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		m_fAngle += D3DXToRadian(3);



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
}
