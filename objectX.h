//==============================================================================================
//
//モデルの処理[model.h]
//Author：土田凌聖
//
//==============================================================================================
#ifndef _OBJECTX_H_
#define _OBJECTX_H_

#include"Object.h"
#include"renderer.h"
#include"texture.h"

class CGage;

class CObjectX : public CObject
{
public:
	CObjectX(int nPriority = 3);
	~CObjectX();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void DrawShadow();		// 影
	void Stencil();			// ステンシル
	static CObjectX *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, const char* name);

	void SetXFileName(const char *FileName) { m_FileName = FileName; }
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetSize(D3DXVECTOR3 size) { m_Size = size; }

	D3DXVECTOR3 GetPos() { return m_pos; }
	D3DXVECTOR3 GetRot() { return m_rot; }
	D3DXVECTOR3 GetSize() { return m_Size; }
	D3DXVECTOR3 GetMax() { return m_vtxMaxModel; }
	D3DXVECTOR3 GetMin() { return m_vtxMinModel; }

	static const int m_nMax_Model = 128;	// オブジェクトXの最大数
private:
	D3DXVECTOR3 m_pos;				// 位置
	D3DXVECTOR3 m_posOld;			// 前回の位置
	D3DXVECTOR3 m_rot;				// 向き
	D3DXVECTOR3 m_Initrot;			// 最初の向き
	D3DXVECTOR3 m_Size;				// サイズ
	D3DXVECTOR3 m_vtxMinModel;		// 頂点の最小値
	D3DXVECTOR3 m_vtxMaxModel;		// 頂点の最大値
	D3DXVECTOR3 m_vecDir;			// プレイヤーの方向ベクトル
	LPD3DXBUFFER m_pBuffMat;		// マテリアル情報へのポインタ
	LPD3DXMESH m_pMesh;				// メッシュ情報へのポインタ
	D3DXMATRIX m_mtxWorld;			// ワールドマトリックス
	DWORD m_nNumMat;				// マテリアル情報の数
	D3DXMATRIX m_mtxRot;			// 回転マトリックス
	const char *m_FileName;			// ファイルの名前
};

#endif // !_OBJECTX_H_