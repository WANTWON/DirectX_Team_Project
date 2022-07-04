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


CStage3::CStage3() : moncreate(0)
{
	m_dwTime = GetTickCount();
	m_monTime = GetTickCount();
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
	if (CKeyMgr::Get_Instance()->Key_Down('E'))
	{
		for (int i = 0; i < 20; ++i)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster3>::Create(rand() % 801, rand() % 510));
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Down('Q'))
	{
		for (int i = 0; i < 3000; ++i)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster3>::Create(rand() % 801, rand() % 510));
		}
	}
	

	if (m_dwTime + 60 < GetTickCount())
	{
		switch (moncreate)
		{
		case 1:
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster3>::Create(rand() % 801, 0.f));


			break;
		case 2:
			//CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster3>::Create(0, -(um)));


			break;
		case 3:

			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster3>::Create(800, -600.f));

			break;
		case 4:

			//CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster3>::Create(800, -(um)));

			break;




		}
		m_dwTime = GetTickCount();
	}

	if (dynamic_cast<Maintower3*>((*CObjMgr::Get_Instance()->Get_IDlist(OBJ_MAINTOWER)).front())->Get_Score() > 500)
	{

		if (m_monTime + 20 < GetTickCount())
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
			m_monTime = GetTickCount();
		}

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
