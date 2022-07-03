#pragma once
#include "Obj.h"
class CMonster4 :
	public CObj
{
public:
	enum State { NORMAL, RED, END};

public:
	CMonster4();
	virtual ~CMonster4();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void Set_RED_ball(void) { m_eState = RED; }

private:
	D3DXVECTOR3	m_vPoint[8];
	D3DXVECTOR3	m_pOriginPoint[8];
	D3DXVECTOR3	m_pOriginPos;

	bool m_bMove;
	bool m_bCount;
	float m_fAngle = 0;
	float m_fMoveAngle = 0;

	State m_eState = NORMAL;
};

