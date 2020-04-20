#include"../System/KdLibrary/KdLibrary.h"
#include "CShopScene.h"

CShopScene::CShopScene()
{
	shop = std::make_shared<Shop2D>();
	shop->Init();	
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

	//�V�[���؂�ւ�
	if (GetKey('O') & 0x8000)
	{
		return GAME;
	}
	return SHOP;
}

void CShopScene::Draw2D()
{
	shop->Draw2D();

}

void CShopScene::Draw3D()
{

}
