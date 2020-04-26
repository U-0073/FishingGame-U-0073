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
	void End()override {};

private:
	std::shared_ptr<CGameProc> gameProc = nullptr;


	KdMatrix BackMat;
	LPDIRECT3DTEXTURE9 BackTex;

};