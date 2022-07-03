#include "stdafx.h"
#include "Player3.h"
#include "AbstractFactory.h"
#include "Bullet3.h"
#include "ObjMgr.h"
#include "KeyMgr.h"


CPlayer3::CPlayer3()// :m_fAngle(0.f)
{
}


CPlayer3::~CPlayer3()
{
}

void CPlayer3::Initialize(void)
{
	m_tInfo.vPos = { 400.f, 300.f, 0.f };
	m_tInfo.vLook = { 0.f, -1.f, 0.f };

	m_fSpeed = 10.f;

	m_vPoint[0] = { m_tInfo.vPos.x - 50.f, m_tInfo.vPos.y - 50.f, 0.f };
	m_vPoint[1] = { m_tInfo.vPos.x + 50.f, m_tInfo.vPos.y - 50.f, 0.f };
	m_vPoint[2] = { m_tInfo.vPos.x + 50.f, m_tInfo.vPos.y + 50.f, 0.f };
	m_vPoint[3] = { m_tInfo.vPos.x - 50.f, m_tInfo.vPos.y + 50.f, 0.f };

	for (int i = 0; i < 4; ++i)
		m_vOriginPoint[i] = m_vPoint[i];   // 점이니까 포문으로 하나씩 연산 다박아야하니까

										   // 포신

	m_vGunPoint = { m_tInfo.vPos.x, m_tInfo.vPos.y - 100.f, 0.f };
	m_vOriginGunPoint = m_vGunPoint;
}

int CPlayer3::Update(void)
{
#pragma region 복습 1
	

	//m_tInfo.vDir = ::Get_Mouse() - m_tInfo.vPos;

	/*float	fLength = sqrtf(m_tInfo.vDir.x * m_tInfo.vDir.x + m_tInfo.vDir.y * m_tInfo.vDir.y);


	float fDot = D3DXVec3Dot(&m_tInfo.vDir, &m_tInfo.vLook);
    float	fAngle = acosf(fDot);

	m_tInfo.vDir.x /= fLength;
	m_tInfo.vDir.y /= fLength;
	m_tInfo.vDir.z = 0.f;

	float	fLength2 = sqrtf(m_tInfo.vLook.x * m_tInfo.vLook.x + m_tInfo.vLook.y * m_tInfo.vLook.y);

	m_tInfo.vLook.x /= fLength2;
	m_tInfo.vLook.y /= fLength2;
	m_tInfo.vLook.z = 0.f;

	
	float	fDot = m_tInfo.vDir.x * m_tInfo.vLook.x + m_tInfo.vDir.y * m_tInfo.vLook.y;

	

	if (m_tInfo.vPos.y < ::Get_Mouse().y)
	fAngle = 2.f * D3DX_PI - fAngle;

	m_tInfo.vPos.x += cosf(fAngle) * m_fSpeed;
	m_tInfo.vPos.y -= sinf(fAngle) * m_fSpeed;*/

#pragma endregion 복습 1

#pragma region DIRECT 함수를 이용한 과제 풀이

	// 벡터의 크기를 구해주는 함수
	// float	fLength = D3DXVec3Length(&m_tInfo.vDir);

	// 벡터의 정규화(단위 벡터)를 수행하는 함수(결과 값을 저장할 벡터, 정규화를 수행할 벡터)
	/*D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
	D3DXVec3Normalize(&m_tInfo.vLook, &m_tInfo.vLook);

	// 두 방향 벡터의 내적을 수행하는 함수
	float fDot = D3DXVec3Dot(&m_tInfo.vDir, &m_tInfo.vLook);

	// 두 방향 벡터의 외적을 수행하는 함수(결과 값을 저장할 벡터, 외적을 수행할 벡터 1, 외적을 수행할 벡터 2)
	// 주의 사항 : 2, 3인자의 순서에 따라 결과 벡터의 방향이 바뀐다.

	//D3DXVECTOR3	vAxis;
	//D3DXVec3Cross(&vAxis, &m_tInfo.vDir, &m_tInfo.vLook);

	float	fAngle = acosf(fDot);

	if (m_tInfo.vPos.y < ::Get_Mouse().y)
	fAngle = 2.f * D3DX_PI - fAngle;

	m_tInfo.vPos.x += cosf(fAngle) * m_fSpeed;
	m_tInfo.vPos.y -= sinf(fAngle) * m_fSpeed;*/

	


#pragma endregion DIRECT 함수를 이용한 과제 풀이

#pragma region 행렬 함수

	// D3DXMATRIX	matTemp;
	// 항등 행렬을 만들어주는 함수(항등 행렬의 결과값을 담을 행렬의 주소)
	// D3DXMatrixIdentity(&matTemp);

	// 크기 행렬을 만들어주는 함수(결과 행렬, x배율, y배율, z배율)
	// D3DXMatrixScaling(&matTemp, 1.f, 1.f, 1.f);

	// 회전 행렬을 만들어주는 함수
	//D3DXMatrixRotationX(&matTemp, D3DXToRadian(fAngle));
	//D3DXMatrixRotationY(&matTemp, D3DXToRadian(fAngle));
	//D3DXMatrixRotationZ(&matTemp, D3DXToRadian(fAngle));

	// 이동 행렬을 만들어주는 함수(결과 행렬, x좌표, y좌표, z좌표)
	// D3DXMatrixTranslation(&matTemp, x, y, z);

	// 역 행렬을 만들어주는 함수(결과 행렬의 주소, null, 원본 행렬의 주소)
	// D3DXMatrixInverse(&matTemp, NULL, &matTemp);

	//D3DXMATRIX	matWorld, matScale, matRotZ, matTrans;

	//matWorld = matScale * matRotZ * matTrans;


#pragma endregion 행렬 함수

#pragma region 벡터만 이용한 예


	/*for (int i = 0; i < 4; ++i)
	{
	D3DXVECTOR3		vTemp = m_vOriginPoint[i];

	vTemp -= {400.f, 300.f, 0.f };

	m_vPoint[i].x = vTemp.x * cosf(m_fAngle) - vTemp.y * sinf(m_fAngle);
	m_vPoint[i].y = vTemp.x * sinf(m_fAngle) + vTemp.y * cosf(m_fAngle);

	m_vPoint[i] += m_tInfo.vPos;
	}

	D3DXVECTOR3	vTemp = m_vOriginGunPoint;

	vTemp -= {400.f, 300.f, 0.f };

	m_vGunPoint.x = vTemp.x * cosf(m_fAngle) - vTemp.y * sinf(m_fAngle);
	m_vGunPoint.y = vTemp.x * sinf(m_fAngle) + vTemp.y * cosf(m_fAngle);

	m_vGunPoint += m_tInfo.vPos;*/


#pragma endregion 벡터만 이용한 예

	Key_Input();

	// X = x * cosf - y * sinf
	// Y = x * sinf + y * cosf

	D3DXMATRIX	matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, 0.3f, 0.3f, 1.f);
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

	D3DXVec3TransformCoord(&m_vGunPoint, &m_vGunPoint, &m_tInfo.matWorld);


	return OBJ_NOEVENT;
}

