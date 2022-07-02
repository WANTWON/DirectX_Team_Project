#pragma once
#include "Obj.h"
class CPlayer2 :
	public CObj
{
public:
	CPlayer2();
	virtual ~CPlayer2();

public:
	virtual		void	Initialize(void) override;
	virtual		int		Update(void) override;
	virtual		void	Late_Update(void) override;
	virtual		void	Render(HDC hDC) override;
	virtual		void	Release(void) override;

private:
	void			Key_Input(void);
	CObj*			Create_Bullet(DIRECTION eDir);

private:
	D3DXVECTOR3		m_vPoint[4];
	D3DXVECTOR3		m_vOriginPoint[4];
	D3DXVECTOR3		m_vGunPoint;
	D3DXVECTOR3		m_vOriginGunPoint;
	D3DXVECTOR3		vBDir;
	
	D3DXMATRIX		matWorld2;

	float			m_fPosinAngle;
	float			m_fAngle;
	DWORD			m_dBulletTime;
	bool			m_bDead;
	list<CObj*>*	m_pBullet;
};

