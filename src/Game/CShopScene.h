#pragma once
#include"../System/FrameBase/CSceneBase.h"
#define path "Resouce/Texture/"
#include"Shop.h"
#include"Skysphere.h"
#include"Fish.h"
#include"Sea.h"

class Skysphere;
class Fish;
class Shop;
class Sea;

class CShopScene : public CSceneBase
{
public:
	CShopScene();
	~CShopScene();

	void Init()override;
	void Update();
	void Draw2D()override;
	void Draw3D()override;
	void CShopScene::LoadTexture(LPDIRECT3DTEXTURE9* lpTex, const std::string Path, int W, int H, const D3DCOLOR Color);


private:
	std::shared_ptr<Shop> shop = nullptr;

	D3DXMATRIX mMat;
	D3DXMATRIX mScale;
	LPDIRECT3DTEXTURE9 vTex;

};