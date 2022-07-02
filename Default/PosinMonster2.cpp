#include "stdafx.h"
#include "PosinMonster2.h"
#include "Bullet2.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"

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
	m_vGunPosin = { m_tInfo.vPos.x, m_tInfo.vPos.y - 60, 0.f };

	m_originGunPoint = m_vGunPosin;
	m_vInitPoint = m_tInfo.vPos;
	m_dBulletTime = GetTickCount();

}

int CPosinMonster2::Update(void)
{
	m_tInfo.vDir = m_pPlayer->Get_Info().vPos - m_tInfo.vPos;

	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

	D3DXVECTOR3 vecGunLook = { 0.f, -1.f, 0.f };

	float fDot = D3DXVec3Dot(&m_tInfo.vDir, &m_tInfo.vLook);

	float m_fPosinAngle = acosf(fDot);

	if (m_tInfo.vDir.x * vecGunLook.y - m_tInfo.vDir.y * vecGunLook.x > 0)
		m_fPosinAngle = 2.f * D3DX_PI - m_fPosinAngle;

	D3DXMATRIX	matScale, matRotate, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);

	D3DXMatrixRotationZ(&matRotate, -m_fPosinAngle - 4.8);

	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matRotate * matTrans;

	m_vGunPosin = m_originGunPoint;

	m_vGunPosin -= m_vInitPoint;

	D3DXVec3TransformCoord(&m_vGunPosin, &m_vGunPosin, &m_tInfo.matWorld);

	if (m_dBulletTime + 3000 < GetTickCount())
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, Create_Bullet(DIR_LT));

		m_dBulletTime = GetTickCount();
	}

	Monster_Move();

	return 0;
}

void CPosinMonster2::Late_Update(void)
{
}

void CPosinMonster2::Render(HDC hDC)
{
	Ellipse(hDC,
		int(m_tInfo.vPos.x - 30.f),
		int(m_tInfo.vPos.y - 30.f),
		int(m_tInfo.vPos.x + 30.f),
		int(m_tInfo.vPos.y + 30.f));

	MoveToEx(hDC, m_tInfo.vPos.x, m_tInfo.vPos.y, nullptr);
	LineTo(hDC, m_vGunPosin.x, m_vGunPosin.y);

}

void CPosinMonster2::Release(void)
{
}


CObj * CPosinMonster2::Create_Bullet(DIRECTION eDir)
{
	CObj*		pBullet = new CBullet2;

	pBullet->Set_Pos(m_vGunPosin.x, m_vGunPosin.y);
	dynamic_cast<CBullet2*>(pBullet)->Set_Dir(m_tInfo.vDir);
	dynamic_cast<CBullet2*>(pBullet)->Set_Angle(-m_fPosinAngle - 4.8);

	pBullet->Initialize();

	return pBullet;
}


void CPosinMonster2::Monster_Move()
{
	m_tInfo.vPos.x -= 1.f;
}