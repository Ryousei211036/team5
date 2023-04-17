//==============================================================================================
//
// ゲーム　　　game.h
// 土田凌聖
//
//==============================================================================================
#ifndef _GAME_H_
#define	_GAME_H_

#include"object.h"

class CCamera;

class CGame : public CObject
{
public:
	CGame(int nPriority = 0);
	~CGame();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	static CGame *Create();

	EObjType GetObjType() override { return OBJTYPE_MODE; }		// オブジェクトタイプ
	static CCamera *GetCamera() { return m_pCamera; }			// カメラ
	
private:
	static CCamera *m_pCamera;
};

#endif // !_GAME_H_
