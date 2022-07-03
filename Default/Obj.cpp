#include "stdafx.h"
#include "Obj.h"

CObj::CObj() : m_fSpeed(0.f), m_bDead(false), m_eID(OBJ_END) , m_fAngle(0.f)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
}

CObj::~CObj()
{
}

void CObj::Update_Rect(void)
{
	m_tRect.left = int(m_tInfo.vPos.x - (m_tInfo.vSIze.x * 0.5f));
	m_tRect.top = int(m_tInfo.vPos.y - (m_tInfo.vSIze.y * 0.5f));
	m_tRect.right = int(m_tInfo.vPos.x + (m_tInfo.vSIze.x * 0.5f));
	m_tRect.bottom = int(m_tInfo.vPos.y + (m_tInfo.vSIze.y * 0.5f));
}



