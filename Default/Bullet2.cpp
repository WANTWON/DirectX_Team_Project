#include "stdafx.h"
#include "Bullet2.h"


CBullet2::CBullet2()
{
}


CBullet2::~CBullet2()
{
}

void CBullet2::Initialize(void)
{
	m_vPoint[0] = { m_tInfo.vPos.x, m_tInfo.vPos.y - 10.f, 0.f };
	m_vPoint[1] = { m_tInfo.vPos.x + 10.f, m_tInfo.vPos.y + 10.f, 0.f };
	m_vPoint[2] = { m_tInfo.vPos.x - 10.f, m_tInfo.vPos.y + 10.f, 0.f };

	m_tInfo.vLook = { 0.f,-1.f,0.f };
	m_bDead = false;
	for (int i = 0; i < 3; ++i)
		m_vOriginPoint[i] = m_vPoint[i];

	m_fSpeed = 5.f;

	m_vInitPoint = m_tInfo.vPos;
}

int CBullet2::Update(void)
{
	if (m_bDead)
		return 1;

	D3DXMATRIX	matScale, matRotate, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);

	D3DXMatrixRotationZ(&matRotate, m_fAngle);

	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matRotate * matTrans;

	for (int i = 0; i < 3; ++i)
	{
		m_vPoint[i] = m_vOriginPoint[i];
		m_vPoint[i] -= {m_vInitPoint.x, m_vInitPoint.y, 0.f };

		D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
	}
	m_tInfo.vPos += m_eDir * m_fSpeed;

	return 0;
}

void CBullet2::Late_Update(void)
{
	if (m_tInfo.vPos.x < 0 || m_tInfo.vPos.x > WINCX - 10 || m_tInfo.vPos.y < 0 || m_tInfo.vPos.y > WINCY - 10)
		m_bDead = true;

	Update_Rect();
}

void CBullet2::Render(HDC hDC)
{
	MoveToEx(hDC, m_vPoint[0].x, m_vPoint[0].y, nullptr);
	LineTo(hDC, m_vPoint[1].x, m_vPoint[1].y);
	LineTo(hDC, m_vPoint[2].x, m_vPoint[2].y);
	LineTo(hDC, m_vPoint[0].x, m_vPoint[0].y);

	
	Ellipse(hDC, m_tInfo.vPos.x - 5.f,
		m_tInfo.vPos.y - 5.f,
		m_tInfo.vPos.x + 5.f,
		m_tInfo.vPos.y + 5.f);
		
}

void CBullet2::Release(void)
{
}
