////==============================================================================================
////
//// �v���C���[�@�@�@player.h
//// �y�c����
////
////==============================================================================================
//#ifndef _PLAYER_H_
//#define _PLAYER_H_
//
//#include"Object.h"
//
//class CShadow;
//class CModel;
//
//class CPlayer : public CObject
//{
//public:
//	CPlayer();
//	~CPlayer() override;
//
//	HRESULT Init() override;
//	void Uninit() override;
//	void Update() override;
//	void Draw() override;
//
//	static CPlayer *Create(D3DXVECTOR3 pos);
//
//	void Move();			// �ړ�����
//	void Death();			// ���S
//	void SetMotionData(int maxkey, int key, int parts, int motion, int frame, D3DXVECTOR3 pos, D3DXVECTOR3 rot, bool loop);	// ���[�V�����l�̓ǂݍ���
//	void Motion();										// ���[�V�����̐ݒ�
//	void ChangeMotion(int nummotion);					// ���[�V�����̐؂�ւ�
//	CModel *SetModel(int index, int parent, D3DXVECTOR3 pos, D3DXVECTOR3 rot, char *Xfilename);		// ���f���p�[�c�̐ݒ�
//
//	void SetPos(D3DXVECTOR3 pos) { m_Pos = pos; }
//
//	D3DXVECTOR3 GetPos() { return m_Pos; }
//	D3DXVECTOR3 GetPosOld() { return m_PosOld; }
//	D3DXVECTOR3 GetRot() { return m_Rot; }
//	D3DXVECTOR3 GetSizeMin() { return m_SizeMin; }
//	D3DXVECTOR3 GetSizeMax() { return m_SizeMax; }
//	float GetRadius() { return m_fRadius; }
//
//private:
//	D3DXVECTOR3 m_Pos;			// �ʒu
//	D3DXVECTOR3 m_PosOld;		// �ߋ��̈ʒu
//	D3DXVECTOR3 m_InitPos;		// �����ʒu
//	D3DXVECTOR3 m_Rot;			// ���݂̊p�x
//	D3DXVECTOR3 m_RotDest;		// �ړI�̊p�x
//	D3DXVECTOR3 m_SizeMin;		// ���_�̍ŏ��l
//	D3DXVECTOR3 m_SizeMax;		// ���_�̍ő�l
//	D3DXVECTOR3 m_CPosV;		// �J�����̎��_�̊i�[��
//	int m_nLife;				// �̗�
//	float m_fRadius;			// ���a
//	float m_fSpeed;				// �ړ����x
//	float m_fRotSpeed;			// ��]�̃X�s�[�h
//	float m_fCameraDis;			// �J�����Ƃ̋���
//	bool m_bDeath;				// ���S������
//};
//
//#endif // !_PLAYER_H_
