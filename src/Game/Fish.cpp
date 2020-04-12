#include"../System/KdLibrary/KdLibrary.h"
#include"Fish.h"

Fish::Fish()
{
	Start();
}

Fish::~Fish()
{
}

void Fish::Start()
{
	GameObject::Init();

	ScaleMat.CreateScale(0.1f, 0.1f, 0.1f);
	TransMat.CreateTrans(3.0f, -3.0f, 0.0f);
	m_world = ScaleMat * TransMat;
//	int name = rand() % 3;
	int name = 2;
	switch (name)
	{
	case 0:
		m_Tag = "RedSnapper";
		m_pModel = RESOURCE_MNG.GetModel("Resouce/3DModel/RedSnapper.x");
		break;
	case 1:
		m_Tag = "Saury";
		m_pModel = RESOURCE_MNG.GetModel("Resouce/3DModel/Saury.x");
		break;
	case 2:
		m_Tag = "Tuna";
		m_pModel = RESOURCE_MNG.GetModel("Resouce/3DModel/Tuna.x");
		break;
	}
}
void Fish::Init()
{
	int name = rand() % 3;
	switch (name)
	{
	case 0:
		m_Tag = "RedSnapper";
		m_pModel = RESOURCE_MNG.GetModel("Resouce/3DModel/RedSnapper.x");
		break;
	case 1:
		m_Tag = "Saury";
		m_pModel = RESOURCE_MNG.GetModel("Resouce/3DModel/Saury.x");
		break;
	case 2:
		m_Tag = "Tuna";
		m_pModel = RESOURCE_MNG.GetModel("Resouce/3DModel/Tuna.x");
		break;
	}
}

void Fish::Update()
{
	FishLen = KdVec3(FishVec.x, FishVec.y, FishVec.z);

	if (GetKey('Q') & 0x8000)
	{
		Init();
	}

	KdMatrix RotMat;
	static float FishPosZCnt;
	static float FishPosYCnt;

	if (!FishFlg) {
		D3DXVECTOR3	Vec;

		RotMat.CreateRotationY(D3DXToRadian(CamAngY));
		D3DXVec3TransformCoord(&Vec, &D3DXVECTOR3(0, 0, 1), &RotMat);

		FishVec = PlayerVec + Vec * 20 - KdVec3(0.0f, 4.0f, 0.0f);
		FishPosZCnt = 20.0f;
		FishPosYCnt = 8.0f;
	}
	else {
		if (FishPosZCnt > 0 &&FishPosYCnt<7) {

			D3DXVECTOR3	Vec;
			RotMat.CreateRotationY(D3DXToRadian(CamAngY));
			D3DXVec3TransformCoord(&Vec, &D3DXVECTOR3(0, 0, 1), &RotMat);

			FishVec -= Vec * 0.5;
			FishPosZCnt -= 0.5f;
		}

		if (FishPosYCnt > 0) {
			if (FishPosYCnt > 7) {
				FishVec += KdVec3(0.0f, 0.2f, 0.0f);
				FishPosYCnt -= 0.2f;
			}
			else {
			FishVec += KdVec3(0.0f, 0.2f, 0.0f);
			FishPosYCnt -= 0.4f;
			}
		}
	}

	KdMatrix RotMatX;
	RotMatX.CreateRotationX(D3DXToRadian(90));
	RotMat.CreateRotationY(D3DXToRadian(CamAngY - 90));
	TransMat.CreateTrans(FishVec);
	m_world = ScaleMat * RotMatX * RotMat * TransMat;
}


void Fish::Draw2D()
{
	RECT rcText = { 10,30 * 0,0,0 };
	char Text[100];
	sprintf_s(Text, sizeof(Text), "FishPos x %f y %f z %f", FishVec.x, FishVec.y, FishVec.z);
	KD3D.GetFont()->DrawText(NULL, Text, -1, &rcText, DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
}

void Fish::Draw3D()
{
	KD3D.SetWorldMatrix(&m_world);

	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pModel->Draw();
	KD3D.GetDev()->SetRenderState(D3DRS_LIGHTING, FALSE);
}

