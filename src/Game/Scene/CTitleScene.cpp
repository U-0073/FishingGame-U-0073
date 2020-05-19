#include"../../System/KdLibrary/KdLibrary.h"
#include "CTitleScene.h"
#include"../Title.h"
#include"../Skysphere.h"
#include"../Fish.h"
#include"../Sea.h"


CTitleScene::CTitleScene()
{
}

CTitleScene::~CTitleScene()
{
}

void CTitleScene::Init()
{
	Sky = std::make_shared<Skysphere>();
	Sky->Init();
	Fishes = std::make_shared<Fish>();
	Fishes->SetTagType(0);
	Fishes->Init();
	title = std::make_shared<Title>();
	title->Init();

	CAMERA.SetCameraPos(D3DXVECTOR3(0, 3, -5), Fishes->GetFishPos());
	MoveFlg = false;
	mPos = D3DXVECTOR3(0, 20, 0);
	m_PSound = RESOURCE_MNG.GetSound("TitleBGM");

}

int CTitleScene::Update()
{
	title->Update();
	Sky->SetPos(mPos);

	//�V�[���؂�ւ�
	if (GetKey(VK_RETURN) & 0x8000)
	{
		FADE.Start(10);
		MoveFlg = true;
		//return MAP;
	}
	if (MoveFlg) {
		if (Fishes->GetFishPos().z < -15) {
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
	if (GetKey('R') & 0x8000) {
		FADE.Start(5);
		return RESULT;
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
	Sky->End();
	Sky = nullptr;
	Fishes->End();
	Fishes = nullptr;
	title->End();
	title = nullptr;
	//sea->End();
	//sea = nullptr;

	m_PSound->LDSB8->Stop();
	m_PSound = nullptr;
}
