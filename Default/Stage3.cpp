#include "stdafx.h"
#include "Stage3.h"
#include "Player3.h"
#include "AbstractFactory.h"
#include "Tower3.h"
#include "ObjMgr.h"


CStage3::CStage3()
{
}


CStage3::~CStage3()
{
}

void CStage3::Initialize(void)
{


	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer3>::Create(200.f, 200.f));

	//CObjMgr::Get_Instance()->Add_Object(OBJ_TOWER, CAbstractFactory<CTower3>::Create(200.f, 200.f));

	//CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CTower3>::Create(200.f, 200.f));


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
