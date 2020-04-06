#include"../System/KdLibrary/KdLibrary.h"
#include"CGameScene.h"
//-----------
#include"../Game/TestCharacter.h"



CGameScene::CGameScene(LPDIRECT3DDEVICE9 lpD3DDevice)
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

void CGameScene::Draw2D(LPDIRECT3DDEVICE9 lpD3DDevice)
{
}

void CGameScene::Draw3D(LPDIRECT3DDEVICE9 lpD3DDevice)
{
	test->Draw3D();
}
