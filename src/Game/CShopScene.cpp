#include"../System/KdLibrary/KdLibrary.h"
#include "CShopScene.h"

CShopScene::CShopScene()
{

	//shop = std::make_shared<Shop>();
	//shop->Init();

	//KD3D.LoadTexture(&vTex, "Resouce/Texture/white.png", 3, 3, NULL);
	vTex = RESOURCE_MNG.GetTexture("Resouce/Texture/white.png", 3, 3, NULL);
	
}

CShopScene::~CShopScene()
{

}

void CShopScene::Init()
{

}

void CShopScene::Update()
{
	//shop->Update();

	//ƒV[ƒ“Ø‚è‘Ö‚¦
	if (GetKey('I') & 0x8000)
	{
		
	}
}

void CShopScene::Draw2D()
{
	//shop->Draw2D();

}

void CShopScene::Draw3D()
{

}
