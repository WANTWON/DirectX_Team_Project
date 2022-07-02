#pragma once
#include "Obj.h"
class CPlayer4 :
	public CObj
{
public:
	CPlayer4();
	virtual ~CPlayer4();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void		Key_Input(void);

private:
	D3DXVECTOR3	m_pPoint[4];
	D3DXVECTOR3	m_pOriginPoint[4];

	D3DXVECTOR3	m_pPosin;
	D3DXVECTOR3	m_pOriginPosin;

	float m_fAngle = 0;
	float m_fPosinAngle = 0;
};