void CPlayer3::Late_Update(void)
{
}

void CPlayer3::Render(HDC hDC)
{
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

	// 포신
	MoveToEx(hDC, m_tInfo.vPos.x, m_tInfo.vPos.y, nullptr);

	LineTo(hDC, m_vGunPoint.x, m_vGunPoint.y);
}


void CPlayer3::Key_Input(void)
{

	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET,CAbstractFactory<CBullet3>::Create(float(m_vGunPoint.x), float(m_vGunPoint.y), m_fAngle));
	}

	// GetKeyState()
	if (GetAsyncKeyState(VK_RIGHT))

		m_fAngle += D3DXToRadian(3.f);

	if (GetAsyncKeyState(VK_LEFT))
		m_fAngle -= D3DXToRadian(3.f);

#pragma region 벡터만 사용한 예

	/*if (GetAsyncKeyState(VK_UP))
	{
	m_tInfo.vDir.x = m_tInfo.vLook.x * cosf(m_fAngle) - m_tInfo.vLook.y * sinf(m_fAngle);
	m_tInfo.vDir.y = m_tInfo.vLook.x * sinf(m_fAngle) + m_tInfo.vLook.y * cosf(m_fAngle);

	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
	m_tInfo.vDir.x = m_tInfo.vLook.x * cosf(m_fAngle) - m_tInfo.vLook.y * sinf(m_fAngle);
	m_tInfo.vDir.y = m_tInfo.vLook.x * sinf(m_fAngle) + m_tInfo.vLook.y * cosf(m_fAngle);

	m_tInfo.vPos -= m_tInfo.vDir * m_fSpeed;
	}*/

#pragma endregion 벡터만 사용한 예

	if (GetAsyncKeyState(VK_UP))
	{
		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld); //행렬이 곱해진 방향벡터를 구하는 함수
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
		m_tInfo.vPos -= m_tInfo.vDir * m_fSpeed;


	}

}

void CPlayer3::Release(void)
{
}

