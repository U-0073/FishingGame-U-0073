#include"../System/KdLibrary/KdLibrary.h"
#include"CGameScene.h"
//-----------
#include"../Game/TestCharacter.h"



CGameScene::CGameScene()
{
	//テストキャラクター
	test = std::make_shared<TestCharacter>();
	test->Init();
}

CGameScene::~CGameScene()
{
}

void CGameScene::Update()
{

}

void CGameScene::Draw2D()
{
}

void CGameScene::Draw3D()
{
	test->Draw3D();
}
