#include"../System/KdLibrary/KdLibrary.h"
#include "CShopScene.h"
#include"GameProc.h"

CShopScene::CShopScene()
{
	shop = std::make_shared<Shop2D>();
	shop->Init();	

	gameProc = std::make_shared<CGameProc>();
	gameProc->Init();
}

CShopScene::~CShopScene()
{

}

void CShopScene::Init()
{
	
}

int CShopScene::Update()
{
	shop->Update();
	gameProc->Update();

	//ƒV[ƒ“Ø‚è‘Ö‚¦
	if (GetKey('O') & 0x8000)
	{
		return MAP;
	}
	return SHOP;
}

void CShopScene::Draw2D()
{
	shop->Draw2D();
	gameProc->Draw();
}

void CShopScene::Draw3D()
{

}
