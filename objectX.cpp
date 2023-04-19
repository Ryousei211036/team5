//==============================================================================================
//
// オブジェクトX　　　objectX.cpp
// 土田凌聖
//
//==============================================================================================
#include"ObjectX.h"
#include"application.h"
#include"game.h"
#include"inputkeyboard.h"
#include"fade.h"
#include"light.h"
#include"camera.h"

//==============================================================================================
// コンストラクタ
//==============================================================================================
CObjectX::CObjectX(int nPriority) : CObject(nPriority)
{
	m_pos = { 0.0f,0.0f,0.0f };
	m_posOld = { 0.0f,0.0f,0.0f };
	m_rot = { 0.0f,0.0f,0.0f };
	m_vtxMinModel = { 0.0f,0.0f,0.0f };
	m_vtxMaxModel = { 0.0f,0.0f,0.0f };
	m_vecDir = { 0.0f,0.0f,0.0f };
	m_pBuffMat = nullptr;
	m_pMesh = nullptr;
}

//==============================================================================================
// デストラクタ
//==============================================================================================
CObjectX::~CObjectX()
{
}

//==============================================================================================
// 初期化処理
//==============================================================================================
HRESULT CObjectX::Init()
{
	D3DXMatrixIdentity(&m_mtxRot);

	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//Xファイルの読み込み
	D3DXLoadMeshFromX(m_FileName,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_nNumMat,
		&m_pMesh);

	int nNumVtx;		//頂点数
	DWORD sizeFVF;		//頂点フォーマットのサイズ
	BYTE *pVtxBuff;		//頂点バッファへのポインタ

	//頂点数の取得
	nNumVtx = m_pMesh->GetNumVertices();

	//頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	//頂点バッファのロック
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		//頂点座標の代入
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		//最小値の取得
		if (vtx.x < m_vtxMinModel.x)
		{
			m_vtxMinModel.x = vtx.x;
		}
		else if (vtx.y < m_vtxMinModel.y)
		{
			m_vtxMinModel.y = vtx.y;
		}
		else if (vtx.z < m_vtxMinModel.z)
		{
			m_vtxMinModel.z = vtx.z;
		}

		//最大値の取得
		if (vtx.x > m_vtxMaxModel.x)
		{
			m_vtxMaxModel.x = vtx.x;
		}
		else if (vtx.y > m_vtxMaxModel.y)
		{
			m_vtxMaxModel.y = vtx.y;
		}
		else if (vtx.z > m_vtxMaxModel.z)
		{
			m_vtxMaxModel.z = vtx.z;
		}

		//頂点フォーマットのサイズ分ポインタを進める
		pVtxBuff += sizeFVF;
	}

	//頂点バッファのアンロック
	m_pMesh->UnlockVertexBuffer();

	return S_OK;
}

//==============================================================================================
// 終了処理
//==============================================================================================
void CObjectX::Uninit()
{
	for (int nCnt = 0; nCnt < m_nMax_Model; nCnt++)
	{
		//メッシュの破棄
		if (m_pMesh != NULL)
		{
			m_pMesh->Release();
			m_pMesh = NULL;
		}

		//マテリアルの破棄
		if (m_pBuffMat != NULL)
		{
			m_pBuffMat->Release();
			m_pBuffMat = NULL;
		}
	}

	Release();
}

//==============================================================================================
//更新処理
//==============================================================================================
void CObjectX::Update()
{
	
}

//==============================================================================================
// 描画処理
//==============================================================================================
void CObjectX::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans, mtxScaling;		//計算用のマトリックス
	D3DMATERIAL9 matDef;		//現在のマテリアルの保存用
	D3DXMATERIAL *pMat;			//マテリアルデータへのポインタ
	D3DXQUATERNION m_quat;		// クォータニオン

	//ワールドマトリックス
	D3DXMatrixIdentity(&m_mtxWorld);

	// サイズを反映
	D3DXMatrixScaling(&mtxScaling, m_Size.x, m_Size.y, m_Size.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScaling);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&m_mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// 平面投影
	//DrawShadow();

	// ステンシルバッファの設定
	Stencil();

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//現在のマテリアルを保持
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	// ステンシル用の描画
	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//モデルパーツの描画
		m_pMesh->DrawSubset(nCntMat);
	}

	// ステンシルバッファ=>無効
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);

	// 普通の描画
	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		// マテリアル情報の設定
		D3DMATERIAL9 matD3D = pMat[nCntMat].MatD3D;
		
		// マテリアルの設定
		pDevice->SetMaterial(&matD3D);

		//モデルパーツの描画
		m_pMesh->DrawSubset(nCntMat);
	}

	//保持していたマテリアルを元に戻す
	pDevice->SetMaterial(&matDef);
}

