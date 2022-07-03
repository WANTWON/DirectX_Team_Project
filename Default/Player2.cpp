#include "stdafx.h"
#include "Player2.h"
#include "Bullet2.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "CollisionMgr.h"
#include "Item2.h"
#include "ShieldItem2.h"
#include "NormalItem2.h"
#include "SceneMgr.h"

CPlayer2::CPlayer2()
{
}

CPlayer2::~CPlayer2()
{
	Release();
}

void CPlayer2::Initialize(void)
{
	m_bDead = false;
	m_tInfo.vPos = { 400.f, 300.f, 0.f };
	m_tInfo.vLook = { 0.f, -1.f, 0.f };

	m_fSpeed = 5.f;
	m_iScore = 0;
	m_fAngle = 0.f;
	m_fPosinAngle = 0.f;

	m_vPoint[0] = { m_tInfo.vPos.x + 30.f, m_tInfo.vPos.y - 30.f, 0.f };
	m_vPoint[1] = { m_tInfo.vPos.x + 30.f, m_tInfo.vPos.y + 30.f, 0.f };
	m_vPoint[2] = { m_tInfo.vPos.x - 30.f, m_tInfo.vPos.y + 30.f, 0.f };
	m_vPoint[3] = { m_tInfo.vPos.x - 30.f, m_tInfo.vPos.y - 30.f, 0.f };

	for (int i = 0; i < 4; i++)
	{
		m_vOriginPoint[i] = m_vPoint[i];
	}
	m_vGunPoint = { m_tInfo.vPos.x , m_tInfo.vPos.y - 60.f, 0.f };
	m_vOriginGunPoint = m_vGunPoint;
	m_dBulletTime = GetTickCount();
	m_tInfo.vSIze.x = 60;
	m_tInfo.vSIze.y = 60;
	m_iHp = 3;
	m_bInvincible = false;

	m_bPlayerDead = false;
}

int CPlayer2::Update(void)
{

	if (m_iHp <= 0)
		m_bPlayerDead = true;


	if (m_bDead)
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);
		return 1;
	}


	Key_Input();

	Collision_Check();

	if (m_dInvincible + 2000 < GetTickCount())
		m_bInvincible = false;

	D3DXMATRIX	matScale, matRotate, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);

	D3DXMatrixRotationZ(&matRotate, m_fAngle);

	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matRotate * matTrans;

	for (int i = 0; i < 4; ++i)
	{
		m_vPoint[i] = m_vOriginPoint[i];
		m_vPoint[i] -= {400.f, 300.f, 0.f };

		D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
	}

	D3DXMATRIX matGunRotZ;

	vBDir = ::Get_Mouse() - m_tInfo.vPos;

	// 벡터의 정규화(단위 벡터)를 수행하는 함수
	D3DXVec3Normalize(&vBDir, &vBDir);

	D3DXVECTOR3 vecGunLook = { 0.f, -1.f, 0.f };

	float fDot = D3DXVec3Dot(&vBDir, &vecGunLook);

	m_fPosinAngle = acosf(fDot);

	if (vBDir.x * vecGunLook.y - vBDir.y * vecGunLook.x > 0)
		m_fPosinAngle = 2 * D3DX_PI - m_fPosinAngle;

	m_vGunPoint = m_vOriginGunPoint;
	m_vGunPoint -= {400.f, 300.f, 0.f };
	D3DXMatrixRotationZ(&matGunRotZ, m_fPosinAngle);
	matWorld2 = matScale * matGunRotZ * matTrans;

	D3DXVec3TransformCoord(&m_vGunPoint, &m_vGunPoint, &matWorld2);

	D3DXVec3TransformNormal(&vBDir, &m_tInfo.vLook, &matWorld2);

	return 0;
}

void CPlayer2::Late_Update(void)
{
}

void CPlayer2::Render(HDC hDC)
{

	if (!m_bPlayerDead)
	{
		HPEN myPen = nullptr;
		HPEN oldPen = nullptr;

		if (m_bInvincible)
		{
			myPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
			oldPen = (HPEN)SelectObject(hDC, myPen);
		}

		MoveToEx(hDC, m_vPoint[0].x, m_vPoint[0].y, nullptr);

		for (int i = 0; i < 4; ++i)
		{
			LineTo(hDC, m_vPoint[i].x, m_vPoint[i].y);

			if (i > 1)
				continue;

			Ellipse(hDC,
				m_vPoint[i].x - 5.f,
				m_vPoint[i].y - 5.f,
				m_vPoint[i].x + 5.f,
				m_vPoint[i].y + 5.f);
		}
		LineTo(hDC, m_vPoint[0].x, m_vPoint[0].y);

		MoveToEx(hDC, m_tInfo.vPos.x, m_tInfo.vPos.y, nullptr);

		LineTo(hDC, m_vGunPoint.x, m_vGunPoint.y);

		SelectObject(hDC, oldPen);
		DeleteObject(myPen);

		TCHAR		szBuff[32] = L"";
		swprintf_s(szBuff, L"Hp : %4d   Score : %4d", m_iHp, m_iScore);
		TextOut(hDC, 500, 50, szBuff, lstrlen(szBuff));
	}
	else
	{
		TCHAR		szBuff[32] = L"";
		swprintf_s(szBuff, L"최종 Score : %4d", m_iScore);
		TextOut(hDC, 350, 300, szBuff, lstrlen(szBuff));
	}

}

