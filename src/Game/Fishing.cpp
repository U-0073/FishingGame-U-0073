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
	BuoiPos = PlayerPos + KdVec3(0.0f, -1.0f, 0.0f);
	TransMat.SetTrans(BuoiPos);

	m_world = ScileMat * TransMat;

	m_Fishes = std::make_shared<Fishes>();
	m_Fishes->Init();

}



void C_Fishing::Update() {


	FishingProc();

	//m_Fishes->SetPlayerPos(PlayerPos);
	//m_Fishes->SetFishFlg(GetFish);
	//m_Fishes->SetCamAngY(CamAngY);
	(*m_Fishes).Update();
}

void C_Fishing::FishingProc()
{
	static bool StopFlg = false;
	static bool HitFlg = false;
	KdMatrix RotMat;
	D3DXVECTOR3	Vec;
	
	if (FishSceneFlg) {
		if (!StopFlg) {
			
			RotMat.CreateRotationY(D3DXToRadian(CamAngY));
			D3DXVec3TransformCoord(&Vec, &D3DXVECTOR3(0, 0, 1), &RotMat);
			StopFlg = true;
			BuoiPos = PlayerPos + (Vec * 20.0f) + KdVec3(0.0f, -3.7f, 0.0f);
		}
		if (BuoiFlg && !HitFlg) {
			if (BuoiPos.y < -2.9f)BuoiPos += KdVec3(0.0f, 0.05f, 0.0f);
			else BuoiPos.y = -2.9f;
		}

		if (GetKey('1') & 0x8000) {
			HitFlg = true;
		}
	}
	else {
		StopFlg = false;
		HitFlg = false;
		GetFish = false;
	}

	if (HitFlg) {
		if (BuoiPos.y > -3.7f)BuoiPos -= KdVec3(0.0f, 0.15f, 0.0f);
		else {
			BuoiPos.y = -3.7f;
			if (GetKey('2') & 0x8000) {
				HitFlg = false;
			}
			if (GetKey('3') & 0x8000) {
				GetFish = true;
			}
		}
	}

	TransMat.SetTrans(BuoiPos);
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
