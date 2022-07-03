#include "stdafx.h"
#include "NormalItem2.h"
#include "Player2.h"
#include "ObjMgr.h"

CNormalItem2::CNormalItem2()
{
}


CNormalItem2::~CNormalItem2()
{
	Release();
}

void CNormalItem2::Initialize(void)
{
	m_bDead = false;
	m_fSpeed = 2.f;
	m_tInfo.vSIze.x = 30.f;
	m_tInfo.vSIze.y = 30.f;

	m_vPoint[0] = { m_tInfo.vPos.x + 20.f, m_tInfo.vPos.y - 20.f, 0.f };
	m_vPoint[1] = { m_tInfo.vPos.x + 20.f, m_tInfo.vPos.y + 20.f, 0.f };
	m_vPoint[2] = { m_tInfo.vPos.x - 20.f, m_tInfo.vPos.y + 20.f, 0.f };
	m_vPoint[3] = { m_tInfo.vPos.x - 20.f, m_tInfo.vPos.y - 20.f, 0.f };
	m_fAngle = 0.f;
	m_vInitPoint = m_tInfo.vPos;

	for (int i = 0; i < 4; ++i)
		m_vOriginPoint[i] = m_vPoint[i];

	m_eItemType = ITEM_NORMAL;
}

int CNormalItem2::Update(void)
{
	if (m_bDead)
		return 1;

	D3DXMATRIX matTrans, matRotateZ;

	D3DXMatrixRotationZ(&matRotateZ, m_fAngle);

	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	matWorld = matRotateZ * matTrans;

	for (int i = 0; i < 4; ++i)
	{
		m_vPoint[i] = m_vOriginPoint[i];
		m_vPoint[i] -= m_vInitPoint;
		D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &matWorld);
	}

	Item_Move();

	Update_Rect();

	return 0;
}

void CNormalItem2::Late_Update(void)
{
}

void CNormalItem2::Render(HDC hDC)
{

	bool bPlayerDead = dynamic_cast<CPlayer2*>(CObjMgr::Get_Instance()->Get_Player())->Get_PlayerDead();

	if (!bPlayerDead)
	{
		Ellipse(hDC,
			m_tRect.left,
			m_tRect.top,
			m_tRect.right,
			m_tRect.bottom);

		TCHAR		szBuff[32] = L"";
		float fx = m_tInfo.vPos.x;
		float fy = m_tInfo.vPos.y;
		swprintf_s(szBuff, L"I");
		TextOut(hDC, fx - 2.f, fy - 8.f, szBuff, lstrlen(szBuff));
	}

}

void CNormalItem2::Item_Move()
{
	m_tInfo.vPos.x -= 2.f;
	m_fAngle += D3DXToRadian(3.f);
}

void CNormalItem2::Collision_Check()
{
}

void CNormalItem2::Release(void)
{
}

