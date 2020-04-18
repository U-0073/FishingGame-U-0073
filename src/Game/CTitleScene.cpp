#include"../System/KdLibrary/KdLibrary.h"
#include "CTitleScene.h"

CTitleScene::CTitleScene()
{
	KD3D.LoadTexture(&vTex, "Resouce/Texture/white.png", 10000,10000, D3DCOLOR_ARGB(255, 255, 255, 255));
	D3DXMatrixTranslation(&mMat, 0.0f, 0.0f, 0.0f);
	
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
			Alpha += 0.5;
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
	return TITLE;
}

void CTitleScene::Draw2D()
{
	Fishes->Draw2D();
	title->Draw2D();
	
	SPRITE->Begin(D3DXSPRITE_ALPHABLEND);
	RECT rcTitle = { 0,0,10000,10000 };
	SPRITE->SetTransform(&mMat);
	SPRITE->Draw(vTex, &rcTitle, &D3DXVECTOR3(5000.0f, 5000.0f, 0.0f), NULL, D3DCOLOR_ARGB((int)Alpha, 255, 255, 255));
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