void CPlayer2::Release(void)
{
}

void CPlayer2::Key_Input(void)
{
	// GetKeyState()
	if (GetAsyncKeyState(VK_RIGHT))
		m_fPosinAngle += D3DXToRadian(3.f);

	if (GetAsyncKeyState(VK_LEFT))
		m_fPosinAngle -= D3DXToRadian(3.f);

	if (GetAsyncKeyState('A'))
		m_tInfo.vPos.x -= m_fSpeed;
		//m_fAngle -= D3DXToRadian(3.f);

	if (GetAsyncKeyState('D'))
		m_tInfo.vPos.x += m_fSpeed;
		//m_fAngle += D3DXToRadian(3.f);

	if (GetAsyncKeyState('Q'))
		m_fAngle -= D3DXToRadian(3.f);

	if (GetAsyncKeyState('E'))
		m_fAngle += D3DXToRadian(3.f);

	if (GetAsyncKeyState('W'))
	{
		m_tInfo.vPos.y -= m_fSpeed;
	}
	if (GetAsyncKeyState('S'))
	{
		m_tInfo.vPos.y += m_fSpeed;
	}
	if (GetAsyncKeyState(VK_RETURN))
	{
		if (m_bPlayerDead)
			m_bDead = true;
	}

	/*if (GetAsyncKeyState('W'))
	{
		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	}
	if (GetAsyncKeyState('S'))
	{
		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
		m_tInfo.vPos -= m_tInfo.vDir * m_fSpeed;
	}*/
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if (m_dBulletTime + 100 < GetTickCount())
		{
			//m_pBullet->push_back(Create_Bullet(DIR_LT));

			CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, Create_Bullet(DIR_LT));
			m_dBulletTime = GetTickCount();
		}
	}
}

CObj* CPlayer2::Create_Bullet(DIRECTION eDir)
{
	CObj*		pBullet = new CBullet2;

	pBullet->Set_Pos(m_vGunPoint.x, m_vGunPoint.y);
	dynamic_cast<CBullet2*>(pBullet)->Set_Dir(vBDir);
	dynamic_cast<CBullet2*>(pBullet)->Set_Angle(m_fPosinAngle);
	dynamic_cast<CBullet2*>(pBullet)->Set_BulletType(OBJ_PLAYER);

	pBullet->Initialize();

	return pBullet;
}

void CPlayer2::Collision_Check()
{
	list<CObj*>* Bulletlist = CObjMgr::Get_Instance()->Get_IDlist(OBJ_BULLET);
	list<CObj*>* Monsterlist = CObjMgr::Get_Instance()->Get_IDlist(OBJ_MONSTER);
	list<CObj*>* ItemList = CObjMgr::Get_Instance()->Get_IDlist(OBJ_ITEM);

	for (auto& iter = Bulletlist->begin(); iter != Bulletlist->end(); iter++)
	{
		if (CCollisionMgr::ChecK_Sphere(this, (*iter)))
		{
			OBJID bulletID = dynamic_cast<CBullet2*>(*iter)->Get_BulletType();
			if (bulletID == OBJ_MONSTER)
			{
				dynamic_cast<CBullet2*>(*iter)->Set_Dead();
				if (!m_bInvincible)
				{
					--m_iHp;
					m_bInvincible = true;
					m_dInvincible = GetTickCount();
				}
			}
		}
	}
	
	for (auto& iter = Monsterlist->begin(); iter != Monsterlist->end(); iter++)
	{
		if (CCollisionMgr::ChecK_Sphere(this, (*iter)))
		{
			if (!m_bInvincible)
			{
				--m_iHp;
				m_bInvincible = true;
				m_dInvincible = GetTickCount();
			}
		}
	}

	for (auto& iter = ItemList->begin(); iter != ItemList->end(); iter++)
	{
		int iSize = 0;
		if (CCollisionMgr::ChecK_Sphere(this, (*iter)))
		{

			for (auto& iter2 = ItemList->begin(); iter2 != ItemList->end(); iter2++)
			{
				if (dynamic_cast<CItem2*>(*iter2)->Get_ItemType() == CItem2::ITEM_SHIELD)
					iSize++;
			}

			if (dynamic_cast<CItem2*>(*iter)->Get_ItemType() == CItem2::ITEM_NORMAL)
			{
				dynamic_cast<CNormalItem2*>(*iter)->Set_Dead();

				list<CObj*>* ItemList = CObjMgr::Get_Instance()->Get_IDlist(OBJ_ITEM);
				if (iSize < 3)
				{
					CObj*	pShield = new CShieldItem2;
					pShield->Set_Pos(m_tInfo.vPos.x, m_tInfo.vPos.y - 40.f);
					pShield->Initialize();
					CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, pShield);
				}
			}
		}
	}
}