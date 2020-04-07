#include"../System/KdLibrary/KdLibrary.h"
#include"CGameScene.h"
//―――――――――――――――――――――――――
#include"C_Player.h"
#include"TestCharacter.h"
#include"Skysphere.h"
#include"Sea.h"



CGameScene::CGameScene()
{
	//テストキャラクター
	test = std::make_shared<TestCharacter>();
	test->Init();
	//スカイスフィア
	Sky = std::make_shared<Skysphere>();
	Sky->Init();
	Seas = std::make_shared<Sea>();

	//プレイヤー
	m_Player = std::make_shared<C_Player>();
	
}

CGameScene::~CGameScene()
{
}

void CGameScene::Update()
{
	CAMERA.SetCameraPos(D3DXVECTOR3(0, 1, -1), D3DXVECTOR3(0, -0.5, 1));
}

void CGameScene::Draw2D()
{
}

void CGameScene::Draw3D()
{
	test->Draw3D();
	Sky->Draw3D();
	Seas->Draw();
	m_Player->Draw3D();
}
