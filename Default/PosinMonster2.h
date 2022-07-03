#pragma once
#include "Obj.h"
class CPosinMonster2 :
	public CObj
{
public:
	CPosinMonster2();
	virtual ~CPosinMonster2();

public:
	void		Set_Player(CObj* pPlayer) { m_pPlayer = pPlayer; }
	CObj*		Create_Bullet(DIRECTION eDir);

public:
	virtual		void	Initialize(void) override;
	virtual		int		Update(void) override;
	virtual		void	Late_Update(void) override;
	virtual		void	Render(HDC hDC) override;
	virtual		void	Release(void) override;

private:
	void	Monster_Move();


private:
	CObj*			m_pPlayer = nullptr;
	bool			m_bDead;
	D3DXVECTOR3		m_vGunPosin;

	D3DXVECTOR3		m_originGunPoint;
	D3DXVECTOR3		m_vInitPoint;

	float			m_fPosinAngle;
	DWORD			m_dBulletTime;

};

