//==============================================================================================
//
//���f���̏���[model.h]
//Author�F�y�c����
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

	void DrawShadow();		// �e
	void Stencil();			// �X�e���V��
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

	static const int m_nMax_Model = 128;	// �I�u�W�F�N�gX�̍ő吔
private:
	D3DXVECTOR3 m_pos;				// �ʒu
	D3DXVECTOR3 m_posOld;			// �O��̈ʒu
	D3DXVECTOR3 m_rot;				// ����
	D3DXVECTOR3 m_Initrot;			// �ŏ��̌���
	D3DXVECTOR3 m_Size;				// �T�C�Y
	D3DXVECTOR3 m_vtxMinModel;		// ���_�̍ŏ��l
	D3DXVECTOR3 m_vtxMaxModel;		// ���_�̍ő�l
	D3DXVECTOR3 m_vecDir;			// �v���C���[�̕����x�N�g��
	LPD3DXBUFFER m_pBuffMat;		// �}�e���A�����ւ̃|�C���^
	LPD3DXMESH m_pMesh;				// ���b�V�����ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;			// ���[���h�}�g���b�N�X
	DWORD m_nNumMat;				// �}�e���A�����̐�
	D3DXMATRIX m_mtxRot;			// ��]�}�g���b�N�X
	const char *m_FileName;			// �t�@�C���̖��O
};

#endif // !_OBJECTX_H_