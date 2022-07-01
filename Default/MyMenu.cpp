#include "stdafx.h"
#include "MyMenu.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "AbstractFactory.h"
#include "MyButton.h"

CMyMenu::CMyMenu()
{
}


CMyMenu::~CMyMenu()
{
	Release();
}

void CMyMenu::Initialize(void)
{
	CObj*	pObj = CAbstractFactory<CMyButton>::Create(100.f, 200.f);
	pObj->Set_FrameKey(L"Stage1");
	CObjMgr::Get_Instance()->Add_Object(OBJ_BUTTON, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(200.f, 200.f);
	pObj->Set_FrameKey(L"Stage2");
	CObjMgr::Get_Instance()->Add_Object(OBJ_BUTTON, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(300.f, 200.f);
	pObj->Set_FrameKey(L"Stage3");
	CObjMgr::Get_Instance()->Add_Object(OBJ_BUTTON, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(400.f, 200.f);
	pObj->Set_FrameKey(L"Stage4");
	CObjMgr::Get_Instance()->Add_Object(OBJ_BUTTON, pObj);
}

int CMyMenu::Update(void)
{
	CObjMgr::Get_Instance()->Update();

	return 0;
}

void CMyMenu::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CMyMenu::Release(void)
{
	//CObjMgr::Get_Instance()->Delete_ID(OBJ_BUTTON);
}

void CMyMenu::Render(HDC hDC)
{
	Rectangle(hDC, 0, 0, WINCX, WINCY);
	CObjMgr::Get_Instance()->Render(hDC);
}
