#include "stdafx.h"
#include "Monster3.h"



CMonster3::CMonster3()
{
}

CMonster3::~CMonster3()
{
	Release();
}

void CMonster3::Initialize(void)
{
	m_tInfo.vPos = { 100.f, 100.f, 0.f };
	m_fSpeed = 5.f;

	//m_vPoint[0] = { m_tInfo.vPos.x - 50.f, m_tInfo.vPos.y - 50.f, 0.f };
	//m_vPoint[1] = { m_tInfo.vPos.x + 50.f, m_tInfo.vPos.y - 50.f, 0.f };
	//m_vPoint[2] = { m_tInfo.vPos.x + 50.f, m_tInfo.vPos.y + 50.f, 0.f };
	//m_vPoint[3] = { m_tInfo.vPos.x - 50.f, m_tInfo.vPos.y + 50.f, 0.f };

	//for (int i = 0; i < 4; ++i)
	//	m_vOriginPoint[i] = m_vPoint[i];   // ���̴ϱ� �������� �ϳ��� ���� �ٹھƾ��ϴϱ�

	//									   // ����

	//m_vGunPoint = { m_tInfo.vPos.x, m_tInfo.vPos.y - 100.f, 0.f };
	//m_vOriginGunPoint = m_vGunPoint;

}

int CMonster3::Update(void)
{
	m_tInfo.vDir = m_pPlayer->Get_Info().vPos - m_tInfo.vPos; // �ڿ��ִ�(����)���Ͱ� �տ��ִ�(�÷��̾�)���͸� �ٶ󺸴� �����̳���  �÷��̾��� ��ġ���� - ������ ��ġ���� �̰��� ������ vDir �� ���⺤�ͺ����� �־�����!

	float		fLength = sqrtf(m_tInfo.vDir.x * m_tInfo.vDir.x + m_tInfo.vDir.y * m_tInfo.vDir.y); // 

	m_tInfo.vDir.x /= fLength; // ������ ����ȭ����
	m_tInfo.vDir.y /= fLength; // ������ ����ȭ����
	m_tInfo.vDir.z = 0.f;

	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;

	return OBJ_NOEVENT;
}

void CMonster3::Late_Update(void)
{
}


void CMonster3::Render(HDC hDC)
{
	Ellipse(hDC,
		int(m_tInfo.vPos.x - 50.f),
		int(m_tInfo.vPos.y - 50.f),
		int(m_tInfo.vPos.x + 50.f),
		int(m_tInfo.vPos.y + 50.f));

	/*Ellipse(hDC,
		int(300.f),
		int(400.f),
		int(100.f),
		int(100.f));*/

}

void CMonster3::Release(void)
{

}