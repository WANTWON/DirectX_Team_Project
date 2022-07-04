#pragma once
#include "Obj.h"
class Maintower3 : public CObj
{
public:
	Maintower3();
	virtual ~Maintower3();


public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;


public:
	void set_Money(void) { m_iMoney += rand()%4 ; }
	void minus_Money(void) { m_iMoney -= 50; }
 	int get_Money(void) {return m_iMoney;}

	int Get_Score(void) { return m_iScore; }
	void Set_Score(void) { ++m_iScore; }

	void Set_bcount(void) { ++m_bosscount; }
	int Get_bcount(void) { return m_bosscount; }


	
	// {return m_iMoney;)

private:


	D3DXVECTOR3			m_vPoint[4];
	D3DXVECTOR3			m_vOriginPoint[4];

	D3DXVECTOR3			m_vGunPoint;
	D3DXVECTOR3			m_vOriginGunPoint;


private:
	int m_iHp;
	int m_iMoney;
	int m_iScore;
	int 	m_bosscount;

	



};
