#include "stdafx.h"
#include "Bullet.h"


CBullet::CBullet()
{
}


CBullet::~CBullet()
{
}

void CBullet::Initialize(void)
{
	
	//m_tInfo.vPos = { 400.f, 300.f, 0.f };
	//m_tInfo.vLook = { 1.f, 0.f, 0.f };
	
	//m_fSpeed = 10.f;
	

	m_fSpeed = 10.f;


}

int CBullet::Update(void)
{
	

	return OBJ_NOEVENT;
}

void CBullet::Late_Update(void)
{
}

void CBullet::Render(HDC hDC)
{


}

void CBullet::Release(void)
{
}