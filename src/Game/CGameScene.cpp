#include"../System/KdLibrary/KdLibrary.h"
#include"../System/2d/Board.h"

#include"CGameScene.h"
//-----------
#include"../Game/TestCharacter.h"




CGameScene::CGameScene()
{
	//テストキャラクター
	test = std::make_shared<TestCharacter>();
	test->Init();

	Sea = std::make_shared<Board>();
	Sea->CleateBoardList(10,10);
	Sea->CangeSize(D3DXVECTOR3(100, 100, 0));
	Sea->setTexParam("Resouce/Texture/Ground.bmp", 1024, 1024, D3DCOLOR_ARGB(255, 255, 255, 255),true);

}

CGameScene::~CGameScene()
{
}

void CGameScene::Update()
{
	Sea->Update();
}

void CGameScene::Draw2D()
{
}

void CGameScene::Draw3D()
{
	Sea->Draw();
	test->Draw3D();
	
}
