#include "stdafx.h"
#include "Stage1.h"
#include "stdafx.h"
#include "Stage3.h"
#include "AbstractFactory.h"
#include "Player.h"
#include "ObjMgr.h"




CStage1::CStage1()
{
}


CStage1::~CStage1()
{
}

void CStage1::Initialize(void)
{
	//CObjMgr::Get_Instance()->CLear_Obj();

	
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());

	CObjMgr::Get_Instance()->Get_Player()->Set_Pos(300, 300);
}

int CStage1::Update(void)
{
	return 0;
}

void CStage1::Late_Update(void)
{
}

void CStage1::Release(void)
{
}

void CStage1::Render(HDC hDC)
{
	Rectangle(hDC, 0, 0, WINCX, WINCY);
}
