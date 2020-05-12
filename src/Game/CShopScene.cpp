#include"../System/KdLibrary/KdLibrary.h"
#include "CShopScene.h"
#include"GameProc.h"

CShopScene::CShopScene()
	:mMat()
{
	shop2d = std::make_shared<Shop2D>();
	shop2d->Init();

	shopObj = std::make_shared<ShopObject>();
	shopObj->Init();
}

CShopScene::~CShopScene()
{
}

void CShopScene::Init()
{
	vTex = *RESOURCE_MNG.GetTexture("Resource/Texture/Shop/ShopBack001.png", D3DCOLOR_ARGB(255, 255, 255, 255));


}

int CShopScene::Update()
{
	shop2d->Update();
	shopObj->Update();

	shopObj->GetListChange(shop2d->SetListChange());

	//”wŒi‚ÌZ’l’²®
	D3DXMatrixTranslation(&mMat, 0, 0, 1);

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

	shop2d->Draw2D();
}

void CShopScene::Draw3D()
{
	shopObj->Draw3D();
}

void CShopScene::End()
{
	shop2d->End();
	shopObj->End();
	if (vTex != nullptr)vTex->Release();
}


