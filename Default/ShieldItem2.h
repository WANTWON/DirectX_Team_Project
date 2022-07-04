#pragma once
#include "Item2.h"
class CShieldItem2 :
	public CItem2
{
public:
	CShieldItem2();
	virtual ~CShieldItem2();

public:
	virtual		void	Initialize(void) override;
	virtual		int		Update(void) override;
	virtual		void	Late_Update(void) override;
	virtual		void	Render(HDC hDC) override;
	virtual		void	Release(void) override;

private:
	void	Collision_Check();

private:
	int		m_iHp;
	float	m_fAngle2;
	float	m_fDistance;
};

