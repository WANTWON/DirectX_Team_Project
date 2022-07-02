#pragma once
#include "Obj.h"
class CMonster4 :
	public CObj
{
public:
	CMonster4();
	virtual ~CMonster4();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	D3DXVECTOR3	m_pPoint[4];
	D3DXVECTOR3	m_pOriginPoint[4];

	D3DXVECTOR3	m_pOriginPos;

	bool m_bDead;
	float m_fAngle = 0;
};

