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
	Fishes->TitleInit();
	title = std::make_shared<Title>();
	title->Init();

	CAMERA.SetCameraPos(D3DXVECTOR3(0, 3, -5), Fishes->GetFishPos());
	MoveFlg = false;
	clear = false;

	Excellent = 0;
	Miss = 10;

	mPos = D3DXVECTOR3(0, 20, 0);
	m_PSound = RESOURCE_MNG.GetSound("Smash");
	m_PSound->Playsound("Smash", true, true);
	m_PSE = RESOURCE_MNG.GetSound("水バッシャ_2");
}

int CTitleScene::Update()
{
	title->Update();
	
	//シーン切り替え
	if (GetKey(VK_RETURN) & 0x8000)
	{
		if (!MoveFlg) {
			m_PSE->Playsound("水バッシャ_2", true, false);
			FADE.Start(10);
			MoveFlg = true;
		}
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
	m_PSE->LDSB8->Stop();
	m_PSE = nullptr;
}
