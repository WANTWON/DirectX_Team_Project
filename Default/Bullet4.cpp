#include "stdafx.h"
#include "Bullet4.h"


CBullet4::CBullet4() : m_pPlayer(nullptr), m_bCount(false)
{
}


CBullet4::~CBullet4()
{
}

void CBullet4::Initialize(void)
{
	m_tInfo.vSIze = { 25.f, 25.f, 0.f };
	m_tInfo.vPos = { 200,300 , 0 };
	m_tInfo.vDir = { 0, -1, 0 };
	m_tInfo.vLook = { 0, -1, 0 };

	m_fSpeed = 5.f;

	

}

int CBullet4::Update(void)
{

	if (!m_bCount)
	{
		m_vPoint[0] = { m_tInfo.vPos.x - m_tInfo.vSIze.x*0.5f, m_tInfo.vPos.y - m_tInfo.vSIze.y*0.5f, 0.f };
		m_vPoint[1] = { m_tInfo.vPos.x + m_tInfo.vSIze.x*0.5f, m_tInfo.vPos.y - m_tInfo.vSIze.y*0.5f, 0.f };
		m_vPoint[2] = { m_tInfo.vPos.x + m_tInfo.vSIze.x*0.5f, m_tInfo.vPos.y + m_tInfo.vSIze.y*0.5f, 0.f };
		m_vPoint[3] = { m_tInfo.vPos.x - m_tInfo.vSIze.x*0.5f, m_tInfo.vPos.y + m_tInfo.vSIze.y*0.5f, 0.f };


		for (int i = 0; i < 4; ++i)
		{
			m_vOriginPoint[i] = m_vPoint[i];
		}

		m_tInfo.vDir = m_tInfo.vPos - m_pPlayer->Get_Info().vPos;  
		m_bCount = true;
	}

	 D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);


	 D3DXMATRIX matRotZ, matTrans;

	 D3DXMatrixRotationZ(&matRotZ, m_fAngle);	//각도 만큼 회전 시킨건데
	 D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	 m_tInfo.matWorld = matRotZ *matTrans;

	for (int i = 0; i < 4; ++i)
	{
		m_vPoint[i] = m_vOriginPoint[i];
		m_vPoint[i] -= m_vOriginPos;
		D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);

		/*
		D3DXVECTOR3  vTemp = = m_vOriginPoint[i];
		vTemp -= m_vOriginPos;

		m_vPoint[i].x = cosf(m_fAngle)*vTemp.x - sinf(m_fAngle)*vTemp.y;
		m_vPoint[i].y = sinf(m_fAngle)*vTemp.x + cosf(m_fAngle)*vTemp.y;
		m_vPoint[i] += m_tInfo.vPos;
		*/
	}

	m_tInfo.vPos.x += m_tInfo.vDir.x * m_fSpeed;
	m_tInfo.vPos.y += m_tInfo.vDir.y * m_fSpeed;

	return OBJ_NOEVENT;
}

void CBullet4::Late_Update(void)
{
}

void CBullet4::Render(HDC hDC)
{
	MoveToEx(hDC, m_vPoint[0].x, m_vPoint[0].y, nullptr);

	for (int i = 0; i < 4; ++i)
	{
		LineTo(hDC, m_vPoint[i].x, m_vPoint[i].y);

		if (i < 2)
			Ellipse(hDC, m_vPoint[i].x - 5, m_vPoint[i].y - 5, m_vPoint[i].x + 5, m_vPoint[i].y + 5);
	}
	LineTo(hDC, m_vPoint[0].x, m_vPoint[0].y);
}

void CBullet4::Release(void)
{
}
