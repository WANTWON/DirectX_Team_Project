#include "stdafx.h"
#include "MyButton.h"
#include "KeyMgr.h"
#include "SceneMgr.h"


CMyButton::CMyButton()
{
}


CMyButton::~CMyButton()
{
	Release();
}

void CMyButton::Initialize(void)
{
	int Temp = 0;
}

int CMyButton::Update(void)
{

	for (int i = 0; i < 4; ++i)
	{
		m_tRect[i].left = int(m_tInfo.vPos.x - 25);
		m_tRect[i].top = int(m_tInfo.vPos.y - 25);
		m_tRect[i].right = int(m_tInfo.vPos.x + 25);
		m_tRect[i].bottom = int(m_tInfo.vPos.y + 25);

	}
	

	return OBJ_NOEVENT;
}

void CMyButton::Late_Update(void)
{
	//if (this == nullptr)
		//return;

	POINT		Pt;
	GetCursorPos(&Pt);
	ScreenToClient(g_hWnd, &Pt);


	for (int i = 0; i < 4; ++i)
	{
		if (PtInRect(&m_tRect[i], Pt))
		{
			if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
			{
				if (!lstrcmp(L"Stage1", m_pFrameKey))
					CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE1);
				else if (!lstrcmp(L"Stage2", m_pFrameKey))
					CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE2);
				else if (!lstrcmp(L"Stage3", m_pFrameKey))
					CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE3);
				else if (!lstrcmp(L"Stage4", m_pFrameKey))
					CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE4);

				return;
			}
		}

	}
}

void CMyButton::Render(HDC hDC)
{
	for (size_t i = 0; i< 4; ++i)
		Rectangle(hDC, m_tRect[i].left, m_tRect[i].top, m_tRect[i].right, m_tRect[i].bottom);

}

void CMyButton::Release(void)
{

}
