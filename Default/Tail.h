#pragma once
#include "Obj.h"

class CTail : public CObj
{
public:
	CTail();
	virtual ~CTail();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	const RECT Get_Rect() const { return m_rc; }
private:

	void		Update_Rect();
private:
	float		m_fAngle;
	D3DXVECTOR3			m_vOriginPoint[4];
	RECT m_rc;
	
};

