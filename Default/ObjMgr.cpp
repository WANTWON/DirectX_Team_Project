#include "stdafx.h"
#include "ObjMgr.h"
#include "Obj.h"
#include "SceneMgr.h"

CObjMgr* CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{

}

CObjMgr::~CObjMgr()
{
	Release();
}

CObj* CObjMgr::Get_Target(OBJID _ID, CObj* pObj)
{
	return nullptr;
}


void CObjMgr::Add_Object(OBJID _ID, CObj* pObj)
{
	if (_ID == OBJ_END || nullptr == pObj)
		return;

	m_pObjList[_ID].push_back(pObj);
}

void CObjMgr::Delete_ID(OBJID eID)
{
	//for (auto& iter : m_pObjList[eID])
	//	Safe_Delete(iter);

	//m_pObjList[eID].clear();
}

int CObjMgr::Update()
{
		int iEvent = 0;
		for (size_t i = 0; i != OBJ_END; ++i)
		{
			for (auto& iter = m_pObjList[i].begin(); iter != m_pObjList[i].end(); )
			{
				iEvent = (*iter)->Update();

				if (iEvent == OBJ_DEAD)
				{
					Safe_Delete<CObj*>(*iter);
					iter = m_pObjList[i].erase(iter);
				}
				else
					++iter;
			}
		}

		return iEvent;
}

void CObjMgr::Late_Update()
{
	for (size_t i = 0; i != OBJ_END; ++i)
	{
		for (auto& iter : m_pObjList[i])
			iter->Late_Update();

		if (m_pObjList[i].empty())
			continue;
	}

}

void CObjMgr::Render(HDC hDC)
{
	for (size_t i = 0; i != OBJ_END; ++i)
	{
		for (auto& iter : m_pObjList[i])
			iter->Render(hDC);
	}
}

void CObjMgr::Release()
{
	for (size_t i = 0; i != OBJ_END; ++i)
	{
		for (auto& iter = m_pObjList[i].begin(); iter != m_pObjList[i].end(); )
		{
			Safe_Delete<CObj*>(*iter);
			iter = m_pObjList[i].erase(iter);
		}
		m_pObjList[i].clear();
	}
}