#include"../System/KdLibrary/KdLibrary.h"
#include"CGameScene.h"
//―――――――――――――――――――――――――
#include"C_Player.h"
#include"TestCharacter.h"
#include"Skysphere.h"
#include"Sea.h"
#include"Port.h"
#include"Fish.h"



CGameScene::CGameScene()
{
	//テストキャラクター
	test = std::make_shared<TestCharacter>();
	test->Init();
	//スカイスフィア
	Sky = std::make_shared<Skysphere>();
	Sky->Init();
	//海
	Seas = std::make_shared<Sea>();
	//港
	m_Port = std::make_shared<Port>();
	m_Port->Init();
	//魚
	Fishes = std::make_shared<Fish>();
	Fishes->Init();
	//プレイヤー
	m_Player = std::make_shared<C_Player>();

}

CGameScene::~CGameScene()
{
}

void CGameScene::Update()
{
	m_Player->Update();
	Sky->SetPos(m_Player->GetPlayerPos());
	m_Port->Update();
	Fishes->Update();
}

void CGameScene::Draw2D()
{
	m_Player->Draw2D();
}

void CGameScene::Draw3D()
{
	test->Draw3D();
	Sky->Draw3D();
	m_Port->Draw3D();
	Seas->Draw();
	Fishes->Draw3D();
	m_Player->Draw3D();
}