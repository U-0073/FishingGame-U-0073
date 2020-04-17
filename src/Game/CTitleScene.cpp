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
	
	CAMERA.SetCameraPos(D3DXVECTOR3(0,1,-5), Fishes->GetFishPos());

}

CTitleScene::~CTitleScene()
{
	
}

void CTitleScene::Init()
{
	
}

int CTitleScene::Update()
{
	title->Update();
	Sky->SetPos(mPos);

	//ƒV[ƒ“Ø‚è‘Ö‚¦
	if (GetKey(VK_RETURN) & 0x8000)
	{
		return GAME;
	}
	return TITLE;
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

void CTitleScene::End()
{
}
