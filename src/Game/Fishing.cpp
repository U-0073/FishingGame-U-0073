#include "../System/KdLibrary/KdLibrary.h"
#include "Fishing.h"

C_Fishing::C_Fishing()
{
}

C_Fishing::~C_Fishing() {
	m_pModel = nullptr;
}


void C_Fishing::Init() {
}

void C_Fishing::Start() {
	GameObject::Init();
	m_pModel = RESOURCE_MNG.GetModel("./Resouce/3DModel/Buoy.x");
	ScileMat.CreateScale(3.0f, 3.0f, 3.0f);
	BuoiPos = PlayerVec + KdVec3(0.0f, -1.0f, 0.0f);
	TransMat.CreateTrans(BuoiPos);

	m_world = ScileMat * TransMat;
}

void C_Fishing::End() {
}

void C_Fishing::Update() {

	FishingProc();
}
void C_Fishing::FishingProc()
{
	static bool flg = false;
	static bool HitFlg = false;
	KdMatrix RotMat;
	D3DXVECTOR3	Vec;

	if (FishSceneFlg) {
		if (!flg) {
			RotMat.CreateRotationY(D3DXToRadian(CamAngY));
			D3DXVec3TransformCoord(&Vec, &D3DXVECTOR3(0, 0, 1), &RotMat);
			flg = true;
			BuoiPos = PlayerVec + (Vec * 10.0f) + KdVec3(0.0f, -3.7f, 0.0f);
		}
		if (BuoiFlg && !HitFlg) {
			if (BuoiPos.y < -2.9f)BuoiPos += KdVec3(0.0f, 0.1f, 0.0f);
			else BuoiPos.y = -2.9f;
		}

		if (GetKey('1') & 0x8000) {
			HitFlg = true;
		}
	}
	else {
		flg = false;
		HitFlg = false;
		GetFish = false;
	}

	if (HitFlg) {
		if (BuoiPos.y > -3.7f)BuoiPos -= KdVec3(0.0f, 0.15f, 0.0f);
		else {
			BuoiPos.y = -3.7f;
			if (GetKey('2') & 0x8000) {
				GetFish = true;
			}
		}
	}

	TransMat.CreateTrans(BuoiPos);
	m_world = ScileMat * TransMat;
}


void C_Fishing::Draw2D()
{
	RECT rcText = { 10,30 * 0,0,0 };
	char Text[100];
	sprintf_s(Text, sizeof(Text), "BuoiPos.x %f y %f z %f", BuoiPos.x, BuoiPos.y, BuoiPos.z);
	KD3D.GetFont()->DrawText(NULL, Text, -1, &rcText, DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));

}

void C_Fishing::Draw3D() {
	KD3D.SetWorldMatrix(&m_world);

	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pModel->Draw();
	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, FALSE);
}

