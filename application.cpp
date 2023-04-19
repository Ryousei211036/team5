//==============================================================================================
//
// アプリケーション
// 土田凌聖
//
//==============================================================================================

//**********************************************************************************************
// インクルード
//**********************************************************************************************
#include"application.h"
#include"inputkeyboard.h"
#include"object.h"
#include"camera.h"
#include"title.h"
#include"game.h"
#include"result.h"
#include"texture.h"
#include"light.h"

//**********************************************************************************************
// 静的メンバ変数の宣言
//**********************************************************************************************
CTitle *CApplication::m_pTitle = nullptr;
CGame *CApplication::m_pGame = nullptr;
CResult *CApplication::m_pResult = nullptr;
CRenderer *CApplication::m_pRenderer = nullptr;
CInputkeyboard *CApplication::m_pInputkeyboard = nullptr;
CApplication::MODE CApplication::m_mode = MODE_NONE;
CObject *CApplication::m_pGameMode = nullptr;
CTexture *CApplication::m_pTexture = nullptr;
CLight *CApplication::m_pLight = nullptr;

//==============================================================================================
// コンストラクタ
//==============================================================================================
CApplication::CApplication()
{
}

//==============================================================================================
// デストラクタ
//==============================================================================================
CApplication::~CApplication()
{
}

//==============================================================================================
// 初期化処理
//==============================================================================================
HRESULT CApplication::Init(HINSTANCE hInstance, HWND hWnd)
{
	// クラスの生成
	m_pInputkeyboard = new CInputkeyboard;		// キーボード
	m_pRenderer = new CRenderer;				// レンダリング
	m_pTexture = new CTexture;					// テクスチャ
	m_pLight = new CLight;						// ライト

	// 初期化処理
	m_pInputkeyboard->Init(hInstance, hWnd);	// キーボード
	m_pRenderer->Init(hWnd, TRUE);				// レンダリング
	m_pLight->Init();							// ライト

	// ゲームモード
	m_mode = MODE_GAME;

	// モードの定設
	SetMode(m_mode);

	return S_OK;
}

//==============================================================================================
// 終了処理
//==============================================================================================
void CApplication::Uninit()
{
	// レンダリングの終了
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	// キーボードの終了
	if (m_pInputkeyboard != nullptr)
	{
		m_pInputkeyboard->Uninit();
		delete m_pInputkeyboard;
		m_pInputkeyboard = nullptr;
	}

	//テクスチャの終了
	if (m_pTexture != nullptr)
	{
		m_pTexture->ReleaseAll();
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	CObject::ReleaseAll();
}

//==============================================================================================
// 更新処理
//==============================================================================================
void CApplication::Update()
{
	m_pInputkeyboard->Update();

	m_pRenderer->Update();
}

//==============================================================================================
// 描画処理
//==============================================================================================
void CApplication::Draw()
{
	m_pRenderer->Draw();
}

//==============================================================================================
// モードの設定
//==============================================================================================
void CApplication::SetMode(MODE mode)
{
	if (m_pGameMode != nullptr)
	{
		m_pGameMode->Uninit();
		m_pGameMode = nullptr;

		CObject::ReleaseAll();
	}

	m_mode = mode;

	// 指定のモードの設定
	switch (m_mode)
	{
	case CApplication::MODE_TITLE:
		m_pGameMode = CTitle::Create();
		break;

	case CApplication::MODE_GAME:
		m_pGameMode = CGame::Create();
		break;

	case CApplication::MODE_RESULT:
		m_pGameMode = CResult::Create();
		break;

	default:
		break;
	}
}