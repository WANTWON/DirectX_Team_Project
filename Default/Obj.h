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
	void Set_bDead() { m_bDead = true; }
	const INFO&		Get_Info(void)const { return m_tInfo; }
	const RECT&		Get_Rect(void) const { return m_tRect; }

public:
	virtual		void	Initialize(void)	PURE;
	virtual		int		Update(void)		PURE;
	virtual		void	Late_Update(void)	PURE;
	virtual		void	Render(HDC hDC)		PURE;
	virtual		void	Release(void)		PURE;

public:
	void		Set_FrameKey(TCHAR* _pFramekey) { m_pFrameKey = _pFramekey; }
	
protected:
	void		Update_Rect(void);

protected:
	INFO		m_tInfo;
	TCHAR*		m_pFrameKey;

	float		m_fSpeed;
	RECT		m_tRect;
	bool		m_bDead;
};

