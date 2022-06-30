#pragma once

#include "Obj.h"

class CPlayer :	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void		Key_Input(void);

};

// 1. ���콺 �����͸� ����ٴϴ� �÷��̾ ������(��, ���� ������ �ƴ� ������ �̿��ؼ� ������)

// 2. ���� ���� �ؿ���








// ������ ������ �ʼ� ���� : �ݵ�� �� ���⺤�Ϳ��� ����

// ����, ������ ������ �̿��Ͽ� ��Į�� ���ϰ� �� ��Į��� ������ �������� �� ���� ���ʹ� ���� ���Ϳ��� �Ѵ�.

//������ ���� : U(x, y, z) V(X`, Y`, Z`)	-> x * X` + y * Y` + z * Z`