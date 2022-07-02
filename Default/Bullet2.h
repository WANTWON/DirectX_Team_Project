#pragma once
#include "Obj.h"
class CBullet2 :
	public CObj
{
public:
	CBullet2();
	virtual ~CBullet2();

public:
	virtual void Initialize(void) override;
	virtual int	 Update(void) override;
	virtual	void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void		Set_Dir(D3DXVECTOR3 eDir) { m_eDir = eDir; }
	void		Set_Angle(float _fAngle) { m_fAngle = _fAngle; }


private:
	D3DXVECTOR3		m_vPoint[3];
	D3DXVECTOR3		m_vOriginPoint[3];
	D3DXVECTOR3		m_vInitPoint;
	D3DXVECTOR3		m_eDir;
	float			m_fAngle;
	bool			m_bDead;
};

