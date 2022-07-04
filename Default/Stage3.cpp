#include "stdafx.h"
#include "Stage3.h"
#include "Player3.h"
#include "AbstractFactory.h"
#include "Tower3.h"
#include "ObjMgr.h"
#include "Monster3.h"
#include "Maintower3.h"
#include "Obj.h"
#include "KeyMgr.h"
#include "Mouse.h"


CStage3::CStage3(): moncreate(0)
{
	m_dwTime = GetTickCount();
}


CStage3::~CStage3()
{
}

void CStage3::Initialize(void)
{
	CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CMouse>::Create());

	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster3>::Create(100.f, 100.f));

	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer3>::Create(200.f, 200.f));

	CObjMgr::Get_Instance()->Add_Object(OBJ_MAINTOWER, CAbstractFactory<Maintower3>::Create(400.f, 510.f));

	CObjMgr::Get_Instance()->Add_Object(OBJ_TOWER, CAbstractFactory<CTower3>::Create(200.f, 100.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_TOWER, CAbstractFactory<CTower3>::Create(600.f, 200.f));
	
	int um = rand() % 600 + 1;
	


}

int CStage3::Update(void)
{

	moncreate = rand() % 4 + 1;

	

	if (m_dwTime + 20 < GetTickCount())
	{
		switch (moncreate)
		{
		case 1:
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster3>::Create(rand() % 801, 0.f));


			break;
		case 2:
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster3>::Create(0, -(um)));


			break;
		case 3:

			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster3>::Create(800, -600.f));

			break;
		case 4:

			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster3>::Create(800, -(um)));

			break;

			


		}
		m_dwTime = GetTickCount();
	}

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
