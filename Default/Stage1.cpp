#include "stdafx.h"
#include "Stage1.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Player.h"

CStage1::CStage1()
{
}


CStage1::~CStage1()
{
}

void CStage1::Initialize(void)
{
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(300.f, 200.f));
}

int CStage1::Update(void)
{
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
