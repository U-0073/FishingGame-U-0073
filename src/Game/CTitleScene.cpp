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
	CAMERA.SetCameraPos(mPos+D3DXVECTOR3(3,1,-5), D3DXVECTOR3(0, -1, 1));
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
      Fishes->TitleUpdate();
	}
}

void CTitleScene::Draw2D()
{
	Fishes->Draw2D();
	title->Draw2D();
}

void CTitleScene::Draw3D()
{
	Sky->Draw3D();
	Fishes->Draw3D();
}
