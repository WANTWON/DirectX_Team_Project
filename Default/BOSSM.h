#pragma once
#include "Obj.h"
class BOSSM :
	public CObj
{
public:
	BOSSM();
	virtual ~BOSSM();

public:
	void		Set_Player(CObj* pPlayer) { m_pPlayer = pPlayer; }

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;


	void move();

private:
	CObj*			m_pPlayer = nullptr;

	int m_Bhp;
	int m_bosscount;


};
