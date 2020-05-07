#include"../System/KdLibrary/KdLibrary.h"
#include "CTitleScene.h"

CTitleScene::CTitleScene()
{

	Sky = std::make_shared<Skysphere>();
	Sky->Init();
	Fishes = std::make_shared<Fish>();
	Fishes->Init();
	title = std::make_shared<Title>();
	title->Init();

	CAMERA.SetCameraPos(D3DXVECTOR3(0, 3, -5), Fishes->GetFishPos());
	MoveFlg = false;

	mPos = D3DXVECTOR3(0, 20, 0);
	m_PSound = RESOURCE_MNG.GetSound("Resource/Sound/TitleBGM.wav");
	//m_PSound->Playsound("Resource/Sound/TitleBGM.wav", true, true);

}

CTitleScene::~CTitleScene()
{

}

void CTitleScene::Init()
{
}

int CTitleScene::Update()
{
	title->Update();
	Sky->SetPos(mPos);

	//シーン切り替え
	if (GetKey(VK_RETURN) & 0x8000)
	{
		MoveFlg = true;
	}
	if (MoveFlg) {
		if (Fishes->GetFishPos().z < -30) {
			FADE.Start(50);
			return MAP;
		}
		Fishes->TitleUpdate();
		CAMERA.SetCameraPos(D3DXVECTOR3(0, 3, -5), Fishes->GetFishPos());
	}
	if (GetKey('I') & 0x8000) {
		FADE.Start(5);
		return SHOP;
	}
	if (GetKey('F') & 0x8000) {
		FADE.Start(5);
		return GAME;
	}
	return TITLE;
}

void CTitleScene::Draw2D()
{
	//Fishes->Draw2D();
	title->Draw2D();

}

void CTitleScene::Draw3D()
{
	Sky->Draw3D();
	Fishes->Draw3D();
}

void CTitleScene::End()
{
	m_PSound->LDSB8->Stop();
}
