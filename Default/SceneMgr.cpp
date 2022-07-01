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

// STATE ���� (FSM : Finite State Machine ���� ���� ���) :�ڽ��� ���� �� �ִ� ������ ������ ���¸� ������, �׸��� �� �� �ݵ�� �ϳ��� ���¸� ���� �� �ִ�.

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
			m_pScene = new CStage1;
			break;

		case SC_STAGE2:
			m_pScene = new CStage2;
			break;

		case SC_STAGE3:
			m_pScene = new CStage3;
			break;

		case SC_STAGE4:
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
