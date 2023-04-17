//==============================================
//
//カメラの処理[camera.cpp]
//Author：土田凌聖
//
//==============================================
#include"camera.h"
#include"inputkeyboard.h"
#include"application.h"
#include"game.h"
#include"title.h"

//==============================================
//コンストラクタ
//==============================================
CCamera::CCamera()
{

}

//==============================================
//デストラクタ
//==============================================
CCamera::~CCamera()
{

}

//==============================================
//カメラの初期化処理
//==============================================
void CCamera::Init(void)
{
	//視点・注視点・上方向を設定する
	m_posV = D3DXVECTOR3(40.0f, 100.0f, -200.0f);		// 視点(オフセット)
	m_InitposV = D3DXVECTOR3(40.0f, 100.0f, -200.0f);	// 視点(オフセット)
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 1000.0f);			// 注視点(オフセット)
	m_InitposR = D3DXVECTOR3(0.0f, 0.0f, 1000.0f);		// 注視点(オフセット)
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 角度
	m_fRotSpeed = 0.03f;							// 回転速度
	m_nShiftGoalCount = 250;
	m_nGoalCount = 100;
	m_fPlayerDistance = 0.0f;
	m_CPos = { 0.0f,0.0f,0.0f };
}

//==============================================
//カメラの終了処理
//==============================================
void CCamera::Uninit(void)
{

}

//==============================================
//カメラの更新処理
//==============================================
void CCamera::Update(void)
{
	// 行列を使ったカメラ制御
	Matrix();

	// カメラの移動
	Move();
}

//==============================================
// カメラのセット処理
//==============================================
void CCamera::SetCamera(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	// ビューマトリックスの生成
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_WorldCameraPosV,
		&m_WorldCameraPosR,
		&m_vecU);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	// プロジェクションマトリックスの生成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)1280 / (float)720,
		10.0f,
		10000.0f);

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}

//==============================================
// 行列を使ったカメラ制御
//==============================================
void CCamera::Matrix()
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;		//計算用のマトリックス

	// ワールドマトリックス
	D3DXMatrixIdentity(&m_mtxWorld);

	// 行列を回転に反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 行列に移動を反映(プレイヤーの位置)
	D3DXMatrixTranslation(&mtxTrans, m_CPos.x, m_CPos.y, m_CPos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	D3DXVec3TransformCoord(&m_WorldCameraPosV, &m_posV, &m_mtxWorld);
	D3DXVec3TransformCoord(&m_WorldCameraPosR, &m_posR, &m_mtxWorld);

	// 視点からプレイヤーまでの距離
	if (m_fPlayerDistance == 0.0f)
	{
		m_fPlayerDistance = sqrtf((m_CPos.x - m_WorldCameraPosV.x) * (m_CPos.x - m_WorldCameraPosV.x)
			+ (m_CPos.z - m_WorldCameraPosV.z) * (m_CPos.z - m_WorldCameraPosV.z));
	}
}

//==============================================
// カメラの移動
//==============================================
void CCamera::Move()
{
	// キーボードの情報
	CInputkeyboard *pKeyboard = CApplication::GetInputKeyboard();

	if (!m_bGoalOpen)
	{
		// カメラの移動
		if (pKeyboard->GetKeyboardPress(DIK_RIGHT))
		{
			m_rot.y += m_fRotSpeed;
		}
		if (pKeyboard->GetKeyboardPress(DIK_LEFT))
		{
			m_rot.y -= m_fRotSpeed;
		}
	}

	if (pKeyboard->GetKeyboardPress(DIK_W))
	{
		if (CApplication::GetInputKeyboard()->GetKeyboardPress(DIK_A))
		{// 左前
			m_CPos.x -= sinf(m_rot.y + D3DX_PI * 3 / 4) * 3;
			m_CPos.z -= cosf(m_rot.y + D3DX_PI * 3 / 4) * 3;
		}
		else if (pKeyboard->GetKeyboardPress(DIK_D))
		{// 右前
			m_CPos.x += sinf(m_rot.y + D3DX_PI * 1 / 4) * 3;
			m_CPos.z += cosf(m_rot.y + D3DX_PI * 1 / 4) * 3;
		}
		else
		{// 前
			m_CPos.x += sinf(m_rot.y) * 3;
			m_CPos.z += cosf(m_rot.y) * 3;
		}
	}
	else if (pKeyboard->GetKeyboardPress(DIK_S))
	{
		if (pKeyboard->GetKeyboardPress(DIK_A))
		{// 左下
			m_CPos.x -= sinf(m_rot.y + D3DX_PI * 1 / 4) * 3;
			m_CPos.z -= cosf(m_rot.y + D3DX_PI * 1 / 4) * 3;
		}
		else if (pKeyboard->GetKeyboardPress(DIK_D))
		{// 右下
			m_CPos.x += sinf(m_rot.y + D3DX_PI * 3 / 4) * 3;
			m_CPos.z += cosf(m_rot.y + D3DX_PI * 3 / 4) * 3;
		}
		else
		{// 下
			m_CPos.x -= sinf(m_rot.y) * 3;
			m_CPos.z -= cosf(m_rot.y) * 3;
		}
	}
	else if (pKeyboard->GetKeyboardPress(DIK_A))
	{// 左
		m_CPos.x -= sinf(m_rot.y + D3DX_PI * 1 / 2) * 3;
		m_CPos.z -= cosf(m_rot.y + D3DX_PI * 1 / 2) * 3;
	}
	else if (pKeyboard->GetKeyboardPress(DIK_D))
	{// 右
		m_CPos.x += sinf(m_rot.y + D3DX_PI * 1 / 2) * 3;
		m_CPos.z += cosf(m_rot.y + D3DX_PI * 1 / 2) * 3;
	}
	else if (CApplication::GetInputKeyboard()->GetKeyboardPress(DIK_E))
	{
		m_CPos.y += 3;
	}
	else if (CApplication::GetInputKeyboard()->GetKeyboardPress(DIK_Q))
	{
		m_CPos.y -= 3;
	}
	else if (CApplication::GetInputKeyboard()->GetKeyboardPress(DIK_UP))
	{
		m_rot.x -= m_fRotSpeed;
	}
	else if (CApplication::GetInputKeyboard()->GetKeyboardPress(DIK_DOWN))
	{
		m_rot.x += m_fRotSpeed;
	}

	// 角度の正規化
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2;
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2;
	}
}