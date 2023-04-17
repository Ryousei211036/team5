//==============================================================================================
//
// �I�u�W�F�N�g�@�@�@object.h
// Author : �y�c����
//
//==============================================================================================
#ifndef _OBJECT_H_
#define	_OBJECT_H_

#include <d3dx9.h>

#define	MAX_PRI			(6)			// �D�揇�ʂ̍ő吔

class CObject
{
public:
	// �I�u�W�F�N�g�̎��
	enum EObjType
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_MODE,		// �Q�[�����[�h
		OBJTYPE_MAX
	};

	CObject(int nPriority = 3);
	virtual ~CObject();

	virtual HRESULT Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	static void ReleaseAll();
	static void UpdateAll();
	static void DrawAll();

	void Release();
	void Death(int nPriority);
	float Distance(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2);		// ��̈ʒu�̋���

	CObject *GetNext() { return m_pNext; }
	static CObject *GetTop(int Pri) { return m_pTop[Pri]; }
	virtual EObjType GetObjType() { return OBJTYPE_NONE; }		// �I�u�W�F�N�g�^�C�v�̎擾
	bool GetDeathFlag() { return m_bDeath; }

private:
	int m_nPriority;
	CObject *m_pPrev;						// ��O�̃I�u�W�F�N�g�ւ̃|�C���^
	CObject *m_pNext;						// ���̃I�u�W�F�N�g�ւ̃|�C���^
	static CObject *m_pTop[MAX_PRI];		// �擪�̃I�u�W�F�N�g�̂ւ̃|�C���^
	static CObject *m_pCurrent[MAX_PRI];	// ����(��Ԍ��)�̃I�u�W�F�N�g�̂ւ̃|�C���^
	bool m_bDeath;							// ���S�t���O
};

#endif // !_OBJECT_H_
