#include "stdafx.h"
#include "Obj.h"

CObj::CObj() : m_fSpeed(0.f) , m_bDead(false) , m_dwTime(GetTickCount()) , m_bFront(false)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
}

CObj::~CObj()
{
}



