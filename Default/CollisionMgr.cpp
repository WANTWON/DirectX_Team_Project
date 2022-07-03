#include "stdafx.h"
#include "CollisionMgr.h"
#include "Monster4.h"
#include "Bullet4.h"
#include "Player4.h"
#include "ObjMgr.h"
#include "Obj.h"

RECT rc = {};

CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

bool CCollisionMgr::Collision_Rect(list<CObj*> Sour, list<CObj*> Dest)
{

	for (auto& Sour_iter = Sour.begin(); Sour_iter != Sour.end(); )
	{
		for (auto& Dest_iter = Dest.begin(); Dest_iter != Dest.end(); )
		{
			float fWidth = 0.f;
			float fHeight = 0.f;

			if ((Dest.size() != 0) && Check_Rect((*Sour_iter), (*Dest_iter), &fWidth, &fHeight))
			{
				return true;
			}
			Dest_iter++;
		}
		Sour_iter++;
	}
	return false;
}

bool CCollisionMgr::Collision_Sphere(list<CObj*> Sour, list<CObj*> Dest)
{
	int iScore = 0;

	for (auto& Sour_iter = Sour.begin(); Sour_iter != Sour.end(); )
	{
		int iter_count = 0;
		for (auto& Dest_iter = Dest.begin(); Dest_iter != Dest.end(); )
		{
			if ((Dest.size() != 0) && (ChecK_Sphere(*Sour_iter, *Dest_iter)))
			{
				return true;
			}
			Dest_iter++;
		}
		Sour_iter++;
	}
	return false;
}

bool CCollisionMgr::ChecK_Sphere(CObj * Sour, CObj * Dest)
{
	float fRadius = (Sour->Get_Info().vSIze.x + Dest->Get_Info().vSIze.x)*0.5f; //두 원의 반지름을 더한 값

	float fWidth = abs(Sour->Get_Info().vPos.x - Dest->Get_Info().vPos.x);
	float fHeight = abs(Sour->Get_Info().vPos.y - Dest->Get_Info().vPos.y);

	float fDistance = sqrtf((fWidth* fWidth) + (fHeight*fHeight));

	if (fRadius >= fDistance)
		return true;
	else
		return false;
}


bool CCollisionMgr::Collision_Rect_Ex(list<CObj*> Sour, list<CObj*> Dest)
{
	for (auto& Dest : Dest)
	{
		for (auto& Sour : Sour)
		{
			float fWidth = 0.f;
			float fHeight = 0.f;

			if (Check_Rect(Dest, Sour, &fWidth, &fHeight))
			{
				if (fWidth > fHeight)  //상하 충돌
				{
					if (Dest->Get_Info().vPos.y > Sour->Get_Info().vPos.y)
					{
						Sour->Set_PosY(-fHeight);
					}
					else
					{
						Sour->Set_PosY(fHeight);
					}
					return true;
				}
				else //좌우 충돌 
				{
					if (Dest->Get_Info().vPos.x > Sour->Get_Info().vPos.x)
					{
						Sour->Set_PosX(-fWidth);
					}
					else
					{
						Sour->Set_PosX(fWidth);
					}
					return true;
				}

			}

		}
	}
	return false;
}

bool CCollisionMgr::Check_Rect(CObj * Sour, CObj * Dest, float * _pX, float * _pY)
{
	float fWidth = abs(Sour->Get_Info().vPos.x - Dest->Get_Info().vPos.x);
	float fHeight = abs(Sour->Get_Info().vPos.y - Dest->Get_Info().vPos.y);

	float fRadiusX = (Sour->Get_Info().vSIze.x + Dest->Get_Info().vSIze.x)*0.5f;
	float fRadiusY = (Sour->Get_Info().vSIze.y + Dest->Get_Info().vSIze.y)*0.5f;

	if ((fWidth <= fRadiusX) && (fHeight <= fRadiusY))
	{
		*_pX = fRadiusX - fWidth;
		*_pY = fRadiusY - fHeight;
		return true;
	}
	else
		return false;
}

bool CCollisionMgr::Collision_Sphere(list<CObj*> Sour, CObj * Dest)
{
	for (auto& Sour_iter = Sour.begin(); Sour_iter != Sour.end(); )
	{
		int iter_count = 0;
		
			if ((Dest != nullptr) && (ChecK_Sphere(*Sour_iter, Dest)))
			{
				return true;
			}
		Sour_iter++;
	}
	return false;
}

bool CCollisionMgr::Collision_Sphere_with_Monster4(list<CObj*> Sour, CObj * Dest)
{
	for (auto& Sour_iter = Sour.begin(); Sour_iter != Sour.end(); )
	{
		if (((*Sour_iter)->Get_Info().vPos.x == Dest->Get_Info().vPos.x) &&
			((*Sour_iter)->Get_Info().vPos.y == Dest->Get_Info().vPos.y))
		{
			Sour_iter++;

			if (Sour_iter == Sour.end())
				return false;
		}
			
			if ((Dest!= nullptr) && (ChecK_Sphere(*Sour_iter, Dest)))
			{
				D3DXVECTOR3 vTemp = Dest->Get_Info().vPos - (*Sour_iter)->Get_Info().vPos;
				D3DXVec3Normalize(&vTemp, &vTemp);
				(Dest)->Set_DirVector(vTemp);
				(*Sour_iter)->Set_DirVector(-vTemp);
				return true;
			}
			
		Sour_iter++;
	}
	return false;
}

bool CCollisionMgr::Collision_Sphere_with_Bullet(list<CObj*> Sour, CObj * Dest)
{
	for (auto& Sour_iter = Sour.begin(); Sour_iter != Sour.end(); )
	{
		if (((*Sour_iter)->Get_Info().vPos.x == Dest->Get_Info().vPos.x) &&
			((*Sour_iter)->Get_Info().vPos.y == Dest->Get_Info().vPos.y))
		{
			Sour_iter++;

			if (Sour_iter == Sour.end())
				return false;
		}

		if ((Dest != nullptr) && (ChecK_Sphere(*Sour_iter, Dest)))
		{
			D3DXVECTOR3 vTemp = Dest->Get_Info().vPos - (*Sour_iter)->Get_Info().vPos;
			D3DXVec3Normalize(&vTemp, &vTemp);
			(Dest)->Set_DirVector(vTemp);
			dynamic_cast<CBullet4*>(*Sour_iter)->Set_DirVector(-vTemp);
			dynamic_cast<CBullet4*>(*Sour_iter)->Set_bMove();
			return true;
		}

		Sour_iter++;
	}
	return false;
}

bool CCollisionMgr::Collision_Point(D3DXVECTOR3 Point, CObj * Monster)
{
	float fRadius = (Monster->Get_Info().vSIze.x)*0.5f; //원의 반지름
	bool bCoillision = false;


	if ((Point.x >= (Monster->Get_Info().vPos.x - fRadius)  && (Point.x <= (Monster->Get_Info().vPos.x + fRadius)
		&& (Point.y <= Monster->Get_Info().vPos.y + fRadius) && (Point.y >= Monster->Get_Info().vPos.y - fRadius))))
	{
		bCoillision = true; //Left collision
		static_cast<CPlayer4*>(CObjMgr::Get_Instance()->Get_Player())->Set_Stop();
	}
	

	if (bCoillision)
	{
		D3DXVECTOR3 vTemp = Monster->Get_Info().vPos - Point;
		D3DXVec3Normalize(&vTemp, &vTemp);
		(Monster)->Set_DirVector(vTemp);
		return true;
	}

	return false;
}
