#pragma once
#include "Obj.h"
class CMonster3 :
	public CObj
{
public:
	CMonster3();
	virtual ~CMonster3();

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


};
