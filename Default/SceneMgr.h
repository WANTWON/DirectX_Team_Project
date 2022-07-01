#pragma once
#include "Scene.h"


class CSceneMgr
{
private:
	CSceneMgr();
	~CSceneMgr();

public:
	void		Scene_Change(SCENEID eScene);
	void		Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);

public:
	const SCENEID& Get_CurScene(void) const { return m_eCurScene; }

public:
	static		CSceneMgr*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CSceneMgr;

		return m_pInstance;
	}

	static		void			Destroy_Instance(void)
	{
		if (nullptr != m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
private:
	static		CSceneMgr*		m_pInstance;
	CScene*						m_pScene;

	SCENEID						m_ePreScene;
	SCENEID						m_eCurScene;
};

