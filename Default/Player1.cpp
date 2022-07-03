#include "stdafx.h"
#include "Player1.h"
#include "Tail.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "CollisionMgr.h"
#include "Tail.h"
#include "Item.h"
#include "SceneMgr.h"
CPlayer1::CPlayer1()
	:m_fAngle(0), m_iTailSize(0.f), m_dTime(GetTickCount()), m_bDead(false), m_iScore(0), m_dDeadTime(GetTickCount()), m_bDeadTime(false)
, m_Clear(false)
{
	ZeroMemory(&m_rc, sizeof(RECT));
}


CPlayer1::~CPlayer1()
{
}


void CPlayer1::Initialize(void)
{
	m_tInfo.vPos = { 400.f, 300.f, 0.f };
	m_tInfo.vLook = { 0.f, -1.f, 0.f };
	m_fSpeed = 10.f;

	m_vPoint[0] = { m_tInfo.vPos.x - 25.f, m_tInfo.vPos.y - 25.f, 0.f };
	m_vPoint[1] = { m_tInfo.vPos.x + 25.f, m_tInfo.vPos.y - 25.f, 0.f };
	m_vPoint[2] = { m_tInfo.vPos.x + 25.f, m_tInfo.vPos.y + 25.f, 0.f };
	m_vPoint[3] = { m_tInfo.vPos.x - 25.f, m_tInfo.vPos.y + 25.f, 0.f };

	for (int i = 0; i < 4; ++i)
		m_vOriginPoint[i] = m_vPoint[i];
}

int CPlayer1::Update(void)
{
	D3DXMATRIX	matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, 0.25f, 0.25f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matRotZ * matTrans;

	for (int i = 0; i < 4; ++i)
	{
		m_vPoint[i] = m_vOriginPoint[i];
		m_vPoint[i] -= {400.f, 300.f, 0.f };

		D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
	}
	if (m_bDead)
	{
		if (!m_bDeadTime)
		{
			m_dDeadTime = GetTickCount();
			m_bDeadTime = true;
		}
		if (m_dDeadTime + 2000 < GetTickCount())
		{
			m_Clear = true;
			m_dDeadTime = GetTickCount();
		}
		
	}

	if(!m_bDead)
		Key_Input();
	Update_Pos();

	for (int i = 0; i < 2; ++i)
	{
		RECT rc;
		auto& iter = CObjMgr::Get_Instance()->Get_IDlist(OBJ_MONSTER)->begin();
		for (; iter != CObjMgr::Get_Instance()->Get_IDlist(OBJ_MONSTER)->end(); ++iter)
		{
			if (IntersectRect(&rc, &m_rc[i], &dynamic_cast<CTail*>(*iter)->Get_Rect()))
				m_bDead = true;
		}
	}
	for (int i = 0; i < 2; ++i)
	{
		RECT rc;
		auto& iter = CObjMgr::Get_Instance()->Get_IDlist(OBJ_ITEM)->begin();
		for (; iter != CObjMgr::Get_Instance()->Get_IDlist(OBJ_ITEM)->end(); ++iter)
		{
			if (IntersectRect(&rc, &m_rc[i], &dynamic_cast<CItem*>(*iter)->Get_Rect()))
			{
				dynamic_cast<CItem*>(*iter)->Set_Dead();
				if (m_iTailSize == 0)
					CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CTail>::Create(m_tInfo.vPos.x - m_tInfo.vDir.x * 110.f, m_tInfo.vPos.y - m_tInfo.vDir.y * 110.f));
				else
					CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CTail>::Create(CObjMgr::Get_Instance()->Get_IDlist(OBJ_MONSTER)->back()->Get_Info().vPos.x, CObjMgr::Get_Instance()->Get_IDlist(OBJ_MONSTER)->back()->Get_Info().vPos.y));

				++m_iTailSize;
				m_iScore += 100;
			}
		}
	}
	return OBJ_NOEVENT;
}

void CPlayer1::Late_Update(void)
{
	Update_Rect();
	Ckeck_Rect();
}

void CPlayer1::Render(HDC hDC)
{
	TCHAR szScore[32] = L"";
	swprintf_s(szScore, L"Score :  %d", m_iScore);
	TCHAR szClear[32] = L"";
	swprintf_s(szClear, L"√÷¡æ Score :  %d", m_iScore);
	MoveToEx(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y, nullptr);

	for (int i = 0; i < 4; ++i)
	{
		LineTo(hDC, (int)m_vPoint[i].x, (int)m_vPoint[i].y);

		if (i > 1)
			continue;

		Ellipse(hDC,
			m_rc[i].left,
			m_rc[i].top,
			m_rc[i].right,
			m_rc[i].bottom);

	}
	LineTo(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y);
	if(!m_bDead)
		TextOut(hDC, 20, 20, szScore, lstrlen(szScore));
	if(m_Clear)
		TextOut(hDC, 350, 200, szClear, lstrlen(szClear));
}

void CPlayer1::Release(void)
{
}

void CPlayer1::Key_Input(void)
{
	if (GetAsyncKeyState(VK_RIGHT))
		m_fAngle += D3DXToRadian(4.f);

	if (GetAsyncKeyState(VK_LEFT))
		m_fAngle -= D3DXToRadian(4.f);

	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
	m_tInfo.vPos += m_tInfo.vDir * (m_fSpeed + m_iTailSize*0.1f);

	if (CKeyMgr::Get_Instance()->Key_Down('1'))
	{
		if(m_iTailSize == 0)
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CTail>::Create(m_tInfo.vPos.x - m_tInfo.vDir.x * 110.f, m_tInfo.vPos.y - m_tInfo.vDir.y * 110.f));
		else
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CTail>::Create(CObjMgr::Get_Instance()->Get_IDlist(OBJ_MONSTER)->back()->Get_Info().vPos.x, CObjMgr::Get_Instance()->Get_IDlist(OBJ_MONSTER)->back()->Get_Info().vPos.y));
		
		++m_iTailSize;
	}
}

void CPlayer1::Update_Pos()
{

		if (m_dTime + 70 - (int)(m_iTailSize * 0.33f)< GetTickCount())
		{
			CObjMgr::Get_Instance()->Get_IDlist(OBJ_MONSTER)->push_front(CAbstractFactory<CTail>::Create(m_tInfo.vPos.x - m_tInfo.vDir.x*50.f, m_tInfo.vPos.y - m_tInfo.vDir.y*50.f));
			Safe_Delete(CObjMgr::Get_Instance()->Get_IDlist(OBJ_MONSTER)->back());
			CObjMgr::Get_Instance()->Get_IDlist(OBJ_MONSTER)->pop_back();
			m_dTime = GetTickCount();
		}

}

void CPlayer1::Ckeck_Rect()
{
	for (int i = 0; i < 2; ++i)
	{
		if (m_vPoint[i].x >= WINCX || m_vPoint[i].x <= 0)
			m_bDead = true;
		if(m_vPoint[i].y >= WINCY || m_vPoint[i].y <= 0)
			m_bDead = true;
	}
}

void CPlayer1::Update_Rect()
{
	for (int i = 0; i < 2; ++i)
	{
		m_rc[i].left = int(m_vPoint[i].x - 2.f);
		m_rc[i].top = int(m_vPoint[i].y - 2.f);
		m_rc[i].right = int(m_vPoint[i].x + 2.f);
		m_rc[i].bottom = int(m_vPoint[i].y + 2.f);
	}
}
