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
	Sky = std::make_shared<Skysphere>();
	Sky->Init();
	result = std::make_shared<Result>();
	result->Init();
	//ゲームシーンで成功していたらロードする
	ScoreData = DTWHOUCE.GetVec("score");
	if (ScoreData.Success) {
		//ゲームシーンから取ってきたデータを保存する

		fish = std::make_shared<Fish>();
		fish->ResultInit();
		if (ScoreData.Success)CalcData();
		mPos = { 0,0,0 };
		CalcNum();
		CoinTex = RESOURCE_MNG.GetTexture("Coin.png");
		mCoinMat.SetTrans(1280.0f / 3, 720.0f / 6 * 5, 0.0f);
		NameTex = RESOURCE_MNG.GetTexture(fish->getTag() + ".png");
		mNameMat.SetTrans(1280.0f / 2, 720.0f / 2 + 75, 0.0f);
		KD3D.CreateDirectionalLight(D3DXVECTOR3(0, 0, -1), D3DXVECTOR4(1, 1, 1, 1), D3DXVECTOR4(1.0, 1.0, 1.0, 1.0));
		if (DTWHOUCE.GetStr("FishName") == "SunFish") {
			CAMERA.SetCameraPos(D3DXVECTOR3(0, -5, -50), D3DXVECTOR3(0, -5, 0));
		}
		else {
			CAMERA.SetCameraPos(D3DXVECTOR3(0, -5, -25), D3DXVECTOR3(0, -5, 0));
		}
	}
	else {
		CAMERA.SetCameraPos(D3DXVECTOR3(0, 0, -25), D3DXVECTOR3(0, 0, 0));
		Size = 1280;
		Price = 8888;
	}
}

int CResultScene::Update()
{
	result->Update();
	if (GetKey(VK_RETURN) & 0x8000)
	{
		if (sellflg == false)
		{
			if (ScoreData.Success)
			{
				if (sellflg == false) 
				{
					int Possession;
					Possession = DTWHOUCE.GetInt("Possession");
					Possession += Price;
					DTWHOUCE.SetInt("Possession", Possession);

					SellSound = RESOURCE_MNG.GetSound("Money");
					SellSound->Playsound("Money", true, false);
				}
				sellflg = true;

				FADE.Start(5);
				return MAP;
			}
			else
			{
				FADE.Start(5);
				return MAP;
			}
		}
	}
	return RESULT;
}

void CResultScene::Draw2D()
{
	result->Draw2D();
	if (ScoreData.Success)
	{
		RECT rcName = { 0,0,300,50 };
		SPRITE->SetTransform(&mNameMat);
		SPRITE->Draw(*NameTex, &rcName, &D3DXVECTOR3(150.0f, 50.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

		RECT rcCoin = { 0,0,80,80 };
		SPRITE->SetTransform(&mCoinMat);
		SPRITE->Draw(*CoinTex, &rcCoin, &D3DXVECTOR3(40.0f, 40.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

		mNumberMat.SetTrans(1280 / 2 * 0.3, 720 / 5 * 3, 0);
		mPriceMat.SetTrans(1280 / 2, 720 / 5 * 4, 0);


		for (int i = 0; i < 6; i++)
		{
			mNumberMat *= mTransMat;
			SPRITE->SetTransform(&mNumberMat);
			SPRITE->Draw(*NumberTex, &rcSize[i], &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		for (int i = 0; i < 7; i++)
		{
			mPriceMat *= mPriceTransMat;
			SPRITE->SetTransform(&mPriceMat);
			SPRITE->Draw(*NumberTex, &rcPrice[i], &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
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
	result->End();
	result = nullptr;
	if (ScoreData.Success)
	{
		fish->End();
		fish = nullptr;
	}
	DTWHOUCE.SetVec("score", { 0,0,0 });
	DTWHOUCE.SetFlg("HitFish", false);
}

void CResultScene::CalcData()
{
	//魚のサイズと売値
	if (DTWHOUCE.GetStr("FishName") == "RedSnapper") {
		Size = 50;
		Price = 3500;
	}
	if (DTWHOUCE.GetStr("FishName") == "Saury") {
		Size = 35;
		Price = 300;
	}
	if (DTWHOUCE.GetStr("FishName") == "Tuna") {
		Size = 150;
		Price = 2000000;
	}
	if (DTWHOUCE.GetStr("FishName") == "Shark") {
		Size = 430;
		Price = 10000;
	}
	if (DTWHOUCE.GetStr("FishName") == "SunFish") {
		Size = 250;
		Price = 20000;
	}
	if (DTWHOUCE.GetStr("FishName") == "Whale") {
		Size = 2700;
		Price = 3500000;
	}
	float Quality = 1.0f + DTWHOUCE.GetNo("Quality");
	Size *= Quality;
	Price *= Quality;
}

void CResultScene::CalcNum()
{
	NumberTex = RESOURCE_MNG.GetTexture("Shop/number.png");
	//サイズ
	mTransMat.SetTrans(100, 0, 0);
	mPriceTransMat.SetTrans(50, 0, 0);
	mNumberMat.SetScale(2.0f, 2.0f, 2.0f);
	int FishSize = Size * 100;
	//位取り
	rcSize[0] = { (FishSize / 100000) * 50,0,(FishSize / 100000) * 50 + 50,50 };//億の位
	FishSize = (FishSize % 100000);
	rcSize[1] = { (FishSize / 10000) * 50,0,(FishSize / 10000) * 50 + 50,50 };
	FishSize = (FishSize % 10000);
	rcSize[2] = { (FishSize / 1000) * 50,0,(FishSize / 1000) * 50 + 50,50 };
	FishSize = (FishSize % 1000);
	rcSize[3] = { (FishSize / 100) * 50,0,(FishSize / 100) * 50 + 50,50 };
	FishSize = (FishSize % 100);
	rcSize[4] = { (FishSize / 10) * 50,0,(FishSize / 10) * 50 + 50,50 };
	FishSize = (FishSize % 10);
	rcSize[5] = { (FishSize / 1) * 50,0,(FishSize / 1) * 50 + 50,50 };
	FishSize = (FishSize % 1);

	int FishPrice = Price;
	rcPrice[0] = { (FishPrice / 1000000) * 50,0,(FishPrice / 1000000) * 50 + 50,50 };//億の位
	FishPrice = (FishPrice % 1000000);
	rcPrice[1] = { (FishPrice / 100000) * 50,0,(FishPrice / 100000) * 50 + 50,50 };
	FishPrice = (FishPrice % 100000);
	rcPrice[2] = { (FishPrice / 10000) * 50,0,(FishPrice / 10000) * 50 + 50,50 };
	FishPrice = (FishPrice % 10000);
	rcPrice[3] = { (FishPrice / 1000) * 50,0,(FishPrice / 1000) * 50 + 50,50 };
	FishPrice = (FishPrice % 1000);
	rcPrice[4] = { (FishPrice / 100) * 50,0,(FishPrice / 100) * 50 + 50,50 };
	FishPrice = (FishPrice % 100);
	rcPrice[5] = { (FishPrice / 10) * 50,0,(FishPrice / 10) * 50 + 50,50 };
	FishPrice = (FishPrice % 10);
	rcPrice[6] = { (FishPrice / 1) * 50,0,(FishPrice / 1) * 50 + 50,50 };
	FishPrice = (FishPrice % 1);


}
