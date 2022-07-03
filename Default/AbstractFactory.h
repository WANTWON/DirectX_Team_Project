#pragma once

#include "Obj.h"

template<typename T>
class CAbstractFactory
{
public:
	static CObj*		Create(void)
	{
		CObj*		pInstance = new T;
		pInstance->Initialize();

		return pInstance;
	}

	static CObj*		Create(float _fX, float _fY, float _fAngle)
	{
		CObj*		pInstance = new T;
		pInstance->Initialize();
		pInstance->Set_Pos(_fX, _fY);
		pInstance->Set_Angle(_fAngle);

		return pInstance;
	}

	static CObj*		Create(float _fX, float _fY, OBJID _ObjID = OBJ_END)
	{
		CObj*		pInstance = new T;
		pInstance->Initialize();
		pInstance->Set_Pos(_fX, _fY);

		return pInstance;
	}

	static CObj*		Create(float _fX, float _fY, TOWERTYPE eType)
	{

		CObj*		pInstance = new T;

		
			pInstance->Set_TOWERTYPE(eType);

		pInstance->Initialize();
		pInstance->Set_Pos(_fX, _fY);

		return pInstance;
	}

public:
	CAbstractFactory() {	}
	~CAbstractFactory() { }
};

