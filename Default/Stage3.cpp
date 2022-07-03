#include "stdafx.h"
#include "Stage3.h"
#include "Player3.h"
#include "AbstractFactory.h"
#include "Tower3.h"
#include "ObjMgr.h"
#include "Monster3.h"


CStage3::CStage3()
{
}


CStage3::~CStage3()
{
}

void CStage3::Initialize(void)
{


	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer3>::Create(200.f, 200.f));

	CObjMgr::Get_Instance()->Add_Object(OBJ_TOWER, CAbstractFactory<CTower3>::Create(300.f, 300.f));

	//CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster3>::Create(300.f, 300.f));


	


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



void CStage3::Render(HDC hDC)
{

	Rectangle(hDC, 0, 0, WINCX, WINCY);

	CObjMgr::Get_Instance()->Render(hDC);
}



void CStage3::Release(void)
{

}
