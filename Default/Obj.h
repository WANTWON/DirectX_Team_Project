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

	void		Set_TOWERTYPE(TOWERTYPE type) { m_Ttype = type; }
	void Set_PosY(float _fY) { m_tInfo.vPos.y += _fY; }
	void Set_PosX(float _fX) { m_tInfo.vPos.x += _fX; }
	void Set_bDead() { m_bDead = true; }
	bool Get_bDead(void) { return m_bDead; }
	void Set_Angle(float _fAngle) { m_fAngle = _fAngle; }
	const INFO&		Get_Info(void)const { return m_tInfo; }
	const RECT&		Get_Rect(void) const { return m_tRect; }

	TOWERTYPE	Get_TOWERID() { return m_Ttype; }

public:
	virtual		void	Initialize(void)	PURE;
	virtual		int		Update(void)		PURE;
	virtual		void	Late_Update(void)	PURE;
	virtual		void	Render(HDC hDC)		PURE;
	virtual		void	Release(void)		PURE;

public:
	void		Set_FrameKey(TCHAR* _pFramekey) { m_pFrameKey = _pFramekey; }
	void		Set_DirVector(D3DXVECTOR3 vDir) { m_pDirVector = vDir; }
	
protected:
	void		Update_Rect(void);

protected:
	INFO		m_tInfo;
	TCHAR*		m_pFrameKey;

	int m_iHp;
	float		m_fSpeed;
	float       m_fAngle;
	RECT		m_tRect;
	CObj*		m_pTarget;
	
	OBJID		m_eID;

	D3DXVECTOR3 m_pDirVector;

	DWORD		m_dwTime;

	bool m_bDead;
	bool m_bFront;

	TOWERTYPE	m_Ttype;
};

