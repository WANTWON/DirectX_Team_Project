#pragma once
#include "Scene.h"
class CStage2 :
	public CScene
{
public:
	CStage2();
	virtual ~CStage2();

public:
	void	Initialize(void);
	int		Update(void);
	void	Late_Update(void);
	void	Release(void);
	void	Render(HDC hDC);

private:
	DWORD	m_dCreateMonsterTime;
	bool	m_bMonsterType;
	float	monsterY;
};

