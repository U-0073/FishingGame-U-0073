#pragma once
#include"../../System/FrameBase/CSceneBase.h"
#define path "Resource/Texture/"

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
	LPDIRECT3DTEXTURE9 ringTex;
	KdMatrix ringMat;

	//ノーツ
	LPDIRECT3DTEXTURE9 notesTex;
	KdMatrix notesMat;
	float scale;

	//判定文字
	LPDIRECT3DTEXTURE9 judgeTex;
	LPDIRECT3DTEXTURE9 resultTex = nullptr;
	KdMatrix judgeMat;

	LPDIRECT3DTEXTURE9 backTex;
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

	//判定用画像のポジション設定用関数
	const void SetPos(const KdVec3& Vec){
		judgeMat._41 = Vec.x;
		judgeMat._42 = Vec.y;
		judgeMat._43 = Vec.z;
	}

	std::shared_ptr<SoundBase> m_pSound = nullptr;

};