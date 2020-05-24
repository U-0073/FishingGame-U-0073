#pragma once
#include"../../System/FrameBase/CSceneBase.h"

class CGameProc;

class CGameScene : public CSceneBase
{
public:
	CGameScene();
	~CGameScene();

	void Init()override;
	int Update()override;
	void Draw2D()override;
	void Draw3D()override;
	int GetID()override { return GAME; };
	void End()override;
private:
	//固定枠
	std::shared_ptr<LPDIRECT3DTEXTURE9> ringTex = nullptr;
	KdMatrix ringMat;


	//ノーツ
	std::shared_ptr<LPDIRECT3DTEXTURE9> notesTex = nullptr;
	KdMatrix notesMat;
	float scale;

	//判定文字
	std::shared_ptr<LPDIRECT3DTEXTURE9> judgeTex = nullptr;
	std::shared_ptr<LPDIRECT3DTEXTURE9> resultTex = nullptr;
	KdMatrix judgeMat;

	std::shared_ptr<LPDIRECT3DTEXTURE9> backTex = nullptr;
	KdMatrix backMat;

	float speed;
	int size;
	int clickNum;
	bool keyFlg;
	int frame;
	int judgeFlg;

	//マウス関連
	POINT Mouse;
	KdVec3 clickPos;
	float len;
	bool Check;
	bool frameStopper;

	int MusicChoise;

	//判定用画像のポジション設定用関数
	const void SetPos(const KdVec3& Vec) {
		judgeMat._41 = Vec.x;
		judgeMat._42 = Vec.y;
		judgeMat._43 = Vec.z;
	}


	KdVec3 score;
	const void SetScore(const int Excellent, const int Miss)
	{
	}


	//スコアチェッカー
	int clickCNT;
	int Excellent;
	int Miss;

	//何の魚か
	std::string name;

	std::shared_ptr<SoundBase> m_pSound = nullptr;

};