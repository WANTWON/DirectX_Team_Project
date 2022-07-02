#pragma once
#include "Obj.h"
class CMonster2 :
	public CObj
{
public:
	CMonster2();
	virtual ~CMonster2();

public:
	void	Set_Player(CObj* pPlayer) { m_pPlayer = pPlayer; }


private:
	void	Monster_Move();
	CObj*	Create_Bullet(DIRECTION eDir);

public:
	virtual void Initialize(void) override;
	virtual int	 Update(void) override;
	virtual	void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	CObj*			m_pPlayer = nullptr;
	bool			m_bDead;
	DWORD			m_dBulletTime;
};

