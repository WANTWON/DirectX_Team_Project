#pragma once
#include "Obj.h"
class CItem2 :
	public CObj
{

public:
	enum ITEMTYPE { ITEM_NORMAL, ITEM_SHIELD, END };

public:
	CItem2();
	virtual ~CItem2();

public:
	virtual	void Initialize(void)	PURE;
	virtual int	 Update(void)		PURE;
	virtual	void Late_Update(void)	PURE;
	virtual void Render(HDC hDC)	PURE;
	virtual void Release(void)		PURE;

public:
	void		Set_Dead() { m_bDead = true; }
	ITEMTYPE	Get_ItemType() { return m_eItemType; }

protected:
	D3DXVECTOR3		m_vPoint[4];
	D3DXVECTOR3		m_vOriginPoint[4];
	D3DXVECTOR3		m_vInitPoint;
	D3DXMATRIX		matWorld;

	float			m_fAngle;
	ITEMTYPE		m_eItemType;
};

