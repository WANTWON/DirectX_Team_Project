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

	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());
}

int CStage3::Update(void)
{
	return 0;
}

void CStage3::Late_Update(void)
{
}

void CStage3::Release(void)
{
}

void CStage3::Render(HDC hDC)
{
}
