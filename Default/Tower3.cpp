#include "stdafx.h"
#include "Tower3.h"
#include "Bullet3.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"


CTower3::CTower3()
{
}

CTower3::~CTower3()
{
	Release();
}

void CTower3::Initialize(void)
{
	m_dwTime = GetTickCount();


	if (m_Ttype == TOWER_NORMAL)
	{
		m_tInfo.vPos = { 400.f, 300.f, 0.f };
		m_tInfo.vLook = { 0.f, -1.f, 0.f };

		m_fSpeed = 10.f;

		m_vPoint[0] = { m_tInfo.vPos.x - 50.f, m_tInfo.vPos.y - 50.f, 0.f };
		m_vPoint[1] = { m_tInfo.vPos.x + 50.f, m_tInfo.vPos.y - 50.f, 0.f };
		m_vPoint[2] = { m_tInfo.vPos.x + 50.f, m_tInfo.vPos.y + 50.f, 0.f };
		m_vPoint[3] = { m_tInfo.vPos.x - 50.f, m_tInfo.vPos.y + 50.f, 0.f };

		for (int i = 0; i < 4; ++i)
			m_vOriginPoint[i] = m_vPoint[i];   // ���̴ϱ� �������� �ϳ��� ���� �ٹھƾ��ϴϱ�

											   // ����

		m_vGunPoint = { m_tInfo.vPos.x, m_tInfo.vPos.y - 100.f, 0.f };
		m_vOriginGunPoint = m_vGunPoint;
	}

	else
	    m_tInfo.vPos = { 400.f, 300.f, 0.f };
		m_tInfo.vLook = { 0.f, -1.f, 0.f };

		m_fSpeed = 10.f;

		m_vPoint[0] = { m_tInfo.vPos.x - 50.f, m_tInfo.vPos.y - 50.f, 0.f };
		m_vPoint[1] = { m_tInfo.vPos.x + 50.f, m_tInfo.vPos.y - 50.f, 0.f };
		m_vPoint[2] = { m_tInfo.vPos.x + 50.f, m_tInfo.vPos.y + 50.f, 0.f };
		m_vPoint[3] = { m_tInfo.vPos.x - 50.f, m_tInfo.vPos.y + 50.f, 0.f };

		for (int i = 0; i < 4; ++i)
			m_vOriginPoint[i] = m_vPoint[i];   // ���̴ϱ� �������� �ϳ��� ���� �ٹھƾ��ϴϱ�

											   // ����

		m_vGunPoint = { m_tInfo.vPos.x, m_tInfo.vPos.y - 100.f, 0.f };
		m_vOriginGunPoint = m_vGunPoint;
	
}






int CTower3::Update(void)
{
	//m_tInfo.vDir = m_pPlayer->Get_Info().vPos - m_tInfo.vPos; // �ڿ��ִ�(����)���Ͱ� �տ��ִ�(�÷��̾�)���͸� �ٶ󺸴� �����̳���  �÷��̾��� ��ġ���� - ������ ��ġ���� �̰��� ������ vDir �� ���⺤�ͺ����� �־�����!

	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_MONSTER, this);
	m_tInfo.vDir = m_pTarget->Get_Info().vPos - m_tInfo.vPos;

	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
	D3DXVec3Normalize(&m_tInfo.vLook, &m_tInfo.vLook);

	float fDot = D3DXVec3Dot(&m_tInfo.vDir, &m_tInfo.vLook);   // ���������ؼ� �ޱ��� ���߾��
	float	m_fAngle = acosf(fDot);


	if (m_tInfo.vDir.x * m_tInfo.vLook.y - m_tInfo.vDir.y *  m_tInfo.vLook.x > 0)
		m_fAngle = 2.f * D3DX_PI - m_fAngle;


	D3DXMATRIX	matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, 0.3f, 0.5f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matRotZ * matTrans;

	for (int i = 0; i < 4; ++i)
	{
		m_vPoint[i] = m_vOriginPoint[i];
		m_vPoint[i] -= {400.f, 300.f, 0.f };

		D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld); // ���Ϳ� ����� �����ִ�
	}

	m_vGunPoint = m_vOriginGunPoint;
	m_vGunPoint -= {400.f, 300.f, 0.f };

	D3DXVec3TransformCoord(&m_vGunPoint, &m_vGunPoint, &m_tInfo.matWorld);


	if (m_dwTime + 1000 < GetTickCount())
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CBullet3>::Create(float(m_vGunPoint.x), float(m_vGunPoint.y), m_fAngle));

		m_dwTime = GetTickCount();
	}

	

	Update_Rect();


	return OBJ_NOEVENT;
}

void CTower3::Late_Update(void)
{

}

void CTower3::Render(HDC hDC)
{
	/*Rectangle(hDC,
		300,
		300,
		400,
		400);*/

	MoveToEx(hDC, m_vPoint[0].x, m_vPoint[0].y, nullptr);

	for (int i = 0; i < 4; ++i)
	{
		LineTo(hDC, m_vPoint[i].x, m_vPoint[i].y);

		if (i > 0)
			continue;

		Ellipse(hDC,
			int(m_vPoint[i].x - 5.f),
			int(m_vPoint[i].y - 5.f),
			int(m_vPoint[i].x + 5.f),
			int(m_vPoint[i].y + 5.f));
	}

	LineTo(hDC, m_vPoint[0].x, m_vPoint[0].y);

	// ����
	MoveToEx(hDC, m_tInfo.vPos.x, m_tInfo.vPos.y, nullptr);

	LineTo(hDC, m_vGunPoint.x, m_vGunPoint.y);
}

void CTower3::Release(void)
{
}

