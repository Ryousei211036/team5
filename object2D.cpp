//==============================================================================================
//
// オブジェクト　　　object2D.cpp
// 土田凌聖
//
//==============================================================================================

//**********************************************************************************************
// インクルード
//**********************************************************************************************
#include"main.h"
#include"object2D.h"
#include"renderer.h"
#include"application.h"
#include"inputkeyboard.h"

//==============================================================================================
// コンストラクタ
//==============================================================================================
CObject2D::CObject2D(int nPriority) : CObject(nPriority)
{
	m_fAngle = 0.0f;		// 対角線の角度
	m_fRot = 0.0f;			// ポリゴンの角度
	m_pVtxBuff = NULL;
	m_Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_texture = CTexture::TEXTURE_NONE;
}

//==============================================================================================
// デストラクタ
//==============================================================================================
CObject2D::~CObject2D()
{
}

//==============================================================================================
// ポリゴンの初期化
//==============================================================================================
HRESULT CObject2D::Init()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//頂点バッファを取得
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	m_texture = CTexture::TEXTURE_NONE;

	// 頂点バッファ
	VERTEX_2D *pVtx;

	// 頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos.x = m_Pos.x + sinf(m_fRot + (-D3DX_PI + m_fAngle)) * m_fWidth;
	pVtx[0].pos.y = m_Pos.y + cosf(m_fRot + (-D3DX_PI + m_fAngle)) * m_fHeight;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_Pos.x + sinf(m_fRot + (D3DX_PI - m_fAngle)) * m_fWidth2;
	pVtx[1].pos.y = m_Pos.y + cosf(m_fRot + (D3DX_PI - m_fAngle)) * m_fHeight;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_Pos.x + sinf(m_fRot + (m_fAngle * -1.0f)) * m_fWidth;
	pVtx[2].pos.y = m_Pos.y + cosf(m_fRot + (m_fAngle * -1.0f)) * m_fHeight;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_Pos.x + sinf(m_fRot + (m_fAngle * 1.0f)) * m_fWidth2;
	pVtx[3].pos.y = m_Pos.y + cosf(m_fRot + (m_fAngle * 1.0f)) * m_fHeight;
	pVtx[3].pos.z = 0.0f;

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = m_Col;
	pVtx[1].col = m_Col;
	pVtx[2].col = m_Col;
	pVtx[3].col = m_Col;

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//==============================================================================================
// ポリゴンの終了
//==============================================================================================
void CObject2D::Uninit()
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	Release();
}

//==============================================================================================
// ポリゴンの更新
//==============================================================================================
void CObject2D::Update()
{
	// 対角線の角度を算出する
	m_fAngle = (float)atan2(1.0f, 1.0f);

	// 頂点バッファ
	VERTEX_2D *pVtx;

	// 頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//ポリゴンの更新
	pVtx[0].pos.x = m_Pos.x + sinf(m_fRot + (-D3DX_PI + m_fAngle)) * m_fWidth;
	pVtx[0].pos.y = m_Pos.y + cosf(m_fRot + (-D3DX_PI + m_fAngle)) * m_fHeight;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_Pos.x + sinf(m_fRot + (D3DX_PI - m_fAngle)) * m_fWidth2;
	pVtx[1].pos.y = m_Pos.y + cosf(m_fRot + (D3DX_PI - m_fAngle)) * m_fHeight2;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_Pos.x + sinf(m_fRot + (m_fAngle * -1.0f)) * m_fWidth;
	pVtx[2].pos.y = m_Pos.y + cosf(m_fRot + (m_fAngle * -1.0f)) * m_fHeight;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_Pos.x + sinf(m_fRot + (m_fAngle * 1.0f)) * m_fWidth2;
	pVtx[3].pos.y = m_Pos.y + cosf(m_fRot + (m_fAngle * 1.0f)) * m_fHeight2;
	pVtx[3].pos.z = 0.0f;

	// 色の更新
	pVtx[0].col = m_Col;
	pVtx[1].col = m_Col;
	pVtx[2].col = m_Col;
	pVtx[3].col = m_Col;

	// 頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//==============================================================================================
// ポリゴンの描画
//==============================================================================================
void CObject2D::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// ステンシルバッファの設定
	//Stencil();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	 //頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	CTexture *pTexture = CApplication::GetTexture();

	//テクスチャの設定
	pDevice->SetTexture(0, pTexture->GetTexture(m_texture));

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,		//頂点情報の先頭アドレス
		2);		//プリミティブの数

	// ステンシルバッファ=>無効
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
}

