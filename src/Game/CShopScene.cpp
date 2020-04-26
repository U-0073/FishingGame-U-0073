#include"../System/KdLibrary/KdLibrary.h"
#include "CShopScene.h"
#include"GameProc.h"

CShopScene::CShopScene()
	:mMat()
{
	shop = std::make_shared<Shop2D>();
	shop->Init();
}

CShopScene::~CShopScene()
{

}

void CShopScene::Init()
{
	vTex = *RESOURCE_MNG.GetTexture("Resouce/Texture/Shop/ShopBack.png", D3DCOLOR_ARGB(255, 255, 255, 255));


}

int CShopScene::Update()
{
	shop->Update();

	//ƒV[ƒ“Ø‚è‘Ö‚¦
	if (GetKey('O') & 0x8000)
	{
		FADE.Start(5);
		return MAP;
	}
	return SHOP;
}

void CShopScene::Draw2D()
{

	SPRITE->Begin(D3DXSPRITE_ALPHABLEND);

	RECT rcTitle = { 0,0,1280,720 };
	SPRITE->SetTransform(&mMat);
	SPRITE->Draw(vTex, &rcTitle, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	SPRITE->End();

	shop->Draw2D();
}

void CShopScene::Draw3D()
{

}
