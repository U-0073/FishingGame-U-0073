#include"../../System/KdLibrary/KdLibrary.h"
#include"CResultScene.h"
#include"../Skysphere.h"
#include"../Fish.h"
#include"../Result.h"

CResultScene::CResultScene()
{
}

CResultScene::~CResultScene()
{
}

void CResultScene::SetTagType(std::string Name) 
{
	
}

void CResultScene::Init()
{

	fish = std::make_shared<Fish>();
	fish->SetTagType(0);
	fish->ResultInit();



	mPos = { 0,0,0 };

	Sky = std::make_shared<Skysphere>();
	Sky->Init();
	NameTex = RESOURCE_MNG.GetTexture(fish->getTag() + ".png");
	mNameMat.SetTrans(1280.0f/2, 720.0f/2+75, 0.0f);
	result = std::make_shared<Result>();
	result->Init();
	CAMERA.SetCameraPos(D3DXVECTOR3(0, 0, -25), fish->GetFishPos());
	if (fish->getTag() == "SunFish"||fish->getTag()=="Whale") {
		CAMERA.SetCameraPos(D3DXVECTOR3(0, 0, -50), fish->GetFishPos());
	}
	KD3D.CreateDirectionalLight(D3DXVECTOR3(0, 0, -1), D3DXVECTOR4(1, 1, 1, 1), D3DXVECTOR4(1.0, 1.0, 1.0, 1.0));
	
}

int CResultScene::Update()
{
	result->Update();
	if (GetKey(VK_RETURN) & 0x8000)
	{
		FADE.Start(5);
		return MAP;
	}

	if (GetKey('I') & 0x8000) {
		FADE.Start(5);
		return SHOP;
	}

	if (GetKey('F') & 0x8000) {
		FADE.Start(5);
		return GAME;
	}
	return RESULT;
}

void CResultScene::Draw2D()
{
	result->Draw2D();

	RECT rcName = { 0,0,300,50 };
	SPRITE->SetTransform(&mNameMat);
	SPRITE->Draw(*NameTex, &rcName, &D3DXVECTOR3(150.0f, 50.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

}


void CResultScene::Draw3D()
{
	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, TRUE);
	
	Sky->Draw3D();
	fish->Draw3D();
	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, FALSE);
}

void CResultScene::End()
{
	Sky->End();
	Sky = nullptr;
	fish->End();
	fish = nullptr;
	result->End();
	result = nullptr;

}
