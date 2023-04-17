//==============================================================================================
//
// オブジェクト　　　object.h
// Author : 土田凌聖
//
//==============================================================================================
#ifndef _OBJECT_H_
#define	_OBJECT_H_

#include <d3dx9.h>

#define	MAX_PRI			(6)			// 優先順位の最大数

class CObject
{
public:
	// オブジェクトの種類
	enum EObjType
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_MODE,		// ゲームモード
		OBJTYPE_MAX
	};

	CObject(int nPriority = 3);
	virtual ~CObject();

	virtual HRESULT Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	static void ReleaseAll();
	static void UpdateAll();
	static void DrawAll();

	void Release();
	void Death(int nPriority);
	float Distance(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2);		// 二つの位置の距離

	CObject *GetNext() { return m_pNext; }
	static CObject *GetTop(int Pri) { return m_pTop[Pri]; }
	virtual EObjType GetObjType() { return OBJTYPE_NONE; }		// オブジェクトタイプの取得
	bool GetDeathFlag() { return m_bDeath; }

private:
	int m_nPriority;
	CObject *m_pPrev;						// 一つ前のオブジェクトへのポインタ
	CObject *m_pNext;						// 次のオブジェクトへのポインタ
	static CObject *m_pTop[MAX_PRI];		// 先頭のオブジェクトのへのポインタ
	static CObject *m_pCurrent[MAX_PRI];	// 現在(一番後ろ)のオブジェクトのへのポインタ
	bool m_bDeath;							// 死亡フラグ
};

#endif // !_OBJECT_H_
