#include "stdafx.h"
#include "Tower3.h"
#include "Bullet3.h"
#include "ObjMgr.h"


CTower3::CTower3()
{
}

CTower3::~CTower3()
{
	Release();
}

void CTower3::Initialize(void)
{

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

	if (m_Ttype == TOWER_HEART)
	{

	}




}

int CTower3::Update(void)
{
	//m_tInfo.vDir = m_pPlayer->Get_Info().vPos - m_tInfo.vPos; // �ڿ��ִ�(����)���Ͱ� �տ��ִ�(�÷��̾�)���͸� �ٶ󺸴� �����̳���  �÷��̾��� ��ġ���� - ������ ��ġ���� �̰��� ������ vDir �� ���⺤�ͺ����� �־�����!

	float		fLength = sqrtf(m_tInfo.vDir.x * m_tInfo.vDir.x + m_tInfo.vDir.y * m_tInfo.vDir.y); // 

	m_tInfo.vDir.x /= fLength; // ������ ����ȭ����
	m_tInfo.vDir.y /= fLength; // ������ ����ȭ����
	m_tInfo.vDir.z = 0.f;

	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;

	return OBJ_NOEVENT;
}

void CTower3::Late_Update(void)
{

}

void CTower3::Render(HDC hDC)
{
	Ellipse(hDC,
		int(m_tInfo.vPos.x - 50.f),
		int(m_tInfo.vPos.y - 50.f),
		int(m_tInfo.vPos.x + 50.f),
		int(m_tInfo.vPos.y + 50.f));
}

void CTower3::Release(void)
{
}

