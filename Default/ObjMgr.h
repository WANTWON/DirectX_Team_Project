#pragma once

#include "Include.h"

class CObj;

class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();
public:
	void Release();

	// 프레임마다 실행되는 함수 
	int Update();
	void Late_Update();
	void Render(HDC hDC);

	void Add_Object(OBJID _ID, CObj* pObj);
	void Delete_ID(OBJID eID);

public:
	CObj* Get_Player() { return m_pObjList[OBJ_PLAYER].front(); }
	list<CObj*>* Get_IDlist(OBJID _eID) { return &m_pObjList[_eID]; }
	CObj* Get_Target(OBJID _ID, CObj* pObj);

public:
	// 게터와 세터
	static CObjMgr* Get_Instance()
	{
		if (m_pInstance == nullptr)
			m_pInstance = new CObjMgr;

		return m_pInstance;
	}

	static void Destroy_Instance()
	{
		if (nullptr != m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CObjMgr* m_pInstance;

	list<CObj*> m_pObjList[OBJ_END];
};

