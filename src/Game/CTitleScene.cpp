#include"../System/KdLibrary/KdLibrary.h"
#include "CTitleScene.h"

CTitleScene::CTitleScene()
{
	Sky = std::make_shared<Skysphere>();
	Sky->Init();
	Fishes = std::make_shared<Fish>();
	Fishes->Init();
	title = std::make_shared<Title>();
	title->Init();
}

CTitleScene::~CTitleScene()
{
	
}

void CTitleScene::Init()
{
	
}

void CTitleScene::Update()
{
	title->Update();
	Sky->SetPos(mPos);
	if (GetAsyncKeyState(VK_RETURN)&0x8000) {
      Fishes->Update();
	}
}

void CTitleScene::Draw2D()
{
	title->Draw2D();
}

void CTitleScene::Draw3D()
{
	Fishes->Draw3D();
	Sky->Update();
}
