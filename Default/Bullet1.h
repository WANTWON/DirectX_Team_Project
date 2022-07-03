#pragma once
#include "Obj.h"

class CBullet1 : public CObj
{
public:
	CBullet1();
	virtual ~CBullet1();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	const RECT Get_Rect() const { return m_rc; }
	void Set_Dead() { m_bDead = true; }
private:
	void		Update_Rect();
private:
	float		m_fAngle;
	D3DXVECTOR3			m_vOriginPoint[4];
	RECT m_rc;
	bool			m_bDead;
	DWORD m_dTime;
	bool			m_bTrue;
	D3DXVECTOR3		m_vOriginPos;
	bool			m_Target;
};