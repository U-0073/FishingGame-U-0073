#pragma once
#include"../System/FrameBase/CSceneBase.h"
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
	//å≈íËòg
	LPDIRECT3DTEXTURE9 ringTex;
	KdMatrix ringMat;
	//ÉmÅ[Éc
	LPDIRECT3DTEXTURE9 notesTex;
	KdMatrix notesMat;
	float scale;
	//îªíËï∂éö
	LPDIRECT3DTEXTURE9 judgeTex;
	LPDIRECT3DTEXTURE9 resultTex = nullptr;
	KdMatrix judgeMat;

	LPDIRECT3DTEXTURE9 backTex;
	KdMatrix backMat;

	float speed;
	int level;
	int size;
	int clickNum;
	bool keyFlg;
	int frame;
	bool judgeFlg;

	const void SetPos(const KdVec3& Vec){
		judgeMat._41 = Vec.x;
		judgeMat._42 = Vec.y;
		judgeMat._43 = Vec.z;
	}

	std::shared_ptr<SoundBase> m_pSound = nullptr;

};