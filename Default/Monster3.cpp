#include "stdafx.h"
#include "Monster3.h"
#include "ObjMgr.h"


CMonster3::CMonster3()
{
}

CMonster3::~CMonster3()
{
	Release();
}

void CMonster3::Initialize(void)
{

	m_bDead = false;
	m_tInfo.vPos = { 100.f, 100.f, 0.f };
	m_fSpeed = 2.f;

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

	/*if (m_bDead)
		return OBJ_DEAD;*/

	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_MAINTOWER, this);




		

	m_tInfo.vDir = m_pTarget->Get_Info().vPos - m_tInfo.vPos; // �ڿ��ִ�(����)���Ͱ� �տ��ִ�(�÷��̾�)���͸� �ٶ󺸴� �����̳���  �÷��̾��� ��ġ���� - ������ ��ġ���� �̰��� ������ vDir �� ���⺤�ͺ����� �־�����!

	float		fLength = sqrtf(m_tInfo.vDir.x * m_tInfo.vDir.x + m_tInfo.vDir.y * m_tInfo.vDir.y); // 

	m_tInfo.vDir.x /= fLength; // ������ ����ȭ����
	m_tInfo.vDir.y /= fLength; // ������ ����ȭ����
	m_tInfo.vDir.z = 0.f;


	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;


	//m_tInfo.vPos.x += m_fSpeed;

	
	/*if (m_tInfo.vPos.x == 800 || m_tInfo.vPos.x == 0)
	{
		m_fSpeed *= -1;
	}*/

	
	

	//move();

	return OBJ_NOEVENT;
}

void CMonster3::Late_Update(void)
{
}


void CMonster3::Render(HDC hDC)
{
	/*Rectangle(hDC,
		int(m_tInfo.vPos.x - 50.f),
		int(m_tInfo.vPos.y - 50.f),
		int(m_tInfo.vPos.x + 50.f),
		int(m_tInfo.vPos.y + 50.f));*/

	Rectangle(hDC,
		int(m_tInfo.vPos.x - 10.f),
		int(m_tInfo.vPos.y - 10.f),
		int(m_tInfo.vPos.x + 10.f),
		int(m_tInfo.vPos.y + 10.f));

	/*Ellipse(hDC,
		int(300.f),
		int(400.f),
		int(100.f),
		int(100.f));*/
	
}

void CMonster3::move()
{
	//m_tInfo.vPos.x -= 1.f;
}

void CMonster3::Release(void)
{

}


