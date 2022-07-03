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
		m_vOriginPoint[i] = m_vPoint[i];   // ���̴ϱ� �������� �ϳ��� ���� �ٹھƾ��ϴϱ�

										   // ����

	m_vGunPoint = { m_tInfo.vPos.x, m_tInfo.vPos.y - 100.f, 0.f };
	m_vOriginGunPoint = m_vGunPoint;
}

int CPlayer3::Update(void)
{
#pragma region ���� 1
	

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

#pragma endregion ���� 1

#pragma region DIRECT �Լ��� �̿��� ���� Ǯ��

	// ������ ũ�⸦ �����ִ� �Լ�
	// float	fLength = D3DXVec3Length(&m_tInfo.vDir);

	// ������ ����ȭ(���� ����)�� �����ϴ� �Լ�(��� ���� ������ ����, ����ȭ�� ������ ����)
	/*D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
	D3DXVec3Normalize(&m_tInfo.vLook, &m_tInfo.vLook);

	// �� ���� ������ ������ �����ϴ� �Լ�
	float fDot = D3DXVec3Dot(&m_tInfo.vDir, &m_tInfo.vLook);

	// �� ���� ������ ������ �����ϴ� �Լ�(��� ���� ������ ����, ������ ������ ���� 1, ������ ������ ���� 2)
	// ���� ���� : 2, 3������ ������ ���� ��� ������ ������ �ٲ��.

	//D3DXVECTOR3	vAxis;
	//D3DXVec3Cross(&vAxis, &m_tInfo.vDir, &m_tInfo.vLook);

	float	fAngle = acosf(fDot);

	if (m_tInfo.vPos.y < ::Get_Mouse().y)
	fAngle = 2.f * D3DX_PI - fAngle;

	m_tInfo.vPos.x += cosf(fAngle) * m_fSpeed;
	m_tInfo.vPos.y -= sinf(fAngle) * m_fSpeed;*/

	


#pragma endregion DIRECT �Լ��� �̿��� ���� Ǯ��

#pragma region ��� �Լ�

	// D3DXMATRIX	matTemp;
	// �׵� ����� ������ִ� �Լ�(�׵� ����� ������� ���� ����� �ּ�)
	// D3DXMatrixIdentity(&matTemp);

	// ũ�� ����� ������ִ� �Լ�(��� ���, x����, y����, z����)
	// D3DXMatrixScaling(&matTemp, 1.f, 1.f, 1.f);

	// ȸ�� ����� ������ִ� �Լ�
	//D3DXMatrixRotationX(&matTemp, D3DXToRadian(fAngle));
	//D3DXMatrixRotationY(&matTemp, D3DXToRadian(fAngle));
	//D3DXMatrixRotationZ(&matTemp, D3DXToRadian(fAngle));

	// �̵� ����� ������ִ� �Լ�(��� ���, x��ǥ, y��ǥ, z��ǥ)
	// D3DXMatrixTranslation(&matTemp, x, y, z);

	// �� ����� ������ִ� �Լ�(��� ����� �ּ�, null, ���� ����� �ּ�)
	// D3DXMatrixInverse(&matTemp, NULL, &matTemp);

	//D3DXMATRIX	matWorld, matScale, matRotZ, matTrans;

	//matWorld = matScale * matRotZ * matTrans;


#pragma endregion ��� �Լ�

#pragma region ���͸� �̿��� ��


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


#pragma endregion ���͸� �̿��� ��

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

		D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld); // ���Ϳ� ����� �����ִ�
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

	// ����
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

#pragma region ���͸� ����� ��

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

#pragma endregion ���͸� ����� ��

	if (GetAsyncKeyState(VK_UP))
	{
		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld); //����� ������ ���⺤�͸� ���ϴ� �Լ�
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

