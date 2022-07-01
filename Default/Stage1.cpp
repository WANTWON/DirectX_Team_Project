#include "stdafx.h"
#include "Stage1.h"


CStage1::CStage1()
{
}


CStage1::~CStage1()
{
}

void CStage1::Initialize(void)
{
}

int CStage1::Update(void)
{
	return 0;
}

void CStage1::Late_Update(void)
{
}

void CStage1::Release(void)
{
}

void CStage1::Render(HDC hDC)
{
	Rectangle(hDC, 0, 0, WINCX, WINCY);
}
