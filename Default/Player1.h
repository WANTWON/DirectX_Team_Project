#pragma once
#include "Obj.h"

class CPlayer1 : public CObj
{
public:
	CPlayer1();
	virtual ~CPlayer1();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void		Key_Input(void);
	void		Update_Pos();
private:
	DWORD m_dTime;
	float		m_fAngle;
	D3DXVECTOR3			m_vPoint[4];
	D3DXVECTOR3			m_vOriginPoint[4];
	list<D3DXVECTOR3*>  m_pvPos;
	int			m_iTailSize;
};