#include "stdafx.h"
#include "Stage4.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "AbstractFactory.h"
#include "Player4.h"
#include "Monster4.h"
#include "Goal4.h"

CStage4::CStage4()
{
}


CStage4::~CStage4()
{
	Release();
}

void CStage4::Initialize(void)
{
	
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer4>::Create(400, 500));
	
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster4>::Create(400, 250 + 2));

	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster4>::Create(415, 225 +1));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster4>::Create(390 -1, 225 +1));

	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster4>::Create(400, 200));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster4>::Create(425 +1, 200));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster4>::Create(375 -1, 200));

	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CGoal4>::Create(50, 100));
	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CGoal4>::Create(750, 100));


}

int CStage4::Update(void)
{
	CObjMgr::Get_Instance()->Update();

	return 0;
}

void CStage4::Late_Update(void)
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);
	}

	CObjMgr::Get_Instance()->Late_Update();
}

void CStage4::Release(void)
{
	CObjMgr::Get_Instance()->Destroy_Instance();

}

void CStage4::Render(HDC hDC)
{
	Rectangle(hDC, 0, 0, WINCX, WINCY);

	CObjMgr::Get_Instance()->Render(hDC);
}
