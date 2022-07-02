#pragma once
#include "Obj.h"
class CBullet4 :
	public CObj
{
public:
	CBullet4();
	virtual ~CBullet4();
public:
	void		Set_Player(CObj* pPlayer) { m_pPlayer = pPlayer; }
	void		Set_Pos(D3DXVECTOR3 Pos) { m_vOriginPos = Pos; }
	void		Set_Angle(float angle) { m_fAngle = angle; }

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void Set_DirVector(D3DXVECTOR3 vDir) { m_pDirVector = vDir; }
private:
	CObj* m_pPlayer;

	D3DXVECTOR3 m_vPoint[8];
	D3DXVECTOR3 m_vOriginPoint[8];

	D3DXVECTOR3 m_vOriginPos;

	float XScale, YScale, ZScale;

	float m_fAngle;

	bool m_bCount;

	D3DXVECTOR3 m_pDirVector;
};

