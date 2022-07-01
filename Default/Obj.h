#pragma once

#include "Include.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	void		Set_Pos(float _fX, float _fY) 
	{
		m_tInfo.vPos.x = _fX;
		m_tInfo.vPos.y = _fY;
	}
	void Set_PosY(float _fY) { m_tInfo.vPos.y += _fY; }
	void Set_PosX(float _fX) { m_tInfo.vPos.x += _fX; }
	const INFO&		Get_Info(void)const { return m_tInfo; }

public:
	virtual		void	Initialize(void)	PURE;
	virtual		int		Update(void)		PURE;
	virtual		void	Late_Update(void)	PURE;
	virtual		void	Render(HDC hDC)		PURE;
	virtual		void	Release(void)		PURE;

public:
	void		Set_FrameKey(TCHAR* _pFramekey) { m_pFrameKey = _pFramekey; }
	
protected:
	INFO		m_tInfo;
	TCHAR*		m_pFrameKey;
	int m_iHp;
	float		m_fSpeed;


	DWORD		m_dwTime;

	bool m_bDead;
	bool m_bFront;
};

