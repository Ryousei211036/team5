////==============================================================================================
////
//// プレイヤー　　　player.h
//// 土田凌聖
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
//	void Move();			// 移動処理
//	void Death();			// 死亡
//	void SetMotionData(int maxkey, int key, int parts, int motion, int frame, D3DXVECTOR3 pos, D3DXVECTOR3 rot, bool loop);	// モーション値の読み込み
//	void Motion();										// モーションの設定
//	void ChangeMotion(int nummotion);					// モーションの切り替え
//	CModel *SetModel(int index, int parent, D3DXVECTOR3 pos, D3DXVECTOR3 rot, char *Xfilename);		// モデルパーツの設定
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
//	D3DXVECTOR3 m_Pos;			// 位置
//	D3DXVECTOR3 m_PosOld;		// 過去の位置
//	D3DXVECTOR3 m_InitPos;		// 初期位置
//	D3DXVECTOR3 m_Rot;			// 現在の角度
//	D3DXVECTOR3 m_RotDest;		// 目的の角度
//	D3DXVECTOR3 m_SizeMin;		// 頂点の最小値
//	D3DXVECTOR3 m_SizeMax;		// 頂点の最大値
//	D3DXVECTOR3 m_CPosV;		// カメラの視点の格納先
//	int m_nLife;				// 体力
//	float m_fRadius;			// 半径
//	float m_fSpeed;				// 移動速度
//	float m_fRotSpeed;			// 回転のスピード
//	float m_fCameraDis;			// カメラとの距離
//	bool m_bDeath;				// 死亡したか
//};
//
//#endif // !_PLAYER_H_
