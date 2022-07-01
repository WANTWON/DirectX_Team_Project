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

	// �����Ӹ��� ����Ǵ� �Լ� 
	int Update();
	void Late_Update();
	void Render(HDC hDC);

	void Add_Object(OBJID _ID, CObj* pObj);
	void Delete_ID(OBJID eID);

public:
	CObj* Get_Player() { return m_pObjList[OBJ_PLAYER].front(); }
	list<CObj*> Get_listPlayer() { return m_pObjList[OBJ_PLAYER]; }
	list<CObj*> Get_Monsters() { return m_pObjList[OBJ_MONSTER]; }
	list<CObj*> Get_Blocks() { return m_pObjList[OBJ_BLOCK]; }
	list<CObj*> Get_Items() { return m_pObjList[OBJ_ITEM]; }
	list<CObj*> Get_Bullets() { return m_pObjList[OBJ_BULLET]; }

	CObj* Get_Target(OBJID _ID, CObj* pObj);

public:
	// ���Ϳ� ����
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

