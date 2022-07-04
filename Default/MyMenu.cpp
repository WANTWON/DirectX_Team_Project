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
	TCHAR szLEE[32] = L"LEE";
	TCHAR szWON[32] = L"WON";
	TCHAR szSEO[32] = L"SEO";
	TCHAR szHEO[32] = L"HEO";
	TextOut(hDC, 87, 190, szLEE, lstrlen(szLEE));
	TextOut(hDC, 186, 190, szHEO, lstrlen(szHEO));
	TextOut(hDC, 286, 190, szSEO, lstrlen(szSEO));
	TextOut(hDC, 383, 190, szWON, lstrlen(szWON));
}
