#pragma once
#include "Obj.h"
class CPlayer3 :
	public CObj
{
public:
	CPlayer3();
	virtual ~CPlayer3();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void		Key_Input(void);
};

