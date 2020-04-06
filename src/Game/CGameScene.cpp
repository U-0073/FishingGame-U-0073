#include"../System/KdLibrary/KdLibrary.h"
#include"CGameScene.h"
//―――――――――――――――――――――――――
#include "../Game/C_Player.h"
#include"../Game/TestCharacter.h"




CGameScene::CGameScene()
{
	//テストキャラクター
	test = std::make_shared<TestCharacter>();
	test->Init();

	m_Player = std::make_shared<C_Player>();
	
}

CGameScene::~CGameScene()
{
}

void CGameScene::Update()
{
	m_Player->Update();
}

void CGameScene::Draw2D()
{
}

void CGameScene::Draw3D()
{
	test->Draw3D();
	m_Player->Draw3D();
}
