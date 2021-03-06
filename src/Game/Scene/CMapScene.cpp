#include"../../System/KdLibrary/KdLibrary.h"
#include "../../System/FrameBase/CGameFrame.h"
#include"CMapScene.h"
//―――――――――――――――――――――――――

#include"../C_Player.h"
#include"../Skysphere.h"
#include"../Sea.h"
#include"../Port.h"
#include"../Fish.h"
#include"../Fishing.h"
#include"../Seagull.h"
#include"../ShopObject.h"



CMapScene::CMapScene()
{

}

CMapScene::~CMapScene()
{
}

void CMapScene::Init()
{
	//スカイスフィア
	Sky = std::make_shared<Skysphere>();
	Sky->Init();


	//海
	Seas = std::make_shared<Sea>();
	Seas->Init();
	//港
	m_Port = std::make_shared<Port>();
	m_Port->Init();
	//プレイヤー
	m_Player = std::make_shared<C_Player>();
	m_Player->Init();
	//釣り関係

	//魚
	m_Fishing = std::make_shared<C_Fishing>();
	m_Fishing->Init();

	//カモメ
	m_Seagull = std::make_shared<Seagull>();
	m_Seagull->Init();

	m_PSound = RESOURCE_MNG.GetSound("wave3");
	m_PSound->LDS3B8->SetMode(DS3DMODE_DISABLE, DS3D_IMMEDIATE);
	m_PSound->Playsound("wave3", true, true);
	m_PBGM = RESOURCE_MNG.GetSound("超使いやすいドラム&ベース無限BGM");
	m_PBGM->LDS3B8->SetMode(DS3DMODE_DISABLE, DS3D_IMMEDIATE);
	m_PBGM->SetVol(0.5f);
	m_PBGM->Playsound("超使いやすいドラム&ベース無限BGM", true, true);
	m_pSE = nullptr;





	DTWHOUCE.SetStr("FishName", "SunFish");
}

int CMapScene::Update()
{
	m_Player->Update();
	Sky->Update();
	m_Port->Update();
	Seas->Update();

	m_Fishing->Update();

	m_Seagull->Update();



	if (!DTWHOUCE.GetFlg("FishingFlg")) {
		POINT BasePt;
		BasePt.x = 640;
		BasePt.y = 360;
		ClientToScreen(FRAME.GetHWND(), &BasePt);
		SetCursorPos(BasePt.x, BasePt.y);
	}

	if (GetKey(VK_SPACE) & 0x8000)
	{
		m_pSE = RESOURCE_MNG.GetSound("システム　決定音2");
		m_pSE->Playsound("システム　決定音2", true, false);

		FADE.Start(5);
		return ROGO;
	}
	if (DTWHOUCE.GetFlg("ShopFlg")) {
		m_pSE = RESOURCE_MNG.GetSound("ドア");
		m_PBGM->SetVol(0.1f);
		m_PSound->SetVol(0.1f);
		m_pSE->SetVol(1.0f);
		m_pSE->Playsound("ドア", true, false);

		FADE.Start(5);
		return SHOP;
	}
	if (DTWHOUCE.GetFlg("HitFish")) {
		m_pSE = RESOURCE_MNG.GetSound("システム　決定音2");
		m_PBGM->SetVol(0.1f);
		m_PSound->SetVol(0.1f);
		m_pSE->Playsound("システム　決定音2", true, false);

		FADE.Start(5);
		return GAME;
	}

	return MAP;
}

void CMapScene::Draw2D()
{
	m_Player->Draw2D();
	//m_Fishing->Draw2D();
}

void CMapScene::Draw3D()
{
	//m_Player->Draw3D();
	Sky->Draw3D();
	m_Port->Draw3D();
	Seas->Draw3D();
	m_Fishing->Draw3D();
	m_Seagull->Draw3D();
}

void CMapScene::End()
{
	Sky->End();
	Sky = nullptr;
	Seas->End();
	Seas = nullptr;
	m_Port->End();
	m_Port = nullptr;
	m_Player->End();
	m_Player = nullptr;
	m_Fishing->End();
	m_Fishing = nullptr;
	m_Seagull->End();
	m_Seagull = nullptr;

	m_PSound->LDSB8->Stop();
	m_PSound = nullptr;
	m_PBGM->LDSB8->Stop();
	m_PBGM = nullptr;
	m_pSE->LDSB8->Stop();
	m_pSE = nullptr;
}
