#include "stdafx.h"
#include "Stage2.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Player2.h"
#include "Monster2.h"
#include "PosinMonster2.h"
#include "CollisionMgr.h"

CStage2::CStage2()
{
}


CStage2::~CStage2()
{
	
}

void CStage2::Initialize(void)
{
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer2>::Create(100.f, 300.f));

	CObj*		pMonster = new CPosinMonster2;
	pMonster->Set_Pos(900.f, 200.f);
	dynamic_cast<CPosinMonster2*>(pMonster)->Set_Player(CObjMgr::Get_Instance()->Get_Player());
	pMonster->Initialize();
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pMonster);

	CObj*		pMonster2 = new CMonster2;
	pMonster2->Set_Pos(1100.f, 500.f);
	dynamic_cast<CMonster2*>(pMonster2)->Set_Player(CObjMgr::Get_Instance()->Get_Player());
	pMonster2->Initialize();
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pMonster2);

	m_dCreateMonsterTime = GetTickCount();
	m_bMonsterType = false;

	monsterY = 50;
}

int CStage2::Update(void)
{
	if (m_dCreateMonsterTime + 3000 < GetTickCount())
	{
		if (monsterY >= 600)
			monsterY = 50.f;

		if (m_bMonsterType)
		{
			CObj*		pMonster = new CPosinMonster2;
			pMonster->Set_Pos(900.f, monsterY - 20.f);
			dynamic_cast<CPosinMonster2*>(pMonster)->Set_Player(CObjMgr::Get_Instance()->Get_Player());
			pMonster->Initialize();
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pMonster);
			m_bMonsterType = false;
		}
		else
		{
			CObj*		pMonster2 = new CMonster2;
			pMonster2->Set_Pos(1100.f, monsterY + 30.f);
			dynamic_cast<CMonster2*>(pMonster2)->Set_Player(CObjMgr::Get_Instance()->Get_Player());
			pMonster2->Initialize();
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pMonster2);
			m_bMonsterType = true;
		}
		m_dCreateMonsterTime = GetTickCount();
		monsterY += 30.f;
	}
	CObjMgr::Get_Instance()->Update();

	return 0;
}

void CStage2::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CStage2::Release(void)
{
}

void CStage2::Render(HDC hDC)
{
	CObjMgr::Get_Instance()->Render(hDC);
}

