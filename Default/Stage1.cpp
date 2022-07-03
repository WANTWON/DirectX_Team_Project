#include "stdafx.h"
#include "Stage1.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Player1.h"
#include "Item.h"

CStage1::CStage1()
	:m_dtime(GetTickCount())
{
}


CStage1::~CStage1()
{
}

void CStage1::Initialize(void)
{
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer1>::Create(300.f, 200.f));
}

int CStage1::Update(void)
{
	if (m_dtime + 3000 < GetTickCount())
	{
		Create_Item();
		m_dtime = GetTickCount();
	}
	CObjMgr::Get_Instance()->Update();
	return 0;
}

void CStage1::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CStage1::Release(void)
{
}

void CStage1::Render(HDC hDC)
{
	CObjMgr::Get_Instance()->Render(hDC);
}

void CStage1::Create_Item()
{
	float fTemp = rand() % 780 + 11;
	float fDest = rand() % 580 + 11;
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CItem>::Create(fTemp, fDest));
}
