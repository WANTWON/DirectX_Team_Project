#include "stdafx.h"
#include "Stage3.h"
#include "AbstractFactory.h"
#include "Player.h"
#include "ObjMgr.h"


CStage3::CStage3()
{
}


CStage3::~CStage3()
{
}

void CStage3::Initialize(void)
{

	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(200.f, 200.f));
}

int CStage3::Update(void)
{
	CObjMgr::Get_Instance()->Update();
	return 0;
}

void CStage3::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CStage3::Release(void)
{
}

void CStage3::Render(HDC hDC)
{
	CObjMgr::Get_Instance()->Render(hDC);
}
