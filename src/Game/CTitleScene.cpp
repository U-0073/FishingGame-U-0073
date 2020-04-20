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
	
	CAMERA.SetCameraPos(D3DXVECTOR3(0,3,-5), Fishes->GetFishPos());
	KD3D.LoadTexture(&vTex, "Resouce/Texture/white.png", 3,3, NULL);
	D3DXMatrixTranslation(&mMat, 1280.0f / 2, 720.0f / 2, 0.0f);
	D3DXMatrixScaling(&mScale, 1290.0f, 730.0f, 0.0f);
	mMat = mScale * mMat;
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

	//シーン切り替え
	if (GetKey(VK_RETURN) & 0x8000)
	{
		MoveFlg = true;
		//return GAME;
	}
	if (MoveFlg) {
		if (Fishes->GetFishPos().z < -30) {
			Alpha += 1;
		}
		if (Alpha > 255) {
			Alpha = 255;
			return GAME;
		}
		Fishes->TitleUpdate();
		CAMERA.SetCameraPos(D3DXVECTOR3(0, 3, -5), Fishes->GetFishPos());
	}
	if (Fishes->GetFishPos().z < -100) {
	}
	if (GetKey('I') & 0x8000) {
		return SHOP;
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

	SPRITE->Begin(D3DXSPRITE_ALPHABLEND);
	RECT rcTitle = { 1,1,2,2 };
	SPRITE->SetTransform(&mMat);
	SPRITE->Draw(vTex, &rcTitle, &D3DXVECTOR3(0.5f, 0.5f, 0.0f), NULL, D3DCOLOR_ARGB((int)Alpha, 255, 255, 255));
	SPRITE->End();

}

void CTitleScene::End()
{
}
