//==============================================================================================
//
// リザルト　　　result.h
// 土田凌聖
//
//==============================================================================================
#ifndef _RESULT_H_
#define	_RESULT_H_

#include"object.h"

class CRanking;

class CResult : public CObject
{
public:
	CResult(int nPriority = 0);
	~CResult();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	static CResult *Create();

	EObjType GetObjType() override { return OBJTYPE_MODE; }

private:
};

#endif // !_GAME_H_
