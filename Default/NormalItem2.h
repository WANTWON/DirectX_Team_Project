#pragma once
#include "Item2.h"
class CNormalItem2 :
	public CItem2
{
public:
	CNormalItem2();
	virtual ~CNormalItem2();

public:
	virtual	void Initialize(void)	override;
	virtual int	 Update(void)		override;
	virtual	void Late_Update(void)	override;
	virtual void Render(HDC hDC)	override;
	virtual void Release(void)		override;

private:
	void	Collision_Check();
	void	Item_Move();

};
