#include "stdafx.h"
#include "Monster3.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"
#include "Maintower3.h"


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
	m_fSpeed = 2.5f;
	m_tInfo.vSIze = { 20.f, 20.f , 0.f };
	//m_tInfo.vPos = { 400.f, 300.f, 0.f };

	//m_vPoint[0] = { m_tInfo.vPos.x - 50.f, m_tInfo.vPos.y - 50.f, 0.f };
	//m_vPoint[1] = { m_tInfo.vPos.x + 50.f, m_tInfo.vPos.y - 50.f, 0.f };
	//m_vPoint[2] = { m_tInfo.vPos.x + 50.f, m_tInfo.vPos.y + 50.f, 0.f };
	//m_vPoint[3] = { m_tInfo.vPos.x - 50.f, m_tInfo.vPos.y + 50.f, 0.f };

	//for (int i = 0; i < 4; ++i)
	//	m_vOriginPoint[i] = m_vPoint[i];   // 점이니까 포문으로 하나씩 연산 다박아야하니까

	//									   // 포신

	//m_vGunPoint = { m_tInfo.vPos.x, m_tInfo.vPos.y - 100.f, 0.f };
	//m_vOriginGunPoint = m_vGunPoint;

}

int CMonster3::Update(void)
{

	if (m_bDead)
		return OBJ_DEAD;

	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_MAINTOWER, this);


	//m_pTaarget = CObjMgr::Get_Instance()->Get_Target(OBJ_MAINTOWER, this);

		

	m_tInfo.vDir = m_pTarget->Get_Info().vPos - m_tInfo.vPos; // 뒤에있는(몬스터)벡터가 앞에있는(플레이어)벡터를 바라보는 방향이나옴  플레이어의 위치백터 - 몬스터의 위치백터 이값을 몬스터의 vDir 즉 방향벡터변수에 넣어주자!

	float		fLength = sqrtf(m_tInfo.vDir.x * m_tInfo.vDir.x + m_tInfo.vDir.y * m_tInfo.vDir.y); // 

	m_tInfo.vDir.x /= fLength; // 백터의 정규화과정
	m_tInfo.vDir.y /= fLength; // 벡터의 정규화과정
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

	if (CCollisionMgr::Collision_Sphere(*(CObjMgr::Get_Instance()->Get_IDlist(OBJ_BULLET)), this))
	{

		//dynamic_cast<Maintower3*>((*CObjMgr::Get_Instance()->Get_IDlist(OBJ_PLAYER)).front())->
		dynamic_cast<Maintower3*>((*CObjMgr::Get_Instance()->Get_IDlist(OBJ_MAINTOWER)).front())->set_Money();
		dynamic_cast<Maintower3*>((*CObjMgr::Get_Instance()->Get_IDlist(OBJ_MAINTOWER)).front())->Set_Score();

		//	dynamic_cast<CMonster3*>((*CObjMgr::Get_Instance()->Get_IDlist(OBJ_PLAYER)).front())->Set_Score(10);
		m_bDead = true;
		
	}

	if (CCollisionMgr::Collision_Sphere(*(CObjMgr::Get_Instance()->Get_IDlist(OBJ_MAINTOWER)), this))
	{
		m_bDead = true;
		
	}
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


