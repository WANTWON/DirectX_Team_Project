#pragma once
#include "Scene.h"
class CStage4 :
	public CScene
{
public:
	CStage4();
	virtual ~CStage4();

public:
	void Initialize(void);
	int Update(void);
	void Late_Update(void);
	void Release(void);
	void Render(HDC hDC);

private:
	bool m_bClear = false;
	bool m_bCount = false;
	DWORD m_dwTime;
};

