//==============================================================================================
//
// �A�v���P�[�V����
// �y�c����
//
//==============================================================================================

//**********************************************************************************************
// �C���N���[�h
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
// �ÓI�����o�ϐ��̐錾
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
// �R���X�g���N�^
//==============================================================================================
CApplication::CApplication()
{
}

//==============================================================================================
// �f�X�g���N�^
//==============================================================================================
CApplication::~CApplication()
{
}

//==============================================================================================
// ����������
//==============================================================================================
HRESULT CApplication::Init(HINSTANCE hInstance, HWND hWnd)
{
	// �N���X�̐���
	m_pInputkeyboard = new CInputkeyboard;		// �L�[�{�[�h
	m_pRenderer = new CRenderer;				// �����_�����O
	m_pTexture = new CTexture;					// �e�N�X�`��
	m_pLight = new CLight;						// ���C�g

	// ����������
	m_pInputkeyboard->Init(hInstance, hWnd);	// �L�[�{�[�h
	m_pRenderer->Init(hWnd, TRUE);				// �����_�����O
	m_pLight->Init();							// ���C�g

	// �Q�[�����[�h
	m_mode = MODE_GAME;

	// ���[�h�̒��
	SetMode(m_mode);

	return S_OK;
}

//==============================================================================================
// �I������
//==============================================================================================
void CApplication::Uninit()
{
	// �����_�����O�̏I��
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	// �L�[�{�[�h�̏I��
	if (m_pInputkeyboard != nullptr)
	{
		m_pInputkeyboard->Uninit();
		delete m_pInputkeyboard;
		m_pInputkeyboard = nullptr;
	}

	//�e�N�X�`���̏I��
	if (m_pTexture != nullptr)
	{
		m_pTexture->ReleaseAll();
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	CObject::ReleaseAll();
}

//==============================================================================================
// �X�V����
//==============================================================================================
void CApplication::Update()
{
	m_pInputkeyboard->Update();

	m_pRenderer->Update();
}

//==============================================================================================
// �`�揈��
//==============================================================================================
void CApplication::Draw()
{
	m_pRenderer->Draw();
}

//==============================================================================================
// ���[�h�̐ݒ�
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

	// �w��̃��[�h�̐ݒ�
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