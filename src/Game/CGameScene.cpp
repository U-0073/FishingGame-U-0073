#include"../System/KdLibrary/KdLibrary.h"
#include"../System/2d/Bord.h"

#include"CGameScene.h"
//―――――――――――――――――――――――――
#include "../Game/C_Player.h"
#include"../Game/TestCharacter.h"




CGameScene::CGameScene()
{
	//テストキャラクター
	test = std::make_shared<TestCharacter>();
	test->Init();

	//海
	Sea = std::make_shared<Bord>();
	Sea->CleateBordList(10,10);			
	Sea->CangeSize(D3DXVECTOR3(100, 100, 0));
	Sea->setTexParam("Resouce/Texture/Ground.bmp", 1024, 1024, D3DCOLOR_ARGB(255, 255, 255, 255),true);

	//プレイヤー
	m_Player = std::make_shared<C_Player>();
	
}

CGameScene::~CGameScene()
{
}

void CGameScene::Update()
{
	Sea->Update();
	m_Player->Update();
}

void CGameScene::Draw2D()
{
}

void CGameScene::Draw3D()
{
	Sea->Draw();
	test->Draw3D();
	m_Player->Draw3D();
}
