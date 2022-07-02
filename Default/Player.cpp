#include "stdafx.h"
#include "Player.h"

CPlayer::CPlayer()
{
	//������ �ٺ�
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


#pragma region DIRECT �Լ��� �̿��� ���� Ǯ��

	// ������ ũ�⸦ �����ִ� �Լ�
	// float	fLength = D3DXVec3Length(&m_tInfo.vDir);

	// ������ ����ȭ(���� ����)�� �����ϴ� �Լ�(��� ���� ������ ����, ����ȭ�� ������ ����)
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
	D3DXVec3Normalize(&m_tInfo.vLook, &m_tInfo.vLook);

	// �� ���� ������ ������ �����ϴ� �Լ�
	float fDot = D3DXVec3Dot(&m_tInfo.vDir, &m_tInfo.vLook);

	float	fAngle = acosf(fDot);

	if (m_tInfo.vPos.y < ::Get_Mouse().y)
		fAngle = 2.f * D3DX_PI - fAngle;

	m_tInfo.vPos.x += cosf(fAngle) * m_fSpeed;
	m_tInfo.vPos.y -= sinf(fAngle) * m_fSpeed;


#pragma endregion DIRECT �Լ��� �̿��� ���� Ǯ��



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