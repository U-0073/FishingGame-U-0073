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
	gameProc->Draw();
}

void CGameScene::Draw3D()
{

}
