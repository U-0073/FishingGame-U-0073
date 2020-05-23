#include"../../System/KdLibrary/KdLibrary.h"
#include"CResultScene.h"

CResultScene::CResultScene()
{
}

CResultScene::~CResultScene()
{
}

void CResultScene::Init()
{
	mPos = { 0,0,0 };

	Sky = std::make_shared<Skysphere>();
	Sky->Init();
	result = std::make_shared<Result>();
	result->Init();

	CAMERA.SetCameraPos(D3DXVECTOR3(0, 0, -5), Fishes->GetFishPos());
	KD3D.CreatePointLight(D3DXVECTOR3(0, 0, -1), D3DXVECTOR4(1, 1, 1, 1), D3DXVECTOR4(0.2, 0.2, 0.2, 0.2));
}

int CResultScene::Update()
{
	result->Update();
	Sky->SetPos(mPos);
	Fishes->ResultUpdate();
	if (GetKey(VK_RETURN) & 0x8000)
	{
		FADE.Start(5);
		return MAP;
	}

	if (GetKey('I') & 0x8000) {
		FADE.Start(5);
		return SHOP;
	}

	if (GetKey('F') & 0x8000) {
		FADE.Start(5);
		return GAME;
	}
	return RESULT;
}

void CResultScene::Draw2D()
{
	result->Draw2D();
}

void CResultScene::Draw3D()
{
	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, TRUE);
	
	Sky->Draw3D();
	Fishes->Draw3D();
	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, FALSE);
}

void CResultScene::End()
{
	Sky->End();
	Sky = nullptr;
	Fishes->End();
	Fishes = nullptr;
	result->End();
	result = nullptr;

}
