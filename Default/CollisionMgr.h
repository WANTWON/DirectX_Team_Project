#pragma once
#include "Obj.h"

class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

	static bool Collision_Rect(list<CObj*> Sour, list<CObj*> Dest);
	static bool Collision_Sphere(list<CObj*> Sour, list<CObj*> Dest);
	static bool ChecK_Sphere(CObj* Sour, CObj* Dest);
	static bool Collision_Rect_Ex(list<CObj*> Sour, list<CObj*> Dest);
	static bool Check_Rect(CObj* Sour, CObj* Dest, float* _pX, float* _pY);

	static bool Collision_Sphere(list<CObj*> Sour, CObj* Dest);
	static bool Collision_Sphere_with_Monster4(list<CObj*> Sour, CObj* Dest);
	static bool Collision_Sphere_with_Bullet(list<CObj*> Sour, CObj* Dest);
	static bool Collision_Point(D3DXVECTOR3 Point, CObj* Monster);
};

