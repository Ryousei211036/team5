//==============================================================================
//
// Map.h
// Author : Saito Shian
//
//==============================================================================

//==============================================================================
// 2重インクルードガード
//==============================================================================
#ifndef _MAP_H_
#define	_MAP_H_

//==============================================================================
// インクルード
//==============================================================================
#include "main.h"
#include "object.h"

//==============================================================================
// マップクラス
//==============================================================================
class CMap
{
public:
	CMap();						//コンストラクタ
	~CMap();					//デストラクタ

	HRESULT Init();				//初期化処理
	void Uninit();				//終了処理
	void Update();				//更新処理
	void Draw();				//描画処理

	static CMap *Create();		//生成

private:
};

#endif
