#include "stdafx.h"
#include "Player1.h"
#include "Tail.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
CPlayer1::CPlayer1()
	:m_fAngle(0), m_iTailSize(0), m_dTime(GetTickCount())
{
}


CPlayer1::~CPlayer1()
{
}


void CPlayer1::Initialize(void)
{
	m_tInfo.vPos = { 400.f, 300.f, 0.f };
	m_tInfo.vLook = { 0.f, -1.f, 0.f };
	m_fSpeed = 15.f;

	m_vPoint[0] = { m_tInfo.vPos.x - 50.f, m_tInfo.vPos.y - 50.f, 0.f };
	m_vPoint[1] = { m_tInfo.vPos.x + 50.f, m_tInfo.vPos.y - 50.f, 0.f };
	m_vPoint[2] = { m_tInfo.vPos.x + 50.f, m_tInfo.vPos.y + 50.f, 0.f };
	m_vPoint[3] = { m_tInfo.vPos.x - 50.f, m_tInfo.vPos.y + 50.f, 0.f };

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

	Key_Input();
	Update_Pos();
	return OBJ_NOEVENT;
}

void CPlayer1::Late_Update(void)
{
}

void CPlayer1::Render(HDC hDC)
{
	MoveToEx(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y, nullptr);

	for (int i = 0; i < 4; ++i)
	{
		LineTo(hDC, (int)m_vPoint[i].x, (int)m_vPoint[i].y);

		if (i > 1)
			continue;

		Ellipse(hDC,
			int(m_vPoint[i].x - 5.f),
			int(m_vPoint[i].y - 5.f),
			int(m_vPoint[i].x + 5.f),
			int(m_vPoint[i].y + 5.f));
	}

	LineTo(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y);
}

void CPlayer1::Release(void)
{
}

void CPlayer1::Key_Input(void)
{
	if (GetAsyncKeyState(VK_RIGHT))
		m_fAngle += D3DXToRadian(3.f);

	if (GetAsyncKeyState(VK_LEFT))
		m_fAngle -= D3DXToRadian(3.f);

	if (GetAsyncKeyState(VK_UP))
	{
		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
		m_tInfo.vPos -= m_tInfo.vDir * m_fSpeed;
	}
	if (CKeyMgr::Get_Instance()->Key_Down('1'))
	{
		if(m_iTailSize == 0)
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CTail>::Create(m_tInfo.vPos.x - m_tInfo.vDir.x * 110.f, m_tInfo.vPos.y - m_tInfo.vDir.y * 110.f));
		else
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CTail>::Create(CObjMgr::Get_Instance()->Get_IDlist(OBJ_MONSTER)->back()->Get_Info().vPos.x - m_tInfo.vDir.x * 110.f, CObjMgr::Get_Instance()->Get_IDlist(OBJ_MONSTER)->back()->Get_Info().vPos.y - m_tInfo.vDir.y * 110.f));
			
		++m_iTailSize;
	}
}

void CPlayer1::Update_Pos()
{
	
	m_pvPos.push_front(&m_tInfo.vPos);

	if (CObjMgr::Get_Instance()->Get_IDlist(OBJ_MONSTER)->size() < m_pvPos.size())
	{
		for (; CObjMgr::Get_Instance()->Get_IDlist(OBJ_MONSTER)->size() == m_pvPos.size();)
			m_pvPos.pop_back();
	}
	
	auto& iterMonster = CObjMgr::Get_Instance()->Get_IDlist(OBJ_MONSTER)->begin();
	auto& iterPos = m_pvPos.begin();
	for (; iterMonster != CObjMgr::Get_Instance()->Get_IDlist(OBJ_MONSTER)->end(); ++iterMonster, ++iterPos)
	{
		(*iterMonster)->Set_Pos((*iterPos)->x - m_tInfo.vDir.x * 110.f, (*iterPos)->y - m_tInfo.vDir.y * 110.f);
	}
	//if (m_iTailSize != 0)
	//{
	//	auto& iterMonster = CObjMgr::Get_Instance()->Get_IDlist(OBJ_MONSTER)->begin();
	//	auto& iterMonsterPos = CObjMgr::Get_Instance()->Get_IDlist(OBJ_MONSTER)->begin();
	//	(*iterMonster)->Set_Pos(m_tInfo.vPos.x - m_tInfo.vDir.x * 110.f, m_tInfo.vPos.y - m_tInfo.vDir.y * 110.f);
	//	++iterMonsterPos;
	//	for (; iterMonsterPos != CObjMgr::Get_Instance()->Get_IDlist(OBJ_MONSTER)->end(); ++iterMonster, ++iterMonsterPos)
	//	{
	//		(*iterMonster)->Set_Pos((*iterMonsterPos)->Get_Info().vPos.x - m_tInfo.vDir.x * 110.f, (*iterMonsterPos)->Get_Info().vPos.y - m_tInfo.vDir.y * 110.f);
	//	}
	//	iterMonster = CObjMgr::Get_Instance()->Get_IDlist(OBJ_MONSTER)->begin();
	//	iterMonsterPos = CObjMgr::Get_Instance()->Get_IDlist(OBJ_MONSTER)->begin();
	//	(*iterMonster)->Set_Pos(m_tInfo.vPos.x - m_tInfo.vDir.x * 110.f, m_tInfo.vPos.y - m_tInfo.vDir.y * 110.f);
	//}
}
