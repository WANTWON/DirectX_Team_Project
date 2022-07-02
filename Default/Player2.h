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
	virtual		void	Render(HDC hDC) override;
	virtual		void	 Release(void) override;

private:
	void			Key_Input(void);
	//CObj*			Create_Bullet(DIRECTION eDir);

	D3DXVECTOR3		m_vPoint[4];
	D3DXVECTOR3		m_vOriginPoint[4];

	D3DXVECTOR3		m_vGunPoint;
	D3DXVECTOR3		m_vOriginGunPoint;
	float			m_fPosinAngle;
	D3DXMATRIX		matWorld2;
	D3DXVECTOR3		vBDir;
	float			m_fAngle;
	bool			m_bDead;

private:
	//list<CObj*>*		m_pBullet;
	DWORD				m_dBulletTime;



};

