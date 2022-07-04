#include "stdafx.h"
#include "Mouse.h"
#include "Tower3.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "Maintower3.h"
#include "BOSSM.h"

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

	// 현재 마우스 커서의 위치 값을 얻어오는 함수
	GetCursorPos(&Pt);

	// 모니터 상태의 좌표를 우리가 생성한 창 좌표로 변환하는 함수
	ScreenToClient(g_hWnd, &Pt);

	m_tInfo.vPos.x = (float)Pt.x;
	m_tInfo.vPos.y = (float)Pt.y;

	Update_Rect();

	ShowCursor(false);	// 마우스 커서 출력을 제어하는 함수
	if (CKeyMgr::Get_Instance()->Key_Down('B'))
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<BOSSM>::Create((float)Pt.x, (float)Pt.y));
	}

	if (CKeyMgr::Get_Instance()->Key_Down('D') && dynamic_cast<Maintower3*>((*CObjMgr::Get_Instance()->Get_IDlist(OBJ_MAINTOWER)).front())->get_Money() >= 50)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_TOWER, CAbstractFactory<CTower3>::Create((float)Pt.x, (float)Pt.y));
		dynamic_cast<Maintower3*>((*CObjMgr::Get_Instance()->Get_IDlist(OBJ_MAINTOWER)).front())->minus_Money();
	}
		

	return OBJ_NOEVENT;
}

void CMouse::Late_Update(void)
{

}

void CMouse::Render(HDC hDC)
{
	Ellipse(hDC,
		int(m_tInfo.vPos.x - 20.f),
		int(m_tInfo.vPos.y - 20.f),
		int(m_tInfo.vPos.x + 20.f),
		int(m_tInfo.vPos.y + 20.f));

}

void CMouse::Release(void)
{

}
