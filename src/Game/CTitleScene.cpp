#include"../System/KdLibrary/KdLibrary.h"
#include "CTitleScene.h"

CTitleScene::CTitleScene()
{
	KD3D.LoadTexture(&vTex, "Resouce/Texture/white.png", 3,3, D3DCOLOR_ARGB(255, 255, 255, 255));
	D3DXMatrixTranslation(&mMat, 0.0f, 0.0f, 0.0f);
	D3DXMatrixTranslation(&mScale, 0.0f, 0.0f, 0.0f);
	
	Sky = std::make_shared<Skysphere>();
	Sky->Init();
	Fishes = std::make_shared<Fish>();
	Fishes->Init();
	title = std::make_shared<Title>();
	title->Init();
	
	CAMERA.SetCameraPos(D3DXVECTOR3(0,3,-5), Fishes->GetFishPos());
	MoveFlg = false;
	Alpha = 0;

	mPos = D3DXVECTOR3(0, 20, 0);

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
		MoveFlg = true;
		//return GAME;
	}
	if (MoveFlg) {
		if (Fishes->GetFishPos().z < -30) {
			Alpha += 100;
		}
		if (Alpha > 255) {
			Alpha = 255;
		}
		Fishes->TitleUpdate();
		CAMERA.SetCameraPos(D3DXVECTOR3(0, 3, -5), Fishes->GetFishPos());
	}
	if (Fishes->GetFishPos().z < -100) {
		return GAME;
	}
	D3DXMatrixScaling(&mMat, 1280.0f/2, 720.0f/2, 0.0f);
	D3DXMatrixScaling(&mScale, 1290.0f, 730.0f, 0.0f);
	mMat = mScale * mMat;
	return TITLE;
}

void CTitleScene::Draw2D()
{
	Fishes->Draw2D();
	title->Draw2D();
	
	SPRITE->Begin(D3DXSPRITE_ALPHABLEND);
	RECT rcTitle = { 1,1,2,2 };
	SPRITE->SetTransform(&mMat);
	SPRITE->Draw(vTex, &rcTitle, &D3DXVECTOR3(1.0f, 1.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	SPRITE->End();
}

void CTitleScene::Draw3D()
{
	Sky->Draw3D();
	Fishes->Draw3D();
}

void CTitleScene::End()
{
}
