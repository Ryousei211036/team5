//==============================================================================================
//
// �Q�[���@�@�@game.h
// �y�c����
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

	EObjType GetObjType() override { return OBJTYPE_MODE; }		// �I�u�W�F�N�g�^�C�v
	static CCamera *GetCamera() { return m_pCamera; }			// �J����
	
private:
	static CCamera *m_pCamera;
};

#endif // !_GAME_H_
