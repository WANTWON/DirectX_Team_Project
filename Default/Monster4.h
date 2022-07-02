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

public:
	void Set_DirVector(D3DXVECTOR3 vDir) { m_pDirVector = vDir; }

private:
	D3DXVECTOR3	m_pPoint[8];
	D3DXVECTOR3	m_pOriginPoint[8];

	D3DXVECTOR3	m_pOriginPos;

	D3DXVECTOR3 m_pDirVector;

	bool m_bMove;
	float m_fAngle = 0;
};

