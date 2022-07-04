#pragma once
#include "Scene.h"
class CStage3 :
	public CScene
{
public:
	CStage3();
	virtual ~CStage3();

public:
	void Initialize(void);
	int Update(void);
	void Late_Update(void);
	void Release(void);
	void Render(HDC hDC);


	int moncreate;
	int um;
	DWORD		m_dwTime;

};

