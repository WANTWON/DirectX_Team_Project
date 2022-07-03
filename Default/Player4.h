#pragma once
#include "Obj.h"
class CPlayer4 :
	public CObj
{
public:
	enum State {SHOOT, NORMAL, END};

public:
	CPlayer4();
	virtual ~CPlayer4();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void Set_Score(int i) { m_iScore += i; }
	void Set_Clear(void) { m_bClear = true; }
	void Set_Stop(void) { m_bJump = false; }
	const D3DXVECTOR3& Get_PosinPoint(void) const { return m_vPosin; }
	const State& Get_State(void) const { return m_eState; }
	const bool& Get_Clear(void) { return m_bClear; }

private:
	void		Key_Input(void);
	void		Jumping(void);

private:
	D3DXVECTOR3	m_vPoint[4];
	D3DXVECTOR3	m_pOriginPoint[4];

	D3DXVECTOR3	m_vPosin;
	D3DXVECTOR3	m_pOriginPosin;

	float m_fAngle = 0;
	float m_fPosinAngle = 0;

	int m_iScore = 0;
	bool m_bJump;
	bool m_bCount;
	bool m_bClear;

	DWORD m_dwTime;

	float m_fTime = 0;

	State m_eState = NORMAL;
};

