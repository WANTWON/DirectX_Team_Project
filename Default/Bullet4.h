#pragma once
#include "Obj.h"
class CBullet4 :
	public CObj
{
public:
	CBullet4();
	virtual ~CBullet4();
public:
	void		Set_Player(CObj* pPlayer) { m_pPlayer = pPlayer; }

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	CObj* m_pPlayer;
};

