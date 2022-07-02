#include "stdafx.h"
#include "Stage2.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Player2.h"
#include "Monster2.h"
#include "PosinMonster2.h"

CStage2::CStage2()
{
}


CStage2::~CStage2()
{
}

void CStage2::Initialize(void)
{
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer2>::Create(100.f, 300.f));

	CObj*		pMonster = new CPosinMonster2;
	pMonster->Set_Pos(900.f, 200.f);
	dynamic_cast<CPosinMonster2*>(pMonster)->Set_Player(CObjMgr::Get_Instance()->Get_Player());
	pMonster->Initialize();

	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, pMonster);
}

int CStage2::Update(void)
{
	CObjMgr::Get_Instance()->Update();
	return 0;
}

void CStage2::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CStage2::Release(void)
{
}

void CStage2::Render(HDC hDC)
{
	CObjMgr::Get_Instance()->Render(hDC);
}
