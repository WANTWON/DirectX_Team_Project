#include "stdafx.h"
#include "Monster1.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Bullet1.h"
#include "Tail.h"
CMonster1::CMonster1()
	:m_fAngle(0.f), m_bDead(false), m_dTime(GetTickCount()), m_bTrue(false), m_dShot(GetTickCount())
{
	ZeroMemory(&m_rc, sizeof(RECT));
}


CMonster1::~CMonster1()
{
}


void CMonster1::Initialize(void)
{
}

int CMonster1::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;
	if (m_dShot + 2400 < GetTickCount())
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CBullet1>::Create(
			m_vGunPoint.x,
			m_vGunPoint.y));
		m_dShot = GetTickCount();
	}
	if (!m_bTrue)
	{
		m_vOriginPos = m_tInfo.vPos;
		m_vGunPoint = { m_tInfo.vPos.x , m_tInfo.vPos.y - 15.f, 0.f };
		m_vOriginGunPoint = m_vGunPoint;
		m_tInfo.vLook = { 0.f, -1.f, 0.f };
		m_fSpeed = 0.5f;
		m_bTrue = true;
	}

	m_tInfo.vDir = CObjMgr::Get_Instance()->Get_Player()->Get_Info().vPos - m_vGunPoint;
	
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
	D3DXVec3Normalize(&m_tInfo.vLook, &m_tInfo.vLook);
	float fDot = D3DXVec3Dot(&m_tInfo.vDir, &m_tInfo.vLook);
	m_fAngle = acosf(fDot);
	
	if (m_tInfo.vDir.x * m_tInfo.vLook.y - m_tInfo.vDir.y * m_tInfo.vLook.x > 0)
		m_fAngle = 2.f * D3DX_PI - m_fAngle;


	D3DXMATRIX	matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matRotZ * matTrans;
	m_vGunPoint = m_vOriginGunPoint;
	m_vGunPoint -= m_vOriginPos;

	D3DXVec3TransformCoord(&m_vGunPoint, &m_vGunPoint, &m_tInfo.matWorld);
	Update_Rect();

	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;

	RECT rc;
	auto& iter = CObjMgr::Get_Instance()->Get_IDlist(OBJ_MONSTER)->begin();
	for (; iter != CObjMgr::Get_Instance()->Get_IDlist(OBJ_MONSTER)->end(); ++iter)
	{
		if (IntersectRect(&rc, &m_rc, &dynamic_cast<CTail*>(*iter)->Get_Rect()))
			m_bDead = true;
	}

	return OBJ_NOEVENT;
}

void CMonster1::Late_Update(void)
{
	if (m_dTime + 5000 < GetTickCount())
	{
		m_bDead = true;
		m_dTime = GetTickCount();
	}
	Update_Rect();
}

void CMonster1::Render(HDC hDC)
{

	Rectangle(hDC,
		m_rc.left,
		m_rc.top,
		m_rc.right,
		m_rc.bottom);

	MoveToEx(hDC, (int)m_tInfo.vPos.x, (int)m_tInfo.vPos.y, nullptr);
	LineTo(hDC, (int)m_vGunPoint.x, (int)m_vGunPoint.y);
}

void CMonster1::Release(void)
{
}

void CMonster1::Update_Rect()
{
	for (int i = 0; i < 2; ++i)
	{
		m_rc.left = int(m_tInfo.vPos.x - 7.f);
		m_rc.top = int(m_tInfo.vPos.y - 7.f);
		m_rc.right = int(m_tInfo.vPos.x + 7.f);
		m_rc.bottom = int(m_tInfo.vPos.y + 7.f);
	}
}

