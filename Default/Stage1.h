#pragma once
#include "Scene.h"
class CStage1 :
	public CScene
{
public:
	CStage1();
	virtual ~CStage1();

public:
	void Initialize(void);
	int Update(void);
	void Late_Update(void);
	void Release(void);
	void Render(HDC hDC);
private:
	void Create_Item();
	void Create_Monster();
private:
	DWORD m_dtime;
	DWORD m_dtime2;
};

