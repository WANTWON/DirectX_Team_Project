#include "stdafx.h"
#include "Player.h"

CPlayer::CPlayer()
{
	//원혜연 바보
}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo.vPos = { 400.f, 300.f, 0.f };
	m_tInfo.vLook = { 1.f, 0.f, 0.f };
	
	m_fSpeed = 10.f;
	
}

int CPlayer::Update(void)
{
	m_tInfo.vDir = ::Get_Mouse() - m_tInfo.vPos;
	
	/*float	fLength = sqrtf(m_tInfo.vDir.x * m_tInfo.vDir.x + m_tInfo.vDir.y * m_tInfo.vDir.y);

	m_tInfo.vDir.x /= fLength;
	m_tInfo.vDir.y /= fLength;
	m_tInfo.vDir.z = 0.f;
	
	float	fLength2 = sqrtf(m_tInfo.vLook.x * m_tInfo.vLook.x + m_tInfo.vLook.y * m_tInfo.vLook.y);

	m_tInfo.vLook.x /= fLength2;
	m_tInfo.vLook.y /= fLength2;
	m_tInfo.vLook.z = 0.f;

	float	fDot = m_tInfo.vDir.x * m_tInfo.vLook.x + m_tInfo.vDir.y * m_tInfo.vLook.y;

	float	fAngle = acosf(fDot);
			
	if (m_tInfo.vPos.y < ::Get_Mouse().y)
		fAngle = 2.f * D3DX_PI - fAngle;

	m_tInfo.vPos.x += cosf(fAngle) * m_fSpeed;
	m_tInfo.vPos.y -= sinf(fAngle) * m_fSpeed;*/


#pragma region DIRECT 함수를 이용한 과제 풀이

	// 벡터의 크기를 구해주는 함수
	// float	fLength = D3DXVec3Length(&m_tInfo.vDir);

	// 벡터의 정규화(단위 벡터)를 수행하는 함수(결과 값을 저장할 벡터, 정규화를 수행할 벡터)
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
	D3DXVec3Normalize(&m_tInfo.vLook, &m_tInfo.vLook);

	// 두 방향 벡터의 내적을 수행하는 함수
	float fDot = D3DXVec3Dot(&m_tInfo.vDir, &m_tInfo.vLook);

	float	fAngle = acosf(fDot);

	if (m_tInfo.vPos.y < ::Get_Mouse().y)
		fAngle = 2.f * D3DX_PI - fAngle;

	m_tInfo.vPos.x += cosf(fAngle) * m_fSpeed;
	m_tInfo.vPos.y -= sinf(fAngle) * m_fSpeed;


#pragma endregion DIRECT 함수를 이용한 과제 풀이



	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
}

void CPlayer::Render(HDC hDC)
{
	Rectangle(hDC, 
		int(m_tInfo.vPos.x - 50.f),
		int(m_tInfo.vPos.y - 50.f),
		int(m_tInfo.vPos.x + 50.f),
		int(m_tInfo.vPos.y + 50.f));
}

void CPlayer::Release(void)
{	
}

void CPlayer::Key_Input(void)
{
	// GetKeyState()
// 	/*if (GetAsyncKeyState(VK_RIGHT))
// 		m_tInfo.fX += m_fSpeed;
// 
// 	if (GetAsyncKeyState(VK_LEFT))
// 		m_tInfo.fX -= m_fSpeed;
// 
// 	if (GetAsyncKeyState(VK_UP))
// 		m_tInfo.fY -= m_fSpeed;
// 
// 	if (GetAsyncKeyState(VK_DOWN))
// 		m_tInfo.fY += m_fSpeed;*/
}