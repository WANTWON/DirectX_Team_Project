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
	void		Update_Rect();
	void		Ckeck_Rect();
private:
	RECT				m_rc[2];
	DWORD				m_dTime;
	DWORD				m_dDeadTime;
	float				m_fAngle;
	D3DXVECTOR3			m_vPoint[4];
	D3DXVECTOR3			m_vOriginPoint[4];
	float				m_iTailSize;
	bool				m_bDead;
	bool				m_bDeadTime;
	bool				m_Clear;
	int					m_iScore;
	
};