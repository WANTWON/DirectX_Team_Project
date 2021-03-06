#include "stdafx.h"
#include "Bullet3.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "Monster3.h"
#include "Maintower3.h"


CBullet3::CBullet3() 
{
}


CBullet3::~CBullet3()
{
}

void CBullet3::Initialize(void)
{

	m_tInfo.vLook = { 0.f, -1.f, 0.f };


	m_fSpeed = 10.f;


	m_tInfo.vPos = { 400.f, 300.f, 0.f };
	m_tInfo.vLook = { 0.f, -1.f, 0.f };

	m_tInfo.vSIze = { 20.f, 20.f , 0.f };

	m_fSpeed = 10.f;

	m_vPoint[0] = { m_tInfo.vPos.x - 50.f, m_tInfo.vPos.y - 50.f, 0.f };
	m_vPoint[1] = { m_tInfo.vPos.x + 50.f, m_tInfo.vPos.y - 50.f, 0.f };
	m_vPoint[2] = { m_tInfo.vPos.x + 50.f, m_tInfo.vPos.y + 50.f, 0.f };
	m_vPoint[3] = { m_tInfo.vPos.x - 50.f, m_tInfo.vPos.y + 50.f, 0.f };

	for (int i = 0; i < 4; ++i)
		m_vOriginPoint[i] = m_vPoint[i];   // 점이니까 포문으로 하나씩 연산 다박아야하니까

										   // 포신

	//m_vGunPoint = { m_tInfo.vPos.x, m_tInfo.vPos.y - 100.f, 0.f };
	//m_vOriginGunPoint = m_vGunPoint;

}

int CBullet3::Update(void)
{

	if (m_bDead)
		return OBJ_DEAD;

	//if (m_bFront)

	
	//if (m_bFront == false)

	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld); //행렬이 곱해진 방향벡터를 구하는 함수
	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;


	D3DXMATRIX	matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, -1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matRotZ * matTrans;

	for (int i = 0; i < 4; ++i)
	{
		m_vPoint[i] = m_vOriginPoint[i];
		m_vPoint[i] -= {400.f, 300.f, 0.f };

		D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld); // 벡터와 행렬을 곱해주는
	}

	m_vGunPoint = m_vOriginGunPoint;
	m_vGunPoint -= {400.f, 300.f, 0.f };

	//D3DXVec3TransformCoord(&m_vGunPoint, &m_vGunPoint, &m_tInfo.matWorld);

		//*m_tInfo.vPos.x += m_fSpeed * cosf(m_fAngle * PI / 180.f);
	 //   m_tInfo.vPos.y -= m_fSpeed * sinf(m_fAngle * PI / 180.f);*/

	/*if (m_bFront)
		m_tInfo.vPos.x += m_fSpeed;
	else
		m_tInfo.vPos.x -= m_fSpeed;*/
	return OBJ_NOEVENT;
}


void CBullet3::Late_Update(void)
{

//	if (CCollisionMgr::Collision_Sphere(*(CObjMgr::Get_Instance()->Get_IDlist(OBJ_MONSTER)), this))
//	{
//		m_bDead = true;
////		dynamic_cast<CMonster3*>((*CObjMgr::Get_Instance()->Get_IDlist(OBJ_PLAYER)).front())->Set_Score(10);
//	}

	if (m_dwTime + 750 < GetTickCount())
	{
		m_bDead = true;

		m_dwTime = GetTickCount();
	}
		

	if (m_tInfo.vPos.x < 0 || m_tInfo.vPos.x > WINCX - 10 || m_tInfo.vPos.y < 0 || m_tInfo.vPos.y > WINCY - 10)
	{
		m_bDead = true;
	}

	
	/*if (m_tInfo.vPos.x >= WINCX || m_tInfo.vPos.x <= 0)
		m_bDead = true;
	if (m_tInfo.vPos.y >= WINCY || m_tInfo.vPos.y <= 0)
		m_bDead = true;*/
		



	/*RECT rc;
	auto& iter = CObjMgr::Get_Instance()->Get_IDlist(OBJ_MONSTER)->begin();
	for (; iter != CObjMgr::Get_Instance()->Get_IDlist(OBJ_MONSTER)->end(); ++iter)
	{
		if (IntersectRect(&rc, &m_rc, &dynamic_cast<CMonster3*>(*iter)->Get_Rect()))
		{
			m_bDead = true;
		}
			
	}*/

	if (CCollisionMgr::Collision_Sphere(*(CObjMgr::Get_Instance()->Get_IDlist(OBJ_MONSTER)), this))
	{
		m_bDead = true;
		
		
	}

	Update_Rect();
}

void CBullet3::Render(HDC hDC)
{


	Ellipse(hDC,
		int(m_tInfo.vPos.x - 10.f),
		int(m_tInfo.vPos.y - 10.f),
		int(m_tInfo.vPos.x + 10.f),
		int(m_tInfo.vPos.y + 10.f));
}

void CBullet3::Release(void)
{
}