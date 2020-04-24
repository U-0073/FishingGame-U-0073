#include"../System/KdLibrary/KdLibrary.h"
#include "CGameScene.h"
#include"GameProc.h"

CGameScene::CGameScene()
{

	gameProc = std::make_shared<CGameProc>();
	gameProc->Init();
}

CGameScene::~CGameScene()
{

}

void CGameScene::Init()
{
	BackTex = *RESOURCE_MNG.GetTexture("Resouce/Texture/SeaBack001.png");
}

int CGameScene::Update()
{
	gameProc->Update();

	return GAME;
}

void CGameScene::Draw2D()
{
	//”wŒi
	SPRITE->Begin(D3DXSPRITE_ALPHABLEND);
	RECT rc = { 0,0,1280,720 };
	SPRITE->SetTransform(&BackMat);
	SPRITE->Draw(BackTex, &rc, &D3DXVECTOR3(0.0f,  0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	SPRITE->End();

	gameProc->Draw();
}

void CGameScene::Draw3D()
{

}
