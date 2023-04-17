//==============================================
//
//�J�����̏���[camera.cpp]
//Author�F�y�c����
//
//==============================================
#include"camera.h"
#include"inputkeyboard.h"
#include"application.h"
#include"game.h"
#include"title.h"

//==============================================
//�R���X�g���N�^
//==============================================
CCamera::CCamera()
{

}

//==============================================
//�f�X�g���N�^
//==============================================
CCamera::~CCamera()
{

}

//==============================================
//�J�����̏���������
//==============================================
void CCamera::Init(void)
{
	//���_�E�����_�E�������ݒ肷��
	m_posV = D3DXVECTOR3(40.0f, 100.0f, -200.0f);		// ���_(�I�t�Z�b�g)
	m_InitposV = D3DXVECTOR3(40.0f, 100.0f, -200.0f);	// ���_(�I�t�Z�b�g)
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 1000.0f);			// �����_(�I�t�Z�b�g)
	m_InitposR = D3DXVECTOR3(0.0f, 0.0f, 1000.0f);		// �����_(�I�t�Z�b�g)
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �p�x
	m_fRotSpeed = 0.03f;							// ��]���x
	m_nShiftGoalCount = 250;
	m_nGoalCount = 100;
	m_fPlayerDistance = 0.0f;
	m_CPos = { 0.0f,0.0f,0.0f };
}

//==============================================
//�J�����̏I������
//==============================================
void CCamera::Uninit(void)
{

}

//==============================================
//�J�����̍X�V����
//==============================================
void CCamera::Update(void)
{
	// �s����g�����J��������
	Matrix();

	// �J�����̈ړ�
	Move();
}

//==============================================
// �J�����̃Z�b�g����
//==============================================
void CCamera::SetCamera(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	// �r���[�}�g���b�N�X�̐���
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_WorldCameraPosV,
		&m_WorldCameraPosR,
		&m_vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X�̐���
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)1280 / (float)720,
		10.0f,
		10000.0f);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}

//==============================================
// �s����g�����J��������
//==============================================
void CCamera::Matrix()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;		//�v�Z�p�̃}�g���b�N�X

	// ���[���h�}�g���b�N�X
	D3DXMatrixIdentity(&m_mtxWorld);

	// �s�����]�ɔ��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �s��Ɉړ��𔽉f(�v���C���[�̈ʒu)
	D3DXMatrixTranslation(&mtxTrans, m_CPos.x, m_CPos.y, m_CPos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	D3DXVec3TransformCoord(&m_WorldCameraPosV, &m_posV, &m_mtxWorld);
	D3DXVec3TransformCoord(&m_WorldCameraPosR, &m_posR, &m_mtxWorld);

	// ���_����v���C���[�܂ł̋���
	if (m_fPlayerDistance == 0.0f)
	{
		m_fPlayerDistance = sqrtf((m_CPos.x - m_WorldCameraPosV.x) * (m_CPos.x - m_WorldCameraPosV.x)
			+ (m_CPos.z - m_WorldCameraPosV.z) * (m_CPos.z - m_WorldCameraPosV.z));
	}
}

//==============================================
// �J�����̈ړ�
//==============================================
void CCamera::Move()
{
	// �L�[�{�[�h�̏��
	CInputkeyboard *pKeyboard = CApplication::GetInputKeyboard();

	if (!m_bGoalOpen)
	{
		// �J�����̈ړ�
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
		{// ���O
			m_CPos.x -= sinf(m_rot.y + D3DX_PI * 3 / 4) * 3;
			m_CPos.z -= cosf(m_rot.y + D3DX_PI * 3 / 4) * 3;
		}
		else if (pKeyboard->GetKeyboardPress(DIK_D))
		{// �E�O
			m_CPos.x += sinf(m_rot.y + D3DX_PI * 1 / 4) * 3;
			m_CPos.z += cosf(m_rot.y + D3DX_PI * 1 / 4) * 3;
		}
		else
		{// �O
			m_CPos.x += sinf(m_rot.y) * 3;
			m_CPos.z += cosf(m_rot.y) * 3;
		}
	}
	else if (pKeyboard->GetKeyboardPress(DIK_S))
	{
		if (pKeyboard->GetKeyboardPress(DIK_A))
		{// ����
			m_CPos.x -= sinf(m_rot.y + D3DX_PI * 1 / 4) * 3;
			m_CPos.z -= cosf(m_rot.y + D3DX_PI * 1 / 4) * 3;
		}
		else if (pKeyboard->GetKeyboardPress(DIK_D))
		{// �E��
			m_CPos.x += sinf(m_rot.y + D3DX_PI * 3 / 4) * 3;
			m_CPos.z += cosf(m_rot.y + D3DX_PI * 3 / 4) * 3;
		}
		else
		{// ��
			m_CPos.x -= sinf(m_rot.y) * 3;
			m_CPos.z -= cosf(m_rot.y) * 3;
		}
	}
	else if (pKeyboard->GetKeyboardPress(DIK_A))
	{// ��
		m_CPos.x -= sinf(m_rot.y + D3DX_PI * 1 / 2) * 3;
		m_CPos.z -= cosf(m_rot.y + D3DX_PI * 1 / 2) * 3;
	}
	else if (pKeyboard->GetKeyboardPress(DIK_D))
	{// �E
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

	// �p�x�̐��K��
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2;
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2;
	}
}