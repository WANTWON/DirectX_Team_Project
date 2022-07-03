#include "stdafx.h"
#include "Bullet1.h"
#include "ObjMgr.h"
#include "Tail.h"
CBullet1::CBullet1()
	:m_fAngle(0), m_bDead(false), m_dTime(GetTickCount()), m_bTrue(false), m_Target(false)
{
	ZeroMemory(&m_rc, sizeof(RECT));
}


CBullet1::~CBullet1()
{
}


void CBullet1::Initialize(void)
{
	//m_tInfo.vPos = { 400.f, 300.f, 0.f };
	m_tInfo.vLook = { 0.f, -1.f, 0.f };
	m_fSpeed = 4.f;

}

int CBullet1::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (!m_bTrue)
	{
		m_vOriginPos = m_tInfo.vPos;
		m_tInfo.vLook = { 0.f, -1.f, 0.f };
		m_fSpeed = 5.f;
		m_bTrue = true;
	}
	m_tInfo.vDir = CObjMgr::Get_Instance()->Get_Player()->Get_Info().vPos - m_tInfo.vPos;
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
	D3DXVec3Normalize(&m_tInfo.vLook, &m_tInfo.vLook);
	if (!m_Target)
	{
		float fDot = D3DXVec3Dot(&m_tInfo.vDir, &m_tInfo.vLook);
		m_fAngle = acosf(fDot);
		if (m_tInfo.vDir.x * m_tInfo.vLook.y - m_tInfo.vDir.y * m_tInfo.vLook.x > 0)
			m_fAngle = 2.f * D3DX_PI - m_fAngle;
		m_Target = true;
	}
	D3DXMATRIX	matScale, matRotZ, matTrans;
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
	m_tInfo.matWorld = matScale * matRotZ * matTrans;
	m_tInfo.vPos = m_vOriginPos;
	m_tInfo.vPos -= m_vOriginPos;
	D3DXVec3TransformCoord(&m_tInfo.vPos, &m_tInfo.vPos, &m_tInfo.matWorld);
	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;


	Update_Rect();
	RECT rc;
	auto& iter = CObjMgr::Get_Instance()->Get_IDlist(OBJ_MONSTER)->begin();
	for (; iter != CObjMgr::Get_Instance()->Get_IDlist(OBJ_MONSTER)->end(); ++iter)
	{
		if (IntersectRect(&rc, &m_rc, &dynamic_cast<CTail*>(*iter)->Get_Rect()))
			m_bDead = true;
	}

	return OBJ_NOEVENT;
}

void CBullet1::Late_Update(void)
{

	Update_Rect();
	if (m_tInfo.vPos.x >= WINCX || m_tInfo.vPos.x <= 0)
		m_bDead = true;
	if (m_tInfo.vPos.y >= WINCY || m_tInfo.vPos.y <= 0)
		m_bDead = true;
}

void CBullet1::Render(HDC hDC)
{

	Ellipse(hDC,
		m_rc.left,
		m_rc.top,
		m_rc.right,
		m_rc.bottom);
}

void CBullet1::Release(void)
{
}

void CBullet1::Update_Rect()
{
	for (int i = 0; i < 2; ++i)
	{
		m_rc.left = int(m_tInfo.vPos.x - 4.5f);
		m_rc.top = int(m_tInfo.vPos.y - 4.5f);
		m_rc.right = int(m_tInfo.vPos.x + 4.5f);
		m_rc.bottom = int(m_tInfo.vPos.y + 4.5f);
	}
}

