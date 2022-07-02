#include "stdafx.h"
#include "Player2.h"
#include "Bullet2.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"

CPlayer2::CPlayer2()
{
}

CPlayer2::~CPlayer2()
{
	Release();
}

void CPlayer2::Initialize(void)
{
	m_bDead = false;
	m_tInfo.vPos = { 400.f, 300.f, 0.f };
	m_tInfo.vLook = { 0.f, -1.f, 0.f };

	m_fSpeed = 5.f;

	m_fAngle = 0.f;
	m_fPosinAngle = 0.f;

	m_vPoint[0] = { m_tInfo.vPos.x + 30.f, m_tInfo.vPos.y - 30.f, 0.f };
	m_vPoint[1] = { m_tInfo.vPos.x + 30.f, m_tInfo.vPos.y + 30.f, 0.f };
	m_vPoint[2] = { m_tInfo.vPos.x - 30.f, m_tInfo.vPos.y + 30.f, 0.f };
	m_vPoint[3] = { m_tInfo.vPos.x - 30.f, m_tInfo.vPos.y - 30.f, 0.f };

	for (int i = 0; i < 4; i++)
	{
		m_vOriginPoint[i] = m_vPoint[i];
	}
	m_vGunPoint = { m_tInfo.vPos.x , m_tInfo.vPos.y - 60.f, 0.f };
	m_vOriginGunPoint = m_vGunPoint;
	m_dBulletTime = GetTickCount();
}

int CPlayer2::Update(void)
{
	Key_Input();

#pragma region vector만쓰고 움직이기
	/*
	for (int i = 0; i < 4; ++i)
	{
	D3DXVECTOR3 vTemp = m_vOriginPoint[i];

	vTemp -= {400.f, 300.f, 0.f};

	m_vPoint[i].x = vTemp.x * cosf(m_fAngle) - vTemp.y * sinf(m_fAngle);
	m_vPoint[i].y = vTemp.x * sinf(m_fAngle) + vTemp.y * cosf(m_fAngle);

	m_vPoint[i] += {400.f, 300.f, 0.f};
	}

	D3DXVECTOR3	vTemp = m_vOriginGunPoint;

	vTemp -= {400.f, 300.f, 0.f };

	m_vGunPoint.x = vTemp.x * cosf(m_fAngle) - vTemp.y * sinf(m_fAngle);
	m_vGunPoint.y = vTemp.x * sinf(m_fAngle) + vTemp.y * cosf(m_fAngle);

	m_vGunPoint += m_tInfo.vPos;
	*/
#pragma endregion vector만쓰고 움직이기

	D3DXMATRIX	matScale, matRotate, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);

	D3DXMatrixRotationZ(&matRotate, m_fAngle);

	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matRotate * matTrans;

	for (int i = 0; i < 4; ++i)
	{
		m_vPoint[i] = m_vOriginPoint[i];
		m_vPoint[i] -= {400.f, 300.f, 0.f };

		D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
	}

	D3DXMATRIX matGunRotZ;

	vBDir = ::Get_Mouse() - m_tInfo.vPos;

	// 벡터의 정규화(단위 벡터)를 수행하는 함수
	D3DXVec3Normalize(&vBDir, &vBDir);

	D3DXVECTOR3 vecGunLook = { 0.f, -1.f, 0.f };

	float fDot = D3DXVec3Dot(&vBDir, &vecGunLook);

	m_fPosinAngle = acosf(fDot);

	if (vBDir.x * vecGunLook.y - vBDir.y * vecGunLook.x > 0)
		m_fPosinAngle = 2 * D3DX_PI - m_fPosinAngle;

	m_vGunPoint = m_vOriginGunPoint;
	m_vGunPoint -= {400.f, 300.f, 0.f };
	D3DXMatrixRotationZ(&matGunRotZ, m_fPosinAngle);
	matWorld2 = matScale * matGunRotZ * matTrans;

	D3DXVec3TransformCoord(&m_vGunPoint, &m_vGunPoint, &matWorld2);

	D3DXVec3TransformNormal(&vBDir, &m_tInfo.vLook, &matWorld2);

	return 0;
}

void CPlayer2::Late_Update(void)
{
}

void CPlayer2::Render(HDC hDC)
{
	MoveToEx(hDC, m_vPoint[0].x, m_vPoint[0].y, nullptr);

	for (int i = 0; i < 4; ++i)
	{
		LineTo(hDC, m_vPoint[i].x, m_vPoint[i].y);

		if (i > 1)
			continue;

		Ellipse(hDC,
			m_vPoint[i].x - 5.f,
			m_vPoint[i].y - 5.f,
			m_vPoint[i].x + 5.f,
			m_vPoint[i].y + 5.f);
	}
	LineTo(hDC, m_vPoint[0].x, m_vPoint[0].y);

	MoveToEx(hDC, m_tInfo.vPos.x, m_tInfo.vPos.y, nullptr);

	LineTo(hDC, m_vGunPoint.x, m_vGunPoint.y);
}

void CPlayer2::Release(void)
{
}

void CPlayer2::Key_Input(void)
{
	// GetKeyState()
	if (GetAsyncKeyState(VK_RIGHT))
		m_fPosinAngle += D3DXToRadian(3.f);

	if (GetAsyncKeyState(VK_LEFT))
		m_fPosinAngle -= D3DXToRadian(3.f);

	if (GetAsyncKeyState('A'))
		m_tInfo.vPos.x -= m_fSpeed;
		//m_fAngle -= D3DXToRadian(3.f);

	if (GetAsyncKeyState('D'))
		m_tInfo.vPos.x += m_fSpeed;
		//m_fAngle += D3DXToRadian(3.f);

	if (GetAsyncKeyState('Q'))
		m_fAngle -= D3DXToRadian(3.f);

	if (GetAsyncKeyState('E'))
		m_fAngle += D3DXToRadian(3.f);

	if (GetAsyncKeyState('W'))
	{
		m_tInfo.vPos.y -= m_fSpeed;
	}
	if (GetAsyncKeyState('S'))
	{
		m_tInfo.vPos.y += m_fSpeed;
	}

	/*if (GetAsyncKeyState('W'))
	{
		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	}
	if (GetAsyncKeyState('S'))
	{
		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
		m_tInfo.vPos -= m_tInfo.vDir * m_fSpeed;
	}*/
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if (m_dBulletTime + 100 < GetTickCount())
		{
			//m_pBullet->push_back(Create_Bullet(DIR_LT));

			CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, Create_Bullet(DIR_LT));
			m_dBulletTime = GetTickCount();
		}
	}
}

CObj* CPlayer2::Create_Bullet(DIRECTION eDir)
{
	CObj*		pBullet = new CBullet2;

	pBullet->Set_Pos(m_vGunPoint.x, m_vGunPoint.y);
	dynamic_cast<CBullet2*>(pBullet)->Set_Dir(vBDir);
	dynamic_cast<CBullet2*>(pBullet)->Set_Angle(m_fPosinAngle);

	pBullet->Initialize();

	return pBullet;
}
