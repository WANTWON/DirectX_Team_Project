#pragma once

typedef struct tagInfo
{
	D3DXVECTOR3		vPos;		// ¿ßƒ° ∫§≈Õ
	D3DXVECTOR3		vDir;		// πÊ«‚ ∫§≈Õ

	D3DXVECTOR3		vLook;		// πÊ«‚ ∫§≈Õ
	D3DXVECTOR3		vNormal;	// π˝º± ∫§≈Õ
	
}INFO;


static D3DXVECTOR3			Get_Mouse(void)
{
	POINT		pt;

	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	return D3DXVECTOR3(float(pt.x), float(pt.y), 0.f);
}