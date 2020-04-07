#include"../System/KdLibrary/KdLibrary.h"

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
	Seas->Draw();
	test->Draw3D();
	
}
