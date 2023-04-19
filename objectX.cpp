//==============================================================================================
//
// �I�u�W�F�N�gX�@�@�@objectX.cpp
// �y�c����
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
// �R���X�g���N�^
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
// �f�X�g���N�^
//==============================================================================================
CObjectX::~CObjectX()
{
}

//==============================================================================================
// ����������
//==============================================================================================
HRESULT CObjectX::Init()
{
	D3DXMatrixIdentity(&m_mtxRot);

	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(m_FileName,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_nNumMat,
		&m_pMesh);

	int nNumVtx;		//���_��
	DWORD sizeFVF;		//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^

	//���_���̎擾
	nNumVtx = m_pMesh->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	//���_�o�b�t�@�̃��b�N
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		//���_���W�̑��
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		//�ŏ��l�̎擾
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

		//�ő�l�̎擾
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

		//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		pVtxBuff += sizeFVF;
	}

	//���_�o�b�t�@�̃A�����b�N
	m_pMesh->UnlockVertexBuffer();

	return S_OK;
}

//==============================================================================================
// �I������
//==============================================================================================
void CObjectX::Uninit()
{
	for (int nCnt = 0; nCnt < m_nMax_Model; nCnt++)
	{
		//���b�V���̔j��
		if (m_pMesh != NULL)
		{
			m_pMesh->Release();
			m_pMesh = NULL;
		}

		//�}�e���A���̔j��
		if (m_pBuffMat != NULL)
		{
			m_pBuffMat->Release();
			m_pBuffMat = NULL;
		}
	}

	Release();
}

//==============================================================================================
//�X�V����
//==============================================================================================
void CObjectX::Update()
{
	
}

//==============================================================================================
// �`�揈��
//==============================================================================================
void CObjectX::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans, mtxScaling;		//�v�Z�p�̃}�g���b�N�X
	D3DMATERIAL9 matDef;		//���݂̃}�e���A���̕ۑ��p
	D3DXMATERIAL *pMat;			//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXQUATERNION m_quat;		// �N�H�[�^�j�I��

	//���[���h�}�g���b�N�X
	D3DXMatrixIdentity(&m_mtxWorld);

	// �T�C�Y�𔽉f
	D3DXMatrixScaling(&mtxScaling, m_Size.x, m_Size.y, m_Size.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScaling);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&m_mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���ʓ��e
	//DrawShadow();

	// �X�e���V���o�b�t�@�̐ݒ�
	Stencil();

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A����ێ�
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	// �X�e���V���p�̕`��
	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//���f���p�[�c�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}

	// �X�e���V���o�b�t�@=>����
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);

	// ���ʂ̕`��
	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		// �}�e���A�����̐ݒ�
		D3DMATERIAL9 matD3D = pMat[nCntMat].MatD3D;
		
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&matD3D);

		//���f���p�[�c�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}

	//�ێ����Ă����}�e���A�������ɖ߂�
	pDevice->SetMaterial(&matDef);
}

//==============================================================================================
// ���ʓ��e
//==============================================================================================
void CObjectX::DrawShadow()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	D3DMATERIAL9 matDef;		// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;			// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATRIX mtxShadow;		// �V���h�E�}�g���b�N�X
	D3DXPLANE planeField;		// ����
	D3DXVECTOR3 pos, normal;

	// �A���r�G���g�𖳌��ɂ���
	CApplication::GetRenderer()->GetDevice()->SetRenderState(D3DRS_AMBIENT, 0);

	// �V���h�E�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxShadow);

	// ���C�g�̎擾
	CLight *pLight = CApplication::GetLight();

	// ���C�g�̕���
	D3DXVECTOR3 vecDir = pLight->GetLight().Direction;

	D3DXVECTOR4 vecLight = D3DXVECTOR4(-vecDir.x, -vecDir.y, -vecDir.z, 0.0f);

	// �ʒu�̐ݒ�
	pos = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	// �@���̐ݒ�
	normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// ���ʂ̍쐬
	D3DXPlaneFromPointNormal(&planeField, &pos, &normal);

	// ���C�g�ƕ��ʂ���e�s����쐬
	D3DXMatrixShadow(&mtxShadow, &vecLight, &planeField);
	D3DXMatrixMultiply(&mtxShadow, &m_mtxWorld, &mtxShadow);

	// �V���h�E�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

	// ���݂̃}�e���A���ێ�
	pDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	for (int nCnt = 0; nCnt < (int)m_nNumMat; nCnt++)
	{
		// �}�e���A�����̐ݒ�
		D3DMATERIAL9 matD3D = pMat[nCnt].MatD3D;

		// �F�̐ݒ�
		matD3D.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		matD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&matD3D);

		// ���f���p�[�c�̕`��
		m_pMesh->DrawSubset(nCnt);
	}

	// �ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);

	// �A���r�G���g��߂�
	CApplication::GetRenderer()->GetDevice()->SetRenderState(D3DRS_AMBIENT, 0xffffffff);
}

//==============================================================================================
// �X�e���V���o�b�t�@�̐ݒ�
//==============================================================================================
void CObjectX::Stencil()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// �X�e���V���o�b�t�@=>�L��
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

	// �X�e���V���o�b�t�@�Ɣ�r����Q�ƒl�ݒ�=>ref
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);

	// �X�e���V���o�b�t�@�̒l�ɑ΂��Ẵ}�X�N�ݒ�=>0xff(���ׂĐ^)
	pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);

	// �X�e���V���e�X�g�̔�r���@�ݒ�=>
	// �Q�ƒl >= �X�e���V���o�b�t�@�̎Q�ƒl�Ȃ獇�i
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);	// GREATEREQUAL:>=(�ȏ�)	EQUAL:==(������)

	// �X�e���V���e�L�X�g�̌��ʂɑ΂��Ă̔��f�ݒ�
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);	// PASS:Z�e�X�g���X�e���V���e�X�g����		REPLACE:�u������
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);		// FAIL:Z�e�X�g���X�e���V���e�X�g���s		KEEP:�ύX�Ȃ�
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);		// ZFAIL:Z�e�X�g�̂ݎ��s					INCR:+1
}

//==============================================================================================
// ��������
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