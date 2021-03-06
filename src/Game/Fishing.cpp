#include "../System/KdLibrary/KdLibrary.h"

#include "Fishing.h"
#include "Fish.h"

C_Fishing::C_Fishing()
{
}

C_Fishing::~C_Fishing() {
}

void C_Fishing::Init() {

	GameObject::Init();
	m_pModel = RESOURCE_MNG.GetModel("Buoy");
	ScileMat.SetScale(4.0f, 4.0f, 4.0f);
	BuoyPos = D3DXVECTOR3(0, 0, -50);
	TransMat.SetTrans(BuoyPos);

	m_world = ScileMat * TransMat;

	m_Fishes = std::make_shared<Fishes>();
	m_Fishes->Init();

}



void C_Fishing::Update()
{
	PlayerPos = DTWHOUCE.GetVec("Player");

	FishingProc();

	DTWHOUCE.SetVec("Buoy", BuoyPos);

	(*m_Fishes).Update();

}

void C_Fishing::FishingProc()
{
	KdMatrix RotMat;
	D3DXVECTOR3	Vec;
	FishingFlg = DTWHOUCE.GetFlg("Fishing");
	if (FishingFlg) {

		//ウキを海に投げ込む処理
		if (!StopFlg) {
			StopFlg = true;
			BuoyPos = PlayerPos + DTWHOUCE.GetVec("CamVecY") * 15;
			BuoyPos.y = 0;
		}
		//
		if (!HitFlg) {
			if (BuoyPos.y < -2.9f)BuoyPos += KdVec3(0.0f, 0.05f, 0.0f);
			else BuoyPos.y = -2.9f;
		}

	}
	else {
		//ブイをカメラの真後ろに置いて隠す
		KdVec3 Vec = DTWHOUCE.GetVec("CamLookVec");
		Vec.Inverse();
		BuoyPos = CAMERA.GetCameraPos() + (Vec * 1.5f);

		StopFlg = false;
		HitFlg = false;
	}
	
	
	TransMat.SetTrans(BuoyPos);
	m_world = ScileMat * TransMat;
}


void C_Fishing::Draw2D()
{
	m_Fishes->Draw2D();
}

void C_Fishing::Draw3D() {
	KD3D.SetWorldMatrix(&m_world);

	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pModel->Draw();
	m_Fishes->Draw3D();
	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, FALSE);
}

void C_Fishing::End() {
	m_Fishes->End();
	m_Fishes = nullptr;
	m_pModel = nullptr;

}