//==============================================================================================
// 平面投影
//==============================================================================================
void CObjectX::DrawShadow()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	D3DMATERIAL9 matDef;		// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;			// マテリアルデータへのポインタ
	D3DXMATRIX mtxShadow;		// シャドウマトリックス
	D3DXPLANE planeField;		// 平面
	D3DXVECTOR3 pos, normal;

	// アンビエントを無効にする
	CApplication::GetRenderer()->GetDevice()->SetRenderState(D3DRS_AMBIENT, 0);

	// シャドウマトリックスの初期化
	D3DXMatrixIdentity(&mtxShadow);

	// ライトの取得
	CLight *pLight = CApplication::GetLight();

	// ライトの方向
	D3DXVECTOR3 vecDir = pLight->GetLight().Direction;

	D3DXVECTOR4 vecLight = D3DXVECTOR4(-vecDir.x, -vecDir.y, -vecDir.z, 0.0f);

	// 位置の設定
	pos = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	// 法線の設定
	normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// 平面の作成
	D3DXPlaneFromPointNormal(&planeField, &pos, &normal);

	// ライトと平面から影行列を作成
	D3DXMatrixShadow(&mtxShadow, &vecLight, &planeField);
	D3DXMatrixMultiply(&mtxShadow, &m_mtxWorld, &mtxShadow);

	// シャドウマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

	// 現在のマテリアル保持
	pDevice->GetMaterial(&matDef);

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	// テクスチャの設定
	pDevice->SetTexture(0, NULL);

	for (int nCnt = 0; nCnt < (int)m_nNumMat; nCnt++)
	{
		// マテリアル情報の設定
		D3DMATERIAL9 matD3D = pMat[nCnt].MatD3D;

		// 色の設定
		matD3D.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		matD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

		// マテリアルの設定
		pDevice->SetMaterial(&matD3D);

		// モデルパーツの描画
		m_pMesh->DrawSubset(nCnt);
	}

	// 保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);

	// アンビエントを戻す
	CApplication::GetRenderer()->GetDevice()->SetRenderState(D3DRS_AMBIENT, 0xffffffff);
}

//==============================================================================================
// ステンシルバッファの設定
//==============================================================================================
void CObjectX::Stencil()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// ステンシルバッファ=>有効
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

	// ステンシルバッファと比較する参照値設定=>ref
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);

	// ステンシルバッファの値に対してのマスク設定=>0xff(すべて真)
	pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);

	// ステンシルテストの比較方法設定=>
	// 参照値 >= ステンシルバッファの参照値なら合格
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);	// GREATEREQUAL:>=(以上)	EQUAL:==(等しい)

	// ステンシルテキストの結果に対しての反映設定
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);	// PASS:Zテスト＆ステンシルテスト成功		REPLACE:置き換え
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);		// FAIL:Zテスト＆ステンシルテスト失敗		KEEP:変更なし
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);		// ZFAIL:Zテストのみ失敗					INCR:+1
}

//==============================================================================================
// 生成処理
//==============================================================================================
CObjectX *CObjectX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, const char* name)
{
	CObjectX *pObjectX = nullptr;

	pObjectX = new CObjectX;

	if (pObjectX != nullptr)
	{
		pObjectX->SetXFileName(name);
		pObjectX->SetPos(pos);
		pObjectX->SetRot(rot);
		pObjectX->SetSize(size);
		pObjectX->Init();
	}

	return pObjectX;
}