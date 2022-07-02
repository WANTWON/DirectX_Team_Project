#pragma once

typedef struct tagInfo
{
	D3DXVECTOR3		vSIze;

	D3DXVECTOR3		vPos;		// ��ġ ����
	D3DXVECTOR3		vDir;		// ���� ����

	D3DXVECTOR3		vLook;		// ���� ����
	D3DXVECTOR3		vNormal;	// ���� ����
	D3DXMATRIX		matWorld;
}INFO;


static D3DXVECTOR3			Get_Mouse(void)
{
	POINT		pt;

	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	return D3DXVECTOR3(float(pt.x), float(pt.y), 0.f);
}