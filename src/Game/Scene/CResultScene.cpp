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

void CResultScene::Init()
{
	if (ScoreData.Success) {
		//ゲームシーンから取ってきたデータを保存する
		ScoreData = DTWHOUCE.GetVec("score");

		fish = std::make_shared<Fish>();
		fish->ResultInit();
		if (ScoreData.Success)CalcData();
		else {
			Size = 1280;
			Price = 8888;
		}

		mPos = { 0,0,0 };

		Sky = std::make_shared<Skysphere>();
		Sky->Init();
		NumberTex = RESOURCE_MNG.GetTexture("Shop/number.png");
		mNumberMat.SetScale(5.0f, 5.0f, 5.0f);
		CoinTex = RESOURCE_MNG.GetTexture("Coin.png");
		mCoinMat.SetTrans(1280.0f / 3, 720.0f / 6 * 5, 0.0f);

		NameTex = RESOURCE_MNG.GetTexture(fish->getTag() + ".png");
		mNameMat.SetTrans(1280.0f / 2, 720.0f / 2 + 75, 0.0f);

		result = std::make_shared<Result>();
		result->Init();
		CAMERA.SetCameraPos(D3DXVECTOR3(0, 0, -25), fish->GetFishPos());
		if (fish->getTag() == "SunFish" || fish->getTag() == "Whale") {
			CAMERA.SetCameraPos(D3DXVECTOR3(0, 0, -50), fish->GetFishPos());
		}
	}
	if (ScoreData.Success) {
		BackTex = RESOURCE_MNG.GetTexture("SeaBack001.png");
		mBackMat.SetTrans(1280/2, 720/2, 0);
	}
	KD3D.CreateDirectionalLight(D3DXVECTOR3(0, 0, -1), D3DXVECTOR4(1, 1, 1, 1), D3DXVECTOR4(1.0, 1.0, 1.0, 1.0));
	
}

int CResultScene::Update()
{
	
	
	if (!ScoreData.Success) {

		FADE.Start(5);
		return MAP;
	}
	if (ScoreData.Success) {
		result->Update();
		if (GetKey(VK_RETURN) & 0x8000)
		{
			int Possession;
			Possession = DTWHOUCE.GetNo("Possession");
			Possession += Price;
			DTWHOUCE.SetNo("Possession", Possession);

			SellSound = RESOURCE_MNG.GetSound("Money");
			SellSound->Playsound("Money", true, false);
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

	RECT rcScore[] = {
	{  0    ,0, 50 * 1,50 },
	{ 50 * 1,0, 50 * 2,50 },
	{ 50 * 2,0, 50 * 3,50 },
	{ 50 * 3,0, 50 * 4,50 },
	{ 50 * 4,0, 50 * 5,50 },
	{ 50 * 5,0, 50 * 6,50 },
	{ 50 * 6,0, 50 * 7,50 },
	{ 50 * 7,0, 50 * 8,50 },
	{ 50 * 8,0, 50 * 9,50 },
	{ 50 * 9,0, 50 * 10,50 } };

	char cScore[64];
	sprintf_s(cScore, sizeof(cScore), "%d", (int)Price);
	D3DXMatrixTranslation(&mNumberMat, 1280/2*1.5, 720/5*4, 0);
	D3DXMatrixTranslation(&mTransMat, -35, 0, 0);

	int i;
	for (int i = 0; cScore[i] != '\0'; i++);

	for (i -= 1; i >= 0; i--) {
		mNumberMat *= mTransMat;
		SPRITE->SetTransform(&mNumberMat);
		SPRITE->Draw(*NumberTex, &rcScore[cScore[i] - '0'], &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	RECT rcSize[] = {
	{  0    ,0, 50 * 1,50 },
	{ 50 * 1,0, 50 * 2,50 },
	{ 50 * 2,0, 50 * 3,50 },
	{ 50 * 3,0, 50 * 4,50 },
	{ 50 * 4,0, 50 * 5,50 },
	{ 50 * 5,0, 50 * 6,50 },
	{ 50 * 6,0, 50 * 7,50 },
	{ 50 * 7,0, 50 * 8,50 },
	{ 50 * 8,0, 50 * 9,50 },
	{ 50 * 9,0, 50 * 10,50 } };

	char cSize[64];
	sprintf_s(cSize, sizeof(cSize), "%d", (int)Size*100);
	D3DXMatrixTranslation(&mNumberMat, 1280 / 2, 720 / 5 *3, 0);
	D3DXMatrixTranslation(&mTransMat, -35, 0, 0);

	int j;
	for (j = 0; cSize[j] != '\0'; j++);

	for (j -= 1; j >= 0; j--) {
		mNumberMat *= mTransMat;
		SPRITE->SetTransform(&mNumberMat);
		SPRITE->Draw(*NumberTex, &rcSize[cSize[j] - '0'], &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	
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
