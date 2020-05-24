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
	//ゲームシーンから取ってきたデータを保存する
	ScoreData = DTWHOUCE.GetVec("score");


	fish = std::make_shared<Fish>();
	fish->ResultInit();

	if (ScoreData.Success)CalcData();

	mPos = { 0,0,0 };

	Sky = std::make_shared<Skysphere>();
	Sky->Init();
	NumberTex = RESOURCE_MNG.GetTexture("BLackNumber.png");
	
	CoinTex = RESOURCE_MNG.GetTexture("Coin.png");
	mCoinMat.SetTrans(1280.0f / 3, 720.0f / 5 * 4, 0.0f);

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

	RECT rcCoin = { 0,0,80,80 };
	SPRITE->SetTransform(&mCoinMat);
	SPRITE->Draw(*CoinTex, &rcCoin, &D3DXVECTOR3(40.0f, 40.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	RECT rcNumber = { 0,0,400,80 };
	SPRITE->SetTransform(&mNameMat);
	SPRITE->Draw(*NumberTex, &rcNumber, &D3DXVECTOR3(200.0f, 40.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}


void CResultScene::Draw3D()
{
	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, TRUE);
	
	Sky->Draw3D();
	if (ScoreData.Success) {
		fish->Draw3D();
	}
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

	DTWHOUCE.SetVec("score", { 0,0,0 });
}

void CResultScene::CalcData()
{
	//魚のサイズと売値
	if (DTWHOUCE.GetStr("FishName") == "RedSnapper"){
		Size = 50;
		Price = 3500;
	}
	if (DTWHOUCE.GetStr("FishName") == "Saury"){
		Size = 35;
		Price = 300;
	}
	if (DTWHOUCE.GetStr("FishName") == "Tuna"){
		Size = 150;
		Price = 2000000;
	}
	if (DTWHOUCE.GetStr("FishName") == "Shark"){
		Size = 430;
		Price = 10000;
	}
	if (DTWHOUCE.GetStr("FishName") == "SunFish"){
		Size = 250;
		Price = 20000;
	}
	if (DTWHOUCE.GetStr("FishName") == "Whale"){
		Size = 2700;
		Price = 3500000;
	}
}
