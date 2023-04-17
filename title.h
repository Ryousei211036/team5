//==============================================================================================
//
// タイトル　　　title.h
// 土田凌聖
//
//==============================================================================================
#ifndef _TITLE_H_
#define	_TITLE_H_

#include"object.h"

class CCamera;

class CTitle : public CObject
{
public:
	CTitle(int nPriority = 0);
	~CTitle();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	static CTitle *Create();

	static CCamera *GetCamera() { return m_pCamera; }			// カメラ
	EObjType GetObjType() override { return OBJTYPE_MODE; }

private:
	static CCamera *m_pCamera;
};

#endif // !_GAME_H_
