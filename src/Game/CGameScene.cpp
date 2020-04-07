#include"../System/KdLibrary/KdLibrary.h"
//#include"../System/2d/Board.h"

#include"CGameScene.h"
//-----------
#include"../Game/TestCharacter.h"
#include"../Game/Sea.h"



CGameScene::CGameScene()
{
	//�e�X�g�L�����N�^�[
	test = std::make_shared<TestCharacter>();
	test->Init();

	Seas = std::make_shared<Sea>();
	//Sea->CleateBoardList(10,10);
	//Sea->ChangeSize(D3DXVECTOR3(10, 0, 10));
	Seas->setTexParam("Resouce/Texture/Ground.bmp", 1024, 1024, D3DCOLOR_ARGB(255, 255, 255, 255));

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
	Seas->Draw();
	
}
