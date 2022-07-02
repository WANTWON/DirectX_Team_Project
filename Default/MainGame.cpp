#include "stdafx.h"
#include "MainGame.h"
#include "SceneMgr.h"
#include "KeyMgr.h"
#include "BmpMgr.h"

CMainGame::CMainGame() : m_dwTime(GetTickCount()), m_iFPS(0)
{
	ZeroMemory(m_szFPS, sizeof(m_szFPS));
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_hDC = GetDC(g_hWnd);
	hMemdc = CreateCompatibleDC(m_hDC);
	hBitmap = CreateCompatibleBitmap(m_hDC, WINCX, WINCY);
	hOldBitmap = (HBITMAP)SelectObject(hMemdc, hBitmap);
	CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);
}

void CMainGame::Update(void)
{
	CSceneMgr::Get_Instance()->Update();
}

void CMainGame::Late_Update(void)
{
	CSceneMgr::Get_Instance()->Late_Update();
}

void CMainGame::Render(void)
{
	++m_iFPS;
	Rectangle(hMemdc, 0, 0, WINCX, WINCY);
	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}


	CSceneMgr::Get_Instance()->Render(hMemdc);
	BitBlt(m_hDC, 0, 0, WINCX, WINCY, hMemdc, 0, 0, SRCCOPY);

}

void CMainGame::Release(void)
{
	CSceneMgr::Get_Instance()->Destroy_Instance();
	CKeyMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Destroy_Instance();
	CBmpMgr::Get_Instance()->Destroy_Instance();

	hBitmap = (HBITMAP)SelectObject(hMemdc, hOldBitmap);
	ReleaseDC(g_hWnd, hMemdc);
	ReleaseDC(g_hWnd, m_hDC);
}
