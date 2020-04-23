#include"../System/KdLibrary/KdLibrary.h"
#include"CMapScene.h"
//―――――――――――――――――――――――――
#include "structList.h"
#include"C_Player.h"
#include"Skysphere.h"
#include"Sea.h"
#include"Port.h"
#include"Fish.h"
#include "Fishing.h"
#include"ShopObject.h"



CMapScene::CMapScene()
{
	//スカイスフィア
	Sky = std::make_shared<Skysphere>();
	Sky->Init();
	//海
	Seas = std::make_shared<Sea>();
	//港
	m_Port = std::make_shared<Port>();
	m_Port->Init();
	//プレイヤー
	m_Player = std::make_shared<C_Player>();
	m_Player->Init();
	//釣り関係

	m_Fishing = std::make_shared<C_Fishing>();
	m_Fishing->Init();

	m_PSound = RESOURCE_MNG.GetSound("Resouce/Sound/wave3.wav");
	m_PSound->Playsound("Resouce/Sound/wave3.wav", true, false);
}

CMapScene::~CMapScene()
{
}

void CMapScene::Init()
{

}

int CMapScene::Update()
{
	m_Player->Update();
	Sky->SetPos(m_Player->GetPlayerPos());
	m_Port->Update();

	m_Fishing->SetCamAngY(m_Player->GetCamAngY());
	m_Fishing->SetPlayerPos(m_Player->GetPlayerPos());
	m_Fishing->SetFishFlg(m_Player->GetFeshFlg());
	m_Fishing->SetBuoiFlg(m_Player->GetBuoiFlg());
	m_Fishing->Update();
//	Fishes->Update();


	if (GetKey(VK_SPACE) & 0x8000) 
	{
		return TITLE;
	}
	if (GetKey('I') & 0x8000) {
		return SHOP;
	}
	if (GetKey('G') & 0x8000) {
		return GAME;
	}

	return MAP;
}

void CMapScene::Draw2D()
{
	m_Player->Draw2D();
	m_Fishing->Draw2D();
}

void CMapScene::Draw3D()
{
	Sky->Draw3D();
	m_Port->Draw3D();
	//Seas->Draw();
	Seas->DrawObject();
	m_Fishing->Draw3D();
	//Fishes->Draw3D();
	m_Player->Draw3D();
}

void CMapScene::End()
{
	m_PSound->LDSB8->Stop();
}
