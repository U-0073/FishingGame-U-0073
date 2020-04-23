#pragma once
#include"../System/FrameBase/CSceneBase.h"
#define path "Resouce/Texture/"
#include"Shop2D.h"

class Shop2D;
class CGameProc;

class CShopScene : public CSceneBase
{
public:
	CShopScene();
	~CShopScene();

	void Init()override;
	int Update()override;
	void Draw2D()override;
	void Draw3D()override;
	int GetID()override { return SHOP; };
	void End()override {};

private:
	std::shared_ptr<Shop2D> shop = nullptr;
	std::shared_ptr<CGameProc> gameProc = nullptr;


	D3DXMATRIX mMat;
	D3DXMATRIX mScale;
	LPDIRECT3DTEXTURE9 vTex;

};