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
	float scale;
	//ÉmÅ[Éc
	LPDIRECT3DTEXTURE9 notesTex;
	KdMatrix notesMat;
	//îªíËï∂éö
	LPDIRECT3DTEXTURE9 judgeTex;
	LPDIRECT3DTEXTURE9 resultTex = nullptr;
	KdMatrix judgeMat;

	LPDIRECT3DTEXTURE9 backTex;

	float dist;
	int level;
	float speed;
	int size;
	int clickNum;
	bool keyFlg;
	int frame;
	int wait;

	std::vector<std::shared_ptr<SoundBase>> m_pSound;

};