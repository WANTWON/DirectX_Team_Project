#pragma once
#include "Obj.h"
class CGoal4 :
	public CObj
{
public:
	CGoal4();
	virtual ~CGoal4();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	D3DXVECTOR3	m_pPoint[4];
	D3DXVECTOR3	m_pOriginPoint[4];

	bool m_bCount;
};

