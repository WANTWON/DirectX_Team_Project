#pragma once

#include "Define.h"

class CMainGame
{
public:					// 생성자, 소멸자
	CMainGame();
	~CMainGame();

// public, protected, private 함수
 public:
	void		Initialize(void);
	void		Update(void);
	void		Late_Update(void);
	void		Render(void);
	void		Release(void);

// public, protected, private 변수
private:
	HDC			m_hDC;

	DWORD m_dwTime;
	int m_iFPS;
	TCHAR m_szFPS[32];

	HDC hMemdc;
	HBITMAP hBitmap;
	HBITMAP hOldBitmap;
};