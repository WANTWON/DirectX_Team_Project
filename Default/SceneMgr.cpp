#include "stdafx.h"
#include "SceneMgr.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "Obj.h"
#include "Stage1.h"
#include "Stage2.h"
#include "Stage3.h"
#include "Stage4.h"
#include "MyMenu.h"

// STATE 패턴 (FSM : Finite State Machine 유한 상태 기계) :자신이 취할 수 있는 유한한 개수의 상태를 가지고, 그리고 그 중 반드시 하나의 상태만 가질 수 있다.

CSceneMgr* CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr()
	: m_pScene(nullptr), m_ePreScene(SC_END), m_eCurScene(SC_MENU)
{

}


CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Scene_Change(SCENEID eScene)
{
	m_eCurScene = eScene;

	if (m_ePreScene != m_eCurScene)
	{
		Safe_Delete<CScene*>(m_pScene);		//

		switch (m_eCurScene)
		{
		case SC_MENU:
			m_pScene = new CMyMenu;
			break;

		case SC_STAGE1:
			Reset_Stage();
			m_pScene = new CStage1;
			break;

		case SC_STAGE2:
			Reset_Stage();
			m_pScene = new CStage2;
			break;

		case SC_STAGE3:
			Reset_Stage();
			m_pScene = new CStage3;
			break;

		case SC_STAGE4:
			Reset_Stage();
			m_pScene = new CStage4;
			break;
		}

		m_pScene->Initialize();

		m_ePreScene = m_eCurScene;
	}
}

void CSceneMgr::Update(void)
{
	m_pScene->Update();
}

void CSceneMgr::Late_Update(void)
{
	m_pScene->Late_Update();
}

void CSceneMgr::Render(HDC hDC)
{
	m_pScene->Render(hDC);
}

void CSceneMgr::Release(void)
{
	Safe_Delete<CScene*>(m_pScene);
}


void CSceneMgr::Reset_Stage()
{
	auto& iterItem = CObjMgr::Get_Instance()->Get_IDlist(OBJ_ITEM)->begin();
	auto& iterBlock = CObjMgr::Get_Instance()->Get_IDlist(OBJ_BLOCK)->begin();
	auto& iterMonster = CObjMgr::Get_Instance()->Get_IDlist(OBJ_MONSTER)->begin();
	auto& iterButton = CObjMgr::Get_Instance()->Get_IDlist(OBJ_BUTTON)->begin();

	for (; iterItem != CObjMgr::Get_Instance()->Get_IDlist(OBJ_ITEM)->end(); ++iterItem)
		Safe_Delete<CObj*>(*iterItem);
	for (; iterBlock != CObjMgr::Get_Instance()->Get_IDlist(OBJ_BLOCK)->end(); ++iterBlock)
		Safe_Delete<CObj*>(*iterBlock);
	for (; iterMonster != CObjMgr::Get_Instance()->Get_IDlist(OBJ_MONSTER)->end(); ++iterMonster)
		Safe_Delete<CObj*>(*iterMonster);
	for (; iterButton != CObjMgr::Get_Instance()->Get_IDlist(OBJ_BUTTON)->end(); ++iterButton)
		Safe_Delete<CObj*>(*iterButton);

	CObjMgr::Get_Instance()->Get_IDlist(OBJ_ITEM)->clear();
	CObjMgr::Get_Instance()->Get_IDlist(OBJ_BLOCK)->clear();
	CObjMgr::Get_Instance()->Get_IDlist(OBJ_MONSTER)->clear();
	CObjMgr::Get_Instance()->Get_IDlist(OBJ_BUTTON)->clear();
}
