#pragma once
#include "Obj.h"
class CBullet3 : public CObj
{
public:
	CBullet3();
	virtual ~CBullet3();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

};

