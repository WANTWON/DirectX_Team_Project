#include "stdafx.h"
#include "Mouse.h"
#include "Tower3.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "KeyMgr.h"

CMouse::CMouse()
{
}


CMouse::~CMouse()
{
	Release();
}

void CMouse::Initialize(void)
{

	

}

int CMouse::Update(void)
{
	POINT		Pt{};

	// ���� ���콺 Ŀ���� ��ġ ���� ������ �Լ�
	GetCursorPos(&Pt);

	// ����� ������ ��ǥ�� �츮�� ������ â ��ǥ�� ��ȯ�ϴ� �Լ�
	ScreenToClient(g_hWnd, &Pt);

	m_tInfo.vPos.x = (float)Pt.x;
	m_tInfo.vPos.y = (float)Pt.y;

	Update_Rect();

	ShowCursor(false);	// ���콺 Ŀ�� ����� �����ϴ� �Լ�


	if (CKeyMgr::Get_Instance()->Key_Down('D'))
		CObjMgr::Get_Instance()->Add_Object(OBJ_TOWER, CAbstractFactory<CTower3>::Create((float)Pt.x, (float)Pt.y));

	return OBJ_NOEVENT;
}

void CMouse::Late_Update(void)
{

}

void CMouse::Render(HDC hDC)
{
	

}

void CMouse::Release(void)
{

}