//==============================================================================================
// ステンシルバッファの設定
//==============================================================================================
void CObject2D::Stencil()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// ステンシルバッファ=>有効
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

	// ステンシルバッファと比較する参照値設定=>ref
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x02);

	// ステンシルバッファの値に対してのマスク設定=>0xff(すべて真)
	pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);

	// ステンシルテストの比較方法設定=>
	// 参照値 >= ステンシルバッファの参照値なら合格
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);	// GREATEREQUAL:>=(以上)	EQUAL:==(等しい)

	// ステンシルテキストの結果に対しての反映設定
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);	// PASS:Zテスト＆ステンシルテスト成功		REPLACE:置き換え
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);		// FAIL:Zテスト＆ステンシルテスト失敗		KEEP:変更なし
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);		// ZFAIL:Zテストのみ失敗					INCR:+1
}

//==============================================================================================
// 位置の設定
//==============================================================================================
void CObject2D::Setposition(D3DXVECTOR3 pos)
{
	m_Pos = pos;
}

//==============================================================================================
// サイズの設定
//==============================================================================================
void CObject2D::SetSize(float width, float height)
{
	m_fWidth = width;
	m_fWidth2 = width;
	m_fHeight = height;
	m_fHeight2 = height;
}

//==============================================================================================
// 角度の設定
//==============================================================================================
void CObject2D::Setrot(float rot)
{
	m_fRot = rot;
}

//==============================================================================================
// テクスチャ座標の設定
//==============================================================================================
void CObject2D::SetTexPos(float top, float row, float right, float left)
{
	// 頂点バッファ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(left, top);
	pVtx[1].tex = D3DXVECTOR2(right, top);
	pVtx[2].tex = D3DXVECTOR2(left, row);
	pVtx[3].tex = D3DXVECTOR2(right, row);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//==============================================================================================
// アニメーションの設定
//==============================================================================================
void CObject2D::AnimTexture(int nPattern, int nPatternMax)
{
	VERTEX_2D *pVtx;			// 頂点情報へのポインタ

	float nDivisionRate = 1.0f / nPatternMax;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(nPattern * nDivisionRate, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((nPattern + 1) * nDivisionRate, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(nPattern * nDivisionRate, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((nPattern + 1) * nDivisionRate, 1.0f);

	// 頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//==============================================================================================
// テクスチャの設定
//==============================================================================================
void CObject2D::SetTexture(CTexture::TEXTURE texture)
{
	m_texture = texture;
}

//==============================================================================================
// 消える設定
//==============================================================================================
bool CObject2D::SetDisappear(float size, float alpha, float sizespeed, float alphaspeed)
{
	float fSize, fSize1, fSize2;
	fSize = m_fWidth;
	fSize1 = m_fWidth2;
	fSize2 = m_fHeight;

	if (fSize + size >= m_fWidth)
	{
		m_fWidth += sizespeed;		// サイズの加算
		m_fWidth2 += sizespeed;
		m_fHeight += sizespeed;
	}
	if (m_Col.a >= alpha)
	{
		m_Col.a -= alphaspeed;		// α値の減算
	}
	if (m_Col.a <= 0)
	{
		return true;
	}

	return false;
}

//==============================================================================================
// 色の設定
//==============================================================================================
void CObject2D::SetCol(D3DXCOLOR col)
{
	m_Col = col;
}

//==============================================================================================
// 生成処理
//==============================================================================================
CObject2D *CObject2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CObject2D *pObject2D = nullptr;

	pObject2D = new CObject2D(3);

	if (pObject2D != nullptr)
	{
		pObject2D->SetSize(size.x, size.y);
		pObject2D->Setposition(pos);
		pObject2D->Init();
	}

	return pObject2D;
}