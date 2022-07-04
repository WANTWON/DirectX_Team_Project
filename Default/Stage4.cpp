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
	int xPos = 450;
	int yPos = 300;

	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer4>::Create(100, 300));
	
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster4>::Create(xPos, yPos));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster4>::Create(xPos + 20, yPos - 10));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster4>::Create(xPos + 20, yPos + 11));

	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster4>::Create(xPos + 40, yPos - 20));
	CObj* Ball = CAbstractFactory<CMonster4>::Create(xPos + 40, yPos + 1);
	static_cast<CMonster4*>(Ball)->Set_RED_ball();
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, Ball);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster4>::Create(xPos + 40, yPos + 22));

	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster4>::Create(xPos + 60, yPos - 31));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster4>::Create(xPos + 60, yPos - 10));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster4>::Create(xPos + 60, yPos + 11));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster4>::Create(xPos + 60, yPos + 32));


	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CGoal4>::Create(50, 50));
	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CGoal4>::Create(750, 50));
	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CGoal4>::Create(50, 550));
	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CGoal4>::Create(750, 550));


}

int CStage4::Update(void)
{
	CObjMgr::Get_Instance()->Update();

	return 0;
}

void CStage4::Late_Update(void)
{
	if (static_cast<CPlayer4*>((CObjMgr::Get_Instance()->Get_Player()))->Get_Clear() && !m_bCount)
	{
		m_dwTime = GetTickCount();
		m_bClear = true;
		m_bCount = true;
	}

	if (m_bClear && m_dwTime + 2000 <GetTickCount())
	{
	//	CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);
	}

	//if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
	//{
	//	CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);
	//}

	CObjMgr::Get_Instance()->Late_Update();
}

void CStage4::Release(void)
{
	//CObjMgr::Get_Instance()->Destroy_Instance();

}

void CStage4::Render(HDC hDC)
{
	Rectangle(hDC, 0, 0, WINCX, WINCY);

	CObjMgr::Get_Instance()->Render(hDC);
}
